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

void efficiency_of_selection()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 200";

  const double gPOT = 6.6e20;
  const bool save = false;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/efficiency_of_selection";
  const TString cutname   = "two_shw";
  gSystem->Exec("mkdir -p " + saveDir + "/" + cutname);

  SpectrumLoader loaderNu(inputNameNu);

  std::vector<Spectrum*> sNu;

  for(auto const& plot : effPlots)
    {
      for(auto const& cut : efficiency_cuts)
	{
	  std::string name = *plot.name.Data() + "_" + *cut.name.Data();
	  sNu.emplace_back(new Spectrum("nu_" + name, plot.binning, loaderNu, 
					plot.variable, cut.cut && kSignal));
	}
    }

  loaderNu.Go();

  int i = 0;

  for(auto const& plot : effPlots)
    {
      TCanvas *canvas = new TCanvas("c " + plot.name,
				    "c " + plot.name);
      canvas->cd();
      TLegend *legend = new TLegend(plot.legBox[0], plot.legBox[1], plot.legBox[2], plot.legBox[3]);

      TH1D *hDenom = sNu[i]->ToTH1(gPOT);

      for(auto const& cut : efficiency_cuts)
	{
	  if(cut.label == "no_cut")
	    {
	      TH1D *hNoCut = sNu[i]->ToTH1(gPOT);
	      hNoCut->SetLineColor(kGray+3);
	      hNoCut->SetFillStyle(3844);
	      hNoCut->SetFillColor(kGray);
	      hNoCut->SetTitle(plot.axes_labels);

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
	    }
	  ++i;
	}
      legend->Draw();

      if(save)
	{
	  canvas->SaveAs(saveDir + "/" + cutname + "/" + plot.label + "_eff.png");
	  canvas->SaveAs(saveDir + "/" + cutname + "/" + plot.label + "_eff.pdf");
	}
    }
	  
}
