#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "TrueNuVars.h"
#include "NCPiZeroRecoVars.h"
#include "NCPiZeroCuts.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TSystem.h"

#include <string>

void ncpizero_selection(const bool save = true, TString saveDirExt = "basic", const std::vector<CutDef<Cut>> cuts = ncpizero_cuts, const bool test = false)
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");

  std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd";
  std::string inputNameIntime = "defname: official_MCP2022A_prodcorsika_proton_intime_filter_sce_reco2_concat_flat_caf_sbnd";

  if(test)
    {
      inputNameNu += " with limit 100";
      inputNameIntime += " with limit 20";
      saveDirExt += "_test";
    }

  const double gPOT = 1;//10e20;
  TString potString = Form(" (%g POT)", gPOT);
  potString.ReplaceAll("e+","x10^{");
  potString.ReplaceAll(" POT","} POT");

  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/slice_based_selection/selection/" + saveDirExt;
  gSystem->Exec("mkdir -p " + saveDir);
  ofstream log_file;
  log_file.open(saveDir + "/cut_table.log");

  SpectrumLoader loaderNu(inputNameNu);
  SpectrumLoader loaderIntime(inputNameIntime);

  Spectrum *sTotalSignal = new Spectrum("sTotalSignal", nuEnSignalPlot.binning, loaderNu,
					nuEnSignalPlot.variable, kNoSpillCut);

  Spectrum *sTotalSignalSlicesNu         = new Spectrum("sTotalSignalSlicesNu", slcCounterPlot.binning, loaderNu,
							slcCounterPlot.variable, kSignal && kGoodTruthMatch);
  Spectrum *sTotalBackgroundSlicesNu     = new Spectrum("sTotalBackgroundSlicesNu", slcCounterPlot.binning, loaderNu,
							slcCounterPlot.variable, !(kSignal && kGoodTruthMatch));
  Spectrum *sTotalNuFVBackgroundSlicesNu = new Spectrum("sTotalNuFVBackgroundSlicesNu", slcCounterPlot.binning, loaderNu,
							slcCounterPlot.variable, !(kSignal && kGoodTruthMatch) && kTrueFV);

  Spectrum *sTotalSignalSlicesIntime         = new Spectrum("sTotalSignalSlicesIntime", slcCounterPlot.binning, loaderIntime,
							    slcCounterPlot.variable, kSignal && kGoodTruthMatch);
  Spectrum *sTotalBackgroundSlicesIntime     = new Spectrum("sTotalBackgroundSlicesIntime", slcCounterPlot.binning, loaderIntime,
							    slcCounterPlot.variable, !(kSignal && kGoodTruthMatch));
  Spectrum *sTotalNuFVBackgroundSlicesIntime = new Spectrum("sTotalNuFVBackgroundSlicesIntime", slcCounterPlot.binning, loaderIntime,
							    slcCounterPlot.variable, !(kSignal && kGoodTruthMatch) && kTrueFV);
  
  std::vector<Spectrum*> sNu, sIntime;

  Cut previousCuts     = kNoCut;
  bool passedCRUMBSCut = true; //false;

  for(auto const& cut : cuts)
    {
      if(cut.name == "CRUMBS")
	passedCRUMBSCut = true;

      for(auto const& plot : reco_plots)
	{
	  if(!passedCRUMBSCut && plot.name == "Longest Track Length")
	    break;

	  for(auto const& category : ncpizero_sel_categories)
	    {
	      const std::string name = *category.label.Data() + "_" + *plot.name.Data();
  
	      sNu.emplace_back(new Spectrum("nu_" + name, plot.binning, loaderNu,
					    plot.variable, category.cut && previousCuts && cut.cut));

	      sIntime.emplace_back(new Spectrum("intime_" + name, plot.binning, loaderIntime,
						plot.variable, category.cut && previousCuts && cut.cut));
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

  const double totalSignal               = sTotalSignal->Integral(gPOT);
  const double totalSignalSlices         = sTotalSignalSlicesNu->Integral(gPOT) + sTotalSignalSlicesIntime->Integral(intimeScaledLive, 0, kLivetime);
  const double totalBackgroundSlices     = sTotalBackgroundSlicesNu->Integral(gPOT) + sTotalBackgroundSlicesIntime->Integral(intimeScaledLive, 0, kLivetime);
  const double totalNuFVBackgroundSlices = sTotalNuFVBackgroundSlicesNu->Integral(gPOT) + sTotalNuFVBackgroundSlicesIntime->Integral(intimeScaledLive, 0, kLivetime);
  
  log_file << "Total Signal: " << totalSignal << std::endl;
  log_file << "Total Signal Slices: " << totalSignalSlices << std::endl;
  log_file << "Total Background Slices: " << totalBackgroundSlices << std::endl;
  log_file << "Total Nu FV Background Slices: " << totalNuFVBackgroundSlices << std::endl;

  unsigned i =0, j = 0;
  passedCRUMBSCut = true; //false;

  std::vector<double> effVec, purVec, selEffVec, backRejVec, nuFVBackRejVec;

  for(auto const& cut : cuts)
    {
      if(cut.name == "CRUMBS")
	passedCRUMBSCut = true;

      gSystem->Exec("mkdir -p " + saveDir + "/" + cut.label);

      unsigned k = 0;

      for(auto const& plot : reco_plots)
        {
	  if(!passedCRUMBSCut && plot.name == "Longest Track Length")
	    break;

          TCanvas *canvas = new TCanvas("c " + plot.name + " " + cut.name,
                                        "c " + plot.name + " " + cut.name);
          canvas->cd();

          TLegend *legend = new TLegend(plot.legBox[0], plot.legBox[1], plot.legBox[2], plot.legBox[3]);
          THStack *stack = new THStack("stack_" + plot.name + "_" + cut.name, plot.axes_labels + potString);

          double selectedSig = 0., selected = 0., selectedNuFVBack = 0.;

          for(auto const& category : ncpizero_sel_categories)
            {
              TH1D *hist = sNu[i]->ToTH1(gPOT);
              hist->Add(sIntime[i]->ToTH1(intimeScaledLive, kLivetime));
              double integral = sNu[i]->Integral(gPOT);
              integral += sIntime[i]->Integral(intimeScaledLive, 0, kLivetime);

              if(category.label == "Signal")
                selectedSig = integral;

	      if(category.label != "Cosmic" && category.label != "Dirt" && category.label != "NonFVNu" && category.label != "Signal")
		selectedNuFVBack += integral;

              selected += integral;

              hist->SetLineColor(category.colour);
              hist->SetFillColorAlpha(category.colour, 0.4);

              stack->Add(hist);
              legend->AddEntry(hist, Form("%s (%'.0f)", category.name.Data(), integral), "lf");
              ++i;
            }

          if(plot.name == "FV Cut")
            stack->SetMaximum(1.8 * stack->GetMaximum());
          else if(plot.name == "Longest Track PDG")
            stack->SetMaximum(1.6 * stack->GetMaximum());
          else if(plot.name == "Cosine CoM Decay Angle")
            stack->SetMaximum(1.8 * stack->GetMaximum());
          stack->Draw("hist");


          const std::vector<std::string> binlabels = plot.binning.Labels();
          if(!binlabels.empty())
            {
              for(int bin = 1; bin <= stack->GetXaxis()->GetNbins(); ++bin)
                stack->GetXaxis()->SetBinLabel(bin, binlabels[bin-1].c_str());
            }

          legend->SetLineColorAlpha(0,0);
          legend->SetTextSize(0.04);
          legend->Draw();

          const double eff = selectedSig / totalSignal * 100;
          const double pur = selectedSig / selected * 100;
	  
	  const double selEff      = selectedSig / totalSignalSlices * 100;
	  const double backRej     = (1 - (selected - selectedSig) / totalBackgroundSlices) * 100;
	  const double nuFVBackRej = (1 - selectedNuFVBack / totalNuFVBackgroundSlices) * 100;

	  if(k == 0)
	    {
	      effVec.push_back(eff);
	      purVec.push_back(pur);
	      selEffVec.push_back(selEff);
	      backRejVec.push_back(backRej);
	      nuFVBackRejVec.push_back(nuFVBackRej);
	    }

	  double box[4] = {plot.legBox[0] + .03,
                           plot.legBox[1] - .14,
                           plot.legBox[2] + .03,
                           plot.legBox[3] - .31};
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
          delete canvas;
	  delete legend;
	  delete stack;
	  delete pvt;
	  ++k;
        }
      ++j;
    }

  log_file << "\\hline\n"
	   << "Cut Name & $\\epsilon$ (\\%) & $\\rho$ (\\%) & $\\epsilon\\rho$ & Selection $\\epsilon$ (\\%) & BR (\\%) & FV $\\nu$ BR (\\%)\\\\ \\hline" << std::endl;
  
  for(unsigned k = 0; k < effVec.size(); ++k)
    {
      log_file << cuts[k].name << " & " << Form("%.2f", effVec[k]) << " & " << Form("%.2f", purVec[k])
	       << " & " << Form("%.2f", (effVec[k] * purVec[k]) / 100.)
	       << " & " << Form("%.2f", selEffVec[k]) << " & " << Form("%.2f", backRejVec[k]) 
	       << " & " << Form("%.2f", nuFVBackRejVec[k]) << "\\\\ \\hline" << std::endl;
    }
  log_file.close();
}
