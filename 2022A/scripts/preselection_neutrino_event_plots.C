#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "TrueNuVars.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TH1.h"

#include <string>

void preselection_neutrino_event_plots()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 100";

  const double gPOT = 6.6e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/preselection_neutrino_event_plots";

  SpectrumLoader loaderNu(inputNameNu);

  std::vector<Spectrum*> sNu;

  for(auto const& plot : nuPlots)
    {
      for(auto const& category : ncpizero_categories)
	{
	  std::string name = *category.label.Data() + "_" + *plot.name.Data();
	  sNu.emplace_back(new Spectrum(name, plot.binning,
					loaderNu, plot.variable, category.cut));
	}
    }
  loaderNu.Go();

  unsigned i = 0;
  for(auto const& plot : nuPlots)
    {
      TCanvas *canvas = new TCanvas("c_" + plot.name, "c_" + plot.name);
      canvas->cd();
      TLegend *legend = new TLegend(plot.legBox[0], plot.legBox[1], plot.legBox[2], plot.legBox[3]);
      THStack *stack = new THStack("stack_" + plot.name, plot.axes_labels);

      for(auto const& category : ncpizero_categories)
	{
	  TH1D *hist = sNu[i]->ToTH1(gPOT);
	  double integral = sNu[i]->Integral(gPOT);
	  hist->SetLineColor(category.colour);
	  hist->SetFillColorAlpha(category.colour, 0.4);

	  stack->Add(hist);
	  legend->AddEntry(hist, Form("%s (%'.0f)", category.name.Data(), integral), "lf");
	  ++i;
	}
      if(plot.name == "Bjorken X" || plot.name == "Inelasticity Y")
	stack->SetMaximum(1.5 * stack->GetMaximum());
      stack->Draw("hist");
      legend->SetLineColorAlpha(0,0);
      legend->SetTextSize(0.04);
      legend->Draw();

      if(save)
	{
	  canvas->SaveAs(saveDir + "/" + plot.label + ".png");
	  canvas->SaveAs(saveDir + "/" + plot.label + ".pdf");
	}
    }
}
