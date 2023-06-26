#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "/sbnd/data/users/hlay/cafstyle.C"

#include "Structs.h"
#include "TrueEventCategories.h"
#include "DummyVar.h"
#include "Cuts.h"

#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TSystem.h"

#include <string>
#include <iomanip>

void categorisation()
{
  selectionstyle();
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 100";
  const std::string inputNameIntime = "defname: official_MCP2022A_prodcorsika_proton_intime_filter_sce_reco2_concat_flat_caf_sbnd with limit 10";

  const double gPOT = 10e20;
  const bool save = true;
  const TString saveDir = "/sbnd/data/users/hlay/ncpizero/2022A/plots/reevaluation_jan23/categorisation";

  SpectrumLoader loaderNu(inputNameNu);
  SpectrumLoader loaderIntime(inputNameIntime);

  std::vector<Spectrum*> sNu, sIntime;

  const Plot plot = DummyPlot;
  const SpillCut cut = kNoSpillCut && kCRTHitVeto;

  for(auto const& cut : ncpizero_cuts)
    {
      for(auto const& category : ncpizero_categories)
        {
          std::string name = *category.label.Data() + "_" + *plot.name.Data();
          sNu.emplace_back(new Spectrum("nu_" + name, plot.binning, loaderNu,
                                        plot.variable, category.cut && cut.cut));
          sIntime.emplace_back(new Spectrum("intime_" + name, plot.binning,
                                            loaderIntime, plot.variable, category.cut && cut.cut));
        }
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
  std::vector<double> original(ncpizero_categories.size(), 0.);
  std::set<unsigned> double_lined_set = {0, 2, 4, 6, 8, 9, 17};

  for(auto const& cut : ncpizero_cuts)
    {
      std::cout << "\n Cut: " << cut.name << '\n' << std::endl;

      for(auto const& category : ncpizero_categories)
        {
          double integral = sNu[i]->Integral(gPOT);
          integral += sIntime[i]->Integral(intimeScaledLive, 0, kLivetime);

          if(j == 0)
            original[i] = integral;

          std::cout << std::setprecision(0) << std::fixed << category.latex_name << " & "
                    << category.description << " & " << integral;
          if(j != 0)
            std::cout << " & " << std::setprecision(2) << 100. * integral / original[i - j * original.size()] << "\\%";

          if(double_lined_set.find(i - j * original.size()) != double_lined_set.end())
            std::cout << " \\\\ \\hline \\hline" << std::endl;
          else
            std::cout << " \\\\ \\hline" << std::endl;

          ++i;
        }
      ++j;
    }
}
