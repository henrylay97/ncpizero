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
#include "NCPiZeroTruthVars.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "TSystem.h"
#include "TEfficiency.h"

#include <string>

void trigger_eff()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");

  const TString sampleName = "nue";
  const TString inputNameNu = "/sbnd/data/users/hlay/ncpizero/2022A/trigger/" 
    + sampleName + "*.flat.caf.root";
  const TString signalType = "ncpizero";

  const double gPOT = 6.6e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/trigger_eff";
  gSystem->Exec("mkdir -p " + saveDir);

  SpectrumLoader loaderNu(inputNameNu.Data());

  std::vector<Spectrum*> sNu;

  std::vector<Plot<SpillVar>> plots = sampleName == "nue" ? triggerEffPlotsNuE : triggerEffPlots;

  for(auto const& plot : plots)
    {
      if(signalType != "ncpizero" && plot.name != "True Neutrino Energy")
	continue;

      for(auto const& cut : trigger_cuts)
	{
	  std::string name = *plot.name.Data() + "_" + *cut.name.Data();
	  sNu.emplace_back(new Spectrum("nu_" + name, plot.binning, loaderNu, 
					plot.variable, cut.cut && kSignal));
	}
    }

  loaderNu.Go();

  int i = 0;

  for(auto const& plot : plots)
    {
      if(signalType != "ncpizero" && plot.name != "True Neutrino Energy")
	continue;

      TCanvas *canvas = new TCanvas("c " + plot.name,
				    "c " + plot.name);
      canvas->cd();
      TLegend *legend = new TLegend(plot.legBox[0], plot.legBox[1], plot.legBox[2], plot.legBox[3]);

      TH1D *hDenom = sNu[i]->ToTH1(gPOT);

      for(auto const& cut : trigger_cuts)
	{
	  if(cut.label == "no_cut")
	    {
	      TH1D *hNoCut = sNu[i]->ToTH1(gPOT);
	      hNoCut->SetLineColor(kGray+3);
	      hNoCut->SetFillStyle(3844);
	      hNoCut->SetFillColor(kGray);
	      hNoCut->SetTitle(plot.axes_labels);

	      std::cout << sNu[i]->ToTH1(sNu[i]->POT())->GetEntries() << std::endl;

	      double max = hNoCut->GetMaximum();
	      hNoCut->Scale(1./max);
	      hNoCut->Draw("hist");
	      legend->AddEntry(hNoCut, "True Distribution", "lf");
	    }
	  else
	    {
	      TH1D *hCut = sNu[i]->ToTH1(gPOT);
	      TEfficiency *eff = new TEfficiency(*hCut, *hDenom);
	      eff->SetLineColor(cut.colour);
	      eff->SetMarkerColor(cut.colour);
	      eff->Draw("same");
	      legend->AddEntry(eff, cut.name, "pl");

	      std::cout << sNu[i]->ToTH1(sNu[i]->POT())->GetEntries() << std::endl;
	    }
	  ++i;
	}
      legend->Draw();

      if(save)
	{
	  canvas->SaveAs(saveDir + "/" + sampleName + "_" + signalType + "_" + plot.label + "_trigger_eff.png");
	  canvas->SaveAs(saveDir + "/" + sampleName + "_" + signalType + "_" + plot.label + "_trigger_eff.pdf");
	}
    }
	  
}
