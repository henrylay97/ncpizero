#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "Structs.h"
#include "TrueEventCategories.h"
#include "GenericVars.h"
#include "NCPiZeroRecoVars.h"
#include "NCPiZeroCuts.h"

void identify_events()
{
  setlocale(LC_NUMERIC, "");
  
  const std::string inputNameNu = "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_concat_flat_caf_sbnd with limit 3";
  const std::string inputNameIntime = "defname: official_MCP2022A_prodcorsika_proton_intime_filter_sce_reco2_concat_flat_caf_sbnd with limit 3";

  SpectrumLoader loaderNu(inputNameNu);
  SpectrumLoader loaderIntime(inputNameIntime);

  const SpillCut cut = kSignal && kDazzleCuts && !kShowerReq;
  const Binning bins = Binning::Simple(1, 0, 1);

  const Spectrum *sNu     = new Spectrum("sNu", bins, loaderNu, kPrintEvent, cut);
  const Spectrum *sIntime = new Spectrum("sIntime", bins, loaderIntime, kPrintEvent, cut);

  loaderNu.Go();
  loaderIntime.Go();
}
