#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "NCPiZeroTruthVars.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "TH2.h"

#include <string>

void pi_zero_reco()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 200";

  const double gPOT = 6.6e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/pi_zero_reco";

  SpectrumLoader loaderNu(inputNameNu);
  const Binning gridBins = Binning::Simple(4,0.5,4.5);
  const Binning gridBins0 = Binning::Simple(4,-0.5,3.5);
  const Binning gridBins1 = Binning::Simple(5,-0.5,4.5);

  Spectrum sPiZeroSimpleRecoGrid("pizero_reco_grid", gridBins, loaderNu, kPiZeroSimpleRecoStatus, 
				 kSignalTwoGamma);
  Spectrum sPiZeroThresholdRecoGrid("pizero_reco_grid", gridBins, loaderNu,
				    kPiZeroThresholdRecoStatus, kSignalTwoGamma);
  Spectrum sPiZeroHighThresholdRecoGrid("pizero_reco_grid", gridBins, loaderNu,
					kPiZeroHighThresholdRecoStatus, kSignalTwoGamma);
  Spectrum sPhotonOneShwTrkRecoGrid("photon_one_shw_trk_reco_grid", loaderNu, gridBins1, 
				 kPiZeroPhotonOneRecoShws, gridBins0, kPiZeroPhotonOneRecoTrks,
				 kSignalTwoGamma);
  Spectrum sPhotonTwoShwTrkRecoGrid("photon_one_shw_trk_reco_grid", loaderNu, gridBins1, 
				 kPiZeroPhotonTwoRecoShws, gridBins0, kPiZeroPhotonTwoRecoTrks,
				 kSignalTwoGamma);

  loaderNu.Go();

  gStyle->SetPaintTextFormat("4.4f");

  TCanvas *simple_reco_canvas = new TCanvas("simple_reco_canvas","simple_reco_canvas");
  simple_reco_canvas->cd();

  TH1D *simpleRecoHist = sPiZeroSimpleRecoGrid.ToTH1(gPOT);
  gStyle->SetPalette(kBird);

  TH2D *simpleRecoGrid = new TH2D("simpleRecoGrid",";#gamma_{1};#gamma_{2};",2,0,2,2,0,2);
  simpleRecoGrid->SetBinContent(1, 1, simpleRecoHist->GetBinContent(4));
  simpleRecoGrid->SetBinContent(2, 1, simpleRecoHist->GetBinContent(2));
  simpleRecoGrid->SetBinContent(1, 2, simpleRecoHist->GetBinContent(3));
  simpleRecoGrid->SetBinContent(2, 2, simpleRecoHist->GetBinContent(1));
  simpleRecoGrid->SetMarkerSize(4);

  simpleRecoGrid->GetXaxis()->SetBinLabel(1, "Not Reconstructed");
  simpleRecoGrid->GetXaxis()->SetBinLabel(2, "Reconstructed");
  simpleRecoGrid->GetYaxis()->SetBinLabel(1, "#splitline{Not}{Reconstructed}");
  simpleRecoGrid->GetYaxis()->SetBinLabel(2, "Reconstructed");
  
  simpleRecoGrid->DrawNormalized("COLTEXT");

  if(save)
    {
      simple_reco_canvas->SaveAs(saveDir + "/pi_zero_simple_reco_grid.png");
      simple_reco_canvas->SaveAs(saveDir + "/pi_zero_simple_reco_grid.pdf");
    }

  TCanvas *threshold_reco_canvas = new TCanvas("threshold_reco_canvas","threshold_reco_canvas");
  threshold_reco_canvas->cd();

  TH1D *thresholdRecoHist = sPiZeroThresholdRecoGrid.ToTH1(gPOT);
  gStyle->SetPalette(kBird);

  TH2D *thresholdRecoGrid = new TH2D("thresholdRecoGrid",";#gamma_{1};#gamma_{2};",2,0,2,2,0,2);
  thresholdRecoGrid->SetBinContent(1, 1, thresholdRecoHist->GetBinContent(4));
  thresholdRecoGrid->SetBinContent(2, 1, thresholdRecoHist->GetBinContent(2));
  thresholdRecoGrid->SetBinContent(1, 2, thresholdRecoHist->GetBinContent(3));
  thresholdRecoGrid->SetBinContent(2, 2, thresholdRecoHist->GetBinContent(1));
  thresholdRecoGrid->SetMarkerSize(4);

  thresholdRecoGrid->GetXaxis()->SetBinLabel(1, "Not Reconstructed");
  thresholdRecoGrid->GetXaxis()->SetBinLabel(2, "Reconstructed");
  thresholdRecoGrid->GetYaxis()->SetBinLabel(1, "#splitline{Not}{Reconstructed}");
  thresholdRecoGrid->GetYaxis()->SetBinLabel(2, "Reconstructed");
  
  thresholdRecoGrid->DrawNormalized("COLTEXT");

  if(save)
    {
      threshold_reco_canvas->SaveAs(saveDir + "/pi_zero_threshold_reco_grid.png");
      threshold_reco_canvas->SaveAs(saveDir + "/pi_zero_threshold_reco_grid.pdf");
    }

  TCanvas *high_threshold_reco_canvas = new TCanvas("high_threshold_reco_canvas","high_threshold_reco_canvas");
  high_threshold_reco_canvas->cd();

  TH1D *highThresholdRecoHist = sPiZeroHighThresholdRecoGrid.ToTH1(gPOT);
  gStyle->SetPalette(kBird);

  TH2D *highThresholdRecoGrid = new TH2D("highThresholdRecoGrid",";#gamma_{1};#gamma_{2};",2,0,2,2,0,2);
  highThresholdRecoGrid->SetBinContent(1, 1, highThresholdRecoHist->GetBinContent(4));
  highThresholdRecoGrid->SetBinContent(2, 1, highThresholdRecoHist->GetBinContent(2));
  highThresholdRecoGrid->SetBinContent(1, 2, highThresholdRecoHist->GetBinContent(3));
  highThresholdRecoGrid->SetBinContent(2, 2, highThresholdRecoHist->GetBinContent(1));
  highThresholdRecoGrid->SetMarkerSize(4);

  highThresholdRecoGrid->GetXaxis()->SetBinLabel(1, "Not Reconstructed");
  highThresholdRecoGrid->GetXaxis()->SetBinLabel(2, "Reconstructed");
  highThresholdRecoGrid->GetYaxis()->SetBinLabel(1, "#splitline{Not}{Reconstructed}");
  highThresholdRecoGrid->GetYaxis()->SetBinLabel(2, "Reconstructed");
  
  highThresholdRecoGrid->DrawNormalized("COLTEXT");

  if(save)
    {
      high_threshold_reco_canvas->SaveAs(saveDir + "/pi_zero_high_threshold_reco_grid.png");
      high_threshold_reco_canvas->SaveAs(saveDir + "/pi_zero_high_threshold_reco_grid.pdf");
    }

  TCanvas *photon_one_shw_trk_reco_canvas = new TCanvas("photon_one_shw_trk_reco_canvas","photon_one_shw_trk_reco_canvas");
  photon_one_shw_trk_reco_canvas->cd();
  photon_one_shw_trk_reco_canvas->SetTopMargin(0.15);

  TH2D* photonOneShwTrkRecoGrid = (TH2D*) sPhotonOneShwTrkRecoGrid.ToTH2(gPOT);
  photonOneShwTrkRecoGrid->SetMarkerSize(3);
  photonOneShwTrkRecoGrid->SetTitle("#gamma_{1};nShowers;nTracks");
  photonOneShwTrkRecoGrid->DrawNormalized("COLTEXT");

  if(save)
    {
      photon_one_shw_trk_reco_canvas->SaveAs(saveDir + "/photon_one_shw_trk_reco_grid.png");
      photon_one_shw_trk_reco_canvas->SaveAs(saveDir + "/photon_one_shw_trk_reco_grid.pdf");
    }

  TCanvas *photon_two_shw_trk_reco_canvas = new TCanvas("photon_two_shw_trk_reco_canvas","photon_two_shw_trk_reco_canvas");
  photon_two_shw_trk_reco_canvas->cd();
  photon_two_shw_trk_reco_canvas->SetTopMargin(0.15);

  TH2D* photonTwoShwTrkRecoGrid = (TH2D*) sPhotonTwoShwTrkRecoGrid.ToTH2(gPOT);
  photonTwoShwTrkRecoGrid->SetMarkerSize(3);
  photonTwoShwTrkRecoGrid->SetTitle("#gamma_{2};nShowers;nTracks");
  photonTwoShwTrkRecoGrid->DrawNormalized("COLTEXT");

  if(save)
    {
      photon_two_shw_trk_reco_canvas->SaveAs(saveDir + "/photon_two_shw_trk_reco_grid.png");
      photon_two_shw_trk_reco_canvas->SaveAs(saveDir + "/photon_two_shw_trk_reco_grid.pdf");
    }

}
