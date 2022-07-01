#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "TrueParticleVars.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"

void physics_book()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 100";

  const double gPOT = 6.6e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/physics_book";

  SpectrumLoader loaderNu(inputNameNu);

  std::vector<Spectrum*> sNu;

  std::vector<Particle> particles = { {"Muon", kRed+2, "muon", kPrimaryMuonCut},
				      {"Cosmic Muon", kTeal+2, "cosmic_muon", kCosmicMuonCut},
				      {"Dirt Muon", kOrange-6, "cosmic_muon", kCosmicMuonCut},
				      {"Electron", kBlue+2, "electron", kPrimaryElectronCut},
				      {"Charged Pion", kGreen+2, "charged_pion", kPrimaryChargedPionCut},
				      {"Neutral Pion", kYellow+1, "neutral_pion", kPrimaryNeutralPionCut},
				      {"Signal Neutral Pion", kYellow+1, "signal_neutral_pion", kPrimaryNeutralPionCut, kSignal},
				      {"Photon", kMagenta+2, "photon", kPrimaryPhotonCut},
				      {"Proton", kCyan+2, "proton", kPrimaryProtonCut},
  };

  for(auto const& particle : particles)
    {
      for(auto const& plot : particlePlots)
	{
	  Binning bins = plot.binning;
	  if(plot.label == "energy" || plot.label == "momentum")
	    {

	
	      if(particle.label == "electron") bins = Binning::Simple(25,0,5);
	      else if(particle.label == "charged_pion" || particle.label == "neutral_pion" 
		      || particle.label == "signal_neutral_pion") 
		bins = Binning::Simple(25,0,2);
	      else if(particle.label == "photon") bins = Binning::Simple(25,0,0.05);
	      else if(particle.label == "proton") bins = Binning::Simple(25,0,2);
	    }
	  
	  std::string name = *plot.name.Data() + "_" + *particle.name.Data();
	  sNu.emplace_back(new Spectrum(name, bins,
					loaderNu, plot.variable, particle.spillcut, particle.cut));
	}
    }
  loaderNu.Go();

  unsigned i = 0;
  for(auto const& particle : particles)
    {
      for(auto const& plot : particlePlots)
	{
	  TCanvas *canvas = new TCanvas("c " + plot.name + " " + particle.name, "c " + plot.name + " " + particle.name);
	  canvas->cd();

	  TH1D *hist = sNu[i]->ToTH1(gPOT);
	  hist->SetLineColor(particle.colour);
	  hist->SetFillColorAlpha(particle.colour, 0.4);
	  hist->SetTitle(plot.axes_labels + ";" + particle.name + "s");
	  hist->Draw("hist");

	  if(save)
	    {
	      canvas->SaveAs(saveDir + "/" + particle.label + "_" + plot.label + ".png");
	      canvas->SaveAs(saveDir + "/" + particle.label + "_" + plot.label + ".pdf");
	    }
	  ++i;
	}
    }
}
