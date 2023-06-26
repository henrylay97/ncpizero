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
#include "TGraph.h"

#include <string>

void optimise_cuts(Plot<Var> plot, const Cut base_cut, const bool save = true, const bool test = false, const bool rej_cut = false)
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");

  std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd";
  std::string inputNameIntime = "defname: official_MCP2022A_prodcorsika_proton_intime_filter_sce_reco2_concat_flat_caf_sbnd";

  if(test)
    {
      inputNameNu += " with limit 100";
      inputNameIntime += " with limit 20";
    }

  const double gPOT = 10e20;
  TString potString = Form(" (%g POT)", gPOT);
  potString.ReplaceAll("e+","x10^{");
  potString.ReplaceAll(" POT","} POT");

  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/slice_based_selection/selection/cut_optimisation/";
  if(save)
    gSystem->Exec("mkdir -p " + saveDir);

  SpectrumLoader loaderNu(inputNameNu);
  SpectrumLoader loaderIntime(inputNameIntime);

  plot.binning = Binning::Simple(plot.binning.NBins() * 2, plot.binning.Min(), plot.binning.Max());

  Spectrum *sTotalSlicesNu = new Spectrum("sTotalSlicesNu", slcCounterPlot.binning, loaderNu,
					  slcCounterPlot.variable, kNoCut);

  Spectrum *sTotalSlicesIntime = new Spectrum("sTotalSlicesIntime", slcCounterPlot.binning, loaderIntime,
					      slcCounterPlot.variable, kNoCut);

  Spectrum *sTotalSignalSlices = new Spectrum("sTotalSignalSlices", slcCounterPlot.binning, loaderNu,
					      slcCounterPlot.variable, kNoCut && kSignal && kGoodTruthMatch);

  Spectrum *sCutVarSignalNu = new Spectrum("sCutVarSignalNu", plot.binning, loaderNu,
					   plot.variable, kSignal && kGoodTruthMatch && base_cut);
  Spectrum *sCutVarBackNu = new Spectrum("sCutVarBackNu", plot.binning, loaderNu,
					 plot.variable, !(kSignal && kGoodTruthMatch) && base_cut);
  Spectrum *sCutVarBackIntime = new Spectrum("sCutVarBackIntime", plot.binning, loaderIntime,
					     plot.variable, !(kSignal && kGoodTruthMatch) && base_cut);
  loaderNu.Go();
  loaderIntime.Go();

  const double nomInt           = 5e12;
  const double targetLive       = gPOT / nomInt;
  const double nuPOT            = sTotalSlicesNu->POT();
  const double nuLive           = sTotalSlicesNu->Livetime();
  const double nuScaledLive     = nuLive * gPOT / nuPOT;
  const double intimeScaledLive = targetLive - nuScaledLive;

  std::cout << "Neutrino POT = " << sTotalSlicesNu->POT() << " from " << sTotalSlicesNu->Livetime() << " spills" << std::endl;
  std::cout << "Cosmic POT = " << sTotalSlicesIntime->POT() << " from " << sTotalSlicesIntime->Livetime() << " spills" << std::endl;

  TH1D *sigHist  = sCutVarSignalNu->ToTH1(gPOT);
  TH1D *backHist = sCutVarBackNu->ToTH1(gPOT);
  backHist->Add(sCutVarBackIntime->ToTH1(intimeScaledLive, kLivetime));

  const float totalSignal = sTotalSignalSlices->Integral(gPOT);
  const float initSignal  = sCutVarSignalNu->Integral(gPOT);
  const float totalBack   = sCutVarBackNu->Integral(gPOT) + sCutVarBackIntime->Integral(intimeScaledLive, 0, kLivetime);

  TGraph *gEff = new TGraph();
  gEff->SetMarkerColor(kRed+2);
  TGraph *gPur = new TGraph();
  gPur->SetMarkerColor(kBlue+2);
  TGraph *gEP  = new TGraph();
  gEP->SetMarkerColor(kMagenta+2);

  gEff->SetTitle(plot.name + ";Cut Value;Fraction");

  float accumSignal = initSignal, accumBack = totalBack, maxEP = -std::numeric_limits<float>::max(), optimal_cut = -std::numeric_limits<float>::max(),
    max = -std::numeric_limits<float>::max();

  int i = rej_cut ? sigHist->GetNbinsX()+1 : 0;
  int N = rej_cut ? 0 : sigHist->GetNbinsX()+1;

  while((rej_cut && i > N) || (!rej_cut && i < N))
    {
      accumSignal -= sigHist->GetBinContent(i);
      accumBack   -= backHist->GetBinContent(i);

      if(accumSignal < 0)
	break;

      const float eff = (accumSignal / totalSignal) * 100;
      const float pur = (accumSignal / (accumSignal + accumBack)) * 100;
      const float ep  = eff * pur / 100;
      const float cut = rej_cut ? sigHist->GetBinLowEdge(i) : sigHist->GetBinLowEdge(i) + sigHist->GetBinWidth(i);

      std::cout << "Cut: " << cut << " Signal: " << accumSignal << " Back: " << accumBack << std::endl;
      std::cout << "\tEff: " << eff << " Pur: " << pur << " Eff*Pur: " << ep << std::endl;

      if(ep > maxEP)
	{
	  maxEP = ep;
	  optimal_cut = cut;
	}

      if(eff > max)
	max = eff;
      if(pur > max)
	max = pur;
      if(ep > max)
	max = ep;

      gEff->SetPoint(i, cut, eff);
      gPur->SetPoint(i, cut, pur);
      gEP->SetPoint(i, cut, eff * pur / 100);

      if(rej_cut)
	--i;
      else
	++i;
    }

  TLine *line = new TLine(optimal_cut, 0, optimal_cut, 110);
  line->SetLineStyle(9);
  line->SetLineWidth(3);

  TPaveText *pt = new TPaveText(.26, .38, .5, .43, "NDC");
  pt->AddText(Form("Optimal Cut: %.4f", optimal_cut));
  pt->AddText(Form("Efficiency x Purity: %.2f %%", maxEP));
  pt->SetTextColor(kBlack);
  pt->SetTextSize(0.03);
  pt->SetFillColor(kWhite);
  pt->SetBorderSize(0);
  pt->SetLineWidth(0);
  pt->SetTextAlign(11);

  TLegend *leg = new TLegend(.23, .45, .5, .55);
  leg->AddEntry(gEff, "Efficiency", "p");
  leg->AddEntry(gPur, "Purity", "p");
  leg->AddEntry(gEP, "Efficiency x Purity", "p");

  TCanvas *c = new TCanvas("c", "c");
  c->SetTopMargin(.15);
  gEff->Draw("AP");
  gEff->SetMinimum(0);
  gEff->SetMaximum(110);
  gPur->Draw("Psame");
  gEP->Draw("Psame");
  line->Draw();
  pt->Draw();
  leg->Draw();

  if(save)
    {
      c->SaveAs(saveDir + "/" + plot.label + ".png");
      c->SaveAs(saveDir + "/" + plot.label + ".pdf");
    }
}
