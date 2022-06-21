#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "NCPiZeroRecoVars.h"
#include "NCPiZeroCuts.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TSystem.h"

#include <string>

void ncpizero_basic_selection()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 20";
  const std::string inputNameIntime = "defname: official_MCP2022A_prodcorsika_proton_intime_filter_sce_reco2_concat_flat_caf_sbnd with limit 10";

  const double gPOT = 6.6e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/ncpizero_basic_selection";

  SpectrumLoader loaderNu(inputNameNu);
  SpectrumLoader loaderIntime(inputNameIntime);

  std::vector<Spectrum*> sNu, sIntime;

  SpillCut previousCuts = kNoSpillCut;

  bool passedTwoShwCut = false;

  for(auto const& cut : ncpizero_cuts)
    {
      if(cut.name == "Has At Least 2 Showers")
	passedTwoShwCut = true;

      for(auto const& plot : recoPlots)
	{
	  if(!passedTwoShwCut && plot.name == "Leading Shower Energy")
	    break;

	  for(auto const& category : ncpizero_sel_categories)
	    {
	      std::string name = *category.label.Data() + "_" + *plot.name.Data();
	      sNu.emplace_back(new Spectrum("nu_" + name, plot.binning, loaderNu, 
					    plot.variable, 
					    category.cut && previousCuts && cut.cut));
	      sIntime.emplace_back(new Spectrum("intime_" + name, plot.binning, 
						loaderIntime, plot.variable,  
						category.cut && previousCuts && cut.cut));
	    }
	}
      previousCuts = previousCuts && cut.cut;
    }

  loaderNu.Go();
  loaderIntime.Go();

  const double nomInt           = 5e12;
  const double targetLive       = gPOT / nomInt;
  const double nuPOT            = sNu[0]->POT();
  const double nuLive           = sNu[0]->Livetime();
  const double nuScaledLive     = nuLive * gPOT / nuPOT;
  const double intimeScaledLive = targetLive - nuScaledLive;
  const int nuEvents            = nuLive;
  const double cosmicPOT        = nuEvents * nomInt / ( 1 - (1.f / 21.8f));

  unsigned i = 0, j = 0;
  passedTwoShwCut = false;

  double initialSignal = 0.;

  for(auto const& cut : ncpizero_cuts)
    {
      if(cut.name == "Has At Least 2 Showers")
	passedTwoShwCut = true;

      gSystem->Exec("mkdir -p " + saveDir + "/" + cut.label);
      for(auto const& plot : recoPlots)
	{
	  if(!passedTwoShwCut && plot.name == "Leading Shower Energy")
	    break;

	  TCanvas *canvas = new TCanvas("c " + plot.name + " " + cut.name, 
					"c " + plot.name + " " + cut.name);
	  canvas->cd();
	  TLegend *legend = new TLegend(plot.legBox[0], plot.legBox[1], plot.legBox[2], plot.legBox[3]);
	  THStack *stack = new THStack("stack_" + plot.name + "_" + cut.name, plot.axes_labels);

	  double selectedSig = 0., selected = 0.;

	  for(auto const& category : ncpizero_sel_categories)
	    {
	      TH1D *hist = sNu[i]->ToTH1(gPOT);
	      hist->Add(sIntime[i]->ToTH1(intimeScaledLive, kLivetime));
	      double integral = sNu[i]->Integral(gPOT);
	      integral += sIntime[i]->Integral(intimeScaledLive, 0, kLivetime);

	      if(j == 0 && category.label == "Signal")
		initialSignal = integral;
	      
	      if(category.label == "Signal")
		selectedSig = integral;

	      selected += integral;


	      hist->SetLineColor(category.colour);
	      hist->SetFillColorAlpha(category.colour, 0.4);

	      stack->Add(hist);
	      legend->AddEntry(hist, Form("%s (%'.0f)", category.name.Data(), integral), "lf");
	      ++i;
	    }
	  if(plot.name == "FV Cut")
	    stack->SetMaximum(1.8 * stack->GetMaximum());
	  stack->Draw("hist");
	  legend->SetLineColorAlpha(0,0);
	  legend->SetTextSize(0.04);
	  legend->Draw();

	  const double eff = selectedSig / initialSignal * 100;
	  const double pur = selectedSig / selected * 100;

	  double box[4] = {.62, .36, .92, .48};
	  
	  if(plot.name == "FV Cut")
	    { box[0] = .25; box[1] = .68; box[2] = .47; box[3] = .80; }
	  else if(plot.name == "CRUMBS Score")
	    { box[0] = .25; box[1] = .43; box[2] = .47; box[3] = .55; }
 
	  TPaveText *pvt = new TPaveText(box[0],box[1],box[2],box[3], "NB NDC");
	  pvt->SetTextAlign(12);
	  pvt->SetTextSize(0.05);
	  pvt->AddText(Form("Efficiency: %.2f%%", eff));
	  pvt->AddText(Form("Purity: %.2f%%", pur));
	  pvt->Draw();	  

	  if(save)
	    {
	      canvas->SaveAs(saveDir + "/" + cut.label + "/" + plot.label + "_" + cut.label + ".png");
	      canvas->SaveAs(saveDir + "/" + cut.label + "/" + plot.label + "_" + cut.label + ".pdf");
	    }
	}
      ++j;
    }
}
