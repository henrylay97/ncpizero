constexpr unsigned def_unsigned = std::numeric_limits<unsigned>::max();

const Cut kCosmicSlice([](const caf::SRSliceProxy* slc) {
    return slc->tmatch.index == -999;
  });

const FidVol fvndpizero { +5, +180, -180, +180, +10, +450};

const Cut kTrueFV([](const caf::SRSliceProxy *slc) {
    return !kCosmicSlice(slc) && PtInVolAbsX(slc->truth.position, fvndpizero);
  });

const Cut kDirt([](const caf::SRSliceProxy *slc) {
    return !kCosmicSlice(slc) && !PtInVolAbsX(slc->truth.position, avnd);
  });

const Cut kNC([](const caf::SRSliceProxy *slc) {
    return kTrueFV(slc) && !kCosmicSlice(slc) && slc->truth.isnc;
  });

const Cut kCC([](const caf::SRSliceProxy *slc) {
    return kTrueFV(slc) && !kCosmicSlice(slc) && slc->truth.iscc;
  });

const Cut kCCNuE([](const caf::SRSliceProxy *slc) {
    return kCC(slc) && abs(slc->truth.pdg) == 12;
  });

const Cut kCCNuMu([](const caf::SRSliceProxy *slc) {
    return kCC(slc) && abs(slc->truth.pdg) == 14;
  });

const Var kNPiPlus([](const caf::SRSliceProxy *slc) -> unsigned {
    if(kCosmicSlice(slc))
      return def_unsigned;

    unsigned npiplus = 0;

    for(auto const& prim : slc->truth.prim)
      if(prim.pdg == 211)
	++npiplus;

    return npiplus;
  });

const Var kNPiMinus([](const caf::SRSliceProxy *slc) -> unsigned {
    if(kCosmicSlice(slc))
      return def_unsigned;

    unsigned npiminus = 0;

    for(auto const& prim : slc->truth.prim)
      if(prim.pdg == -211)
	++npiminus;

    return npiminus;
  });

const Var kNPiZero([](const caf::SRSliceProxy *slc) -> unsigned {
    if(kCosmicSlice(slc))
      return def_unsigned;

    unsigned npizero = 0;

    for(auto const& prim : slc->truth.prim)
      if(prim.pdg == 111)
	++npizero;

    return npizero;
  });

const Var kNChargedPi = kNPiPlus + kNPiMinus;
const Var kNPi        = kNChargedPi + kNPiZero;

const Var kNProton([](const caf::SRSliceProxy *slc) ->unsigned {
    if(kCosmicSlice(slc))
      return def_unsigned;

    unsigned nproton = 0;

    for(auto const& prim : slc->truth.prim)
      if(prim.pdg == 2212)
	++nproton;

    return nproton;
  });

constexpr double kProtonMass = 9.38272081e-1; // GeV

const Var kNProtonThresh([](const caf::SRSliceProxy *slc) ->unsigned {
    if(kCosmicSlice(slc))
      return def_unsigned;

    unsigned nproton = 0;

    for(auto const& prim : slc->truth.prim)
      if(prim.pdg == 2212 && (prim.genE - kProtonMass) > 0.02)
	++nproton;

    return nproton;
  });

const Cut kNCPiZeroIncl([](const caf::SRSliceProxy *slc) {
    return kNC(slc) && kNPiZero(slc) > 0;
  });

const Cut kNC1PiZero([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) == 1;
  });

const Cut kNCMultiPiZero([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 1;
  });

const Cut kNCPiZeroProton([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 0 && kNProton(slc) > 0;
  });

const Cut kNCPiZeroNoProton([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 0 && kNProton(slc) == 0;
  });

const Cut kNCPiZeroProtonThresh([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 0 && kNProtonThresh(slc) > 0;
  });

const Cut kNCPiZeroNoProtonThresh([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 0 && kNProtonThresh(slc) == 0;
  });

const Cut kNCPiZeroChargedPion([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) > 0 && kNChargedPi(slc) > 0;
  });

const Cut kNCIsolatedPiZero([](const caf::SRSliceProxy* slc) {
    return kNC(slc) && kNPiZero(slc) == 1 && kNProtonThresh(slc) == 0 && kNChargedPi(slc) == 0;
  });

const Cut kCoherent([](const caf::SRSliceProxy* slc) {
    return slc->truth.genie_mode == 3;
  });

const Cut kQE([](const caf::SRSliceProxy* slc) {
    return slc->truth.genie_mode == 0;
  });

const Cut kMEC([](const caf::SRSliceProxy* slc) {
    return slc->truth.genie_mode == 10;
  });

const Cut kResonant([](const caf::SRSliceProxy* slc) {
    return slc->truth.genie_mode == 1;
  });

const Cut kDIS([](const caf::SRSliceProxy* slc) {
    return slc->truth.genie_mode == 2;
  });

const Cut kSignal1PiZero([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNPiZero(slc) == 1;
  });

const Cut kSignal2PiZero([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNPiZero(slc) == 2;
  });

const Cut kSignal3PlusPiZero([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNPiZero(slc) >= 3;
  });

const Cut kSignal0ChargedPi([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNChargedPi(slc) == 0;
  });

const Cut kSignal1ChargedPi([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNChargedPi(slc) == 1;
  });

const Cut kSignal2ChargedPi([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNChargedPi(slc) == 2;
  });

const Cut kSignal3PlusChargedPi([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNChargedPi(slc) >= 3;
  });

const Cut kSignal0Proton([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNProtonThresh(slc) == 0;
  });

const Cut kSignal1Proton([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNProtonThresh(slc) == 1;
  });

const Cut kSignal2Proton([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNProtonThresh(slc) == 2;
  });

const Cut kSignal3PlusProton([](const caf::SRSliceProxy* slc) {
    return kNCPiZeroIncl(slc) && kNProtonThresh(slc) >= 3;
  });

const Cut kGoodTruthMatch([](const caf::SRSliceProxy* slc) {
    if(kCosmicSlice(slc))
      return false;
    
    return slc->tmatch.eff > .5;
  });

const Cut kSignal  = kNCPiZeroIncl;
const Cut kNCOther = kNC && !kSignal;
const Cut kNonFVNu = !kNC && !kCCNuMu && !kCCNuE && !kDirt && !kCosmicSlice;
const Cut kOther   = !kNC && !kCCNuMu && !kCCNuE && !kDirt && !kCosmicSlice && kTrueFV;

std::vector<TrueCategory<Cut>> ncpizero_event_types = {
  {"Coherent", kSignal && kCoherent && kGoodTruthMatch, kRed, "Coherent"},
  {"QE", kSignal && kQE && kGoodTruthMatch, kBlue, "QE"},
  {"MEC", kSignal && kMEC && kGoodTruthMatch, kMagenta+2, "MEC"},
  {"Resonant", kSignal && kResonant && kGoodTruthMatch, kGreen+1, "Resonant"},
  {"DIS", kSignal && kDIS && kGoodTruthMatch, kOrange+2, "DIS"},
};

std::vector<TrueCategory<Cut>> ncpizero_final_states_by_pi_zero = {
  {"1#pi^{0}", kSignal1PiZero && kGoodTruthMatch, kRed+2, "1#pi^{0}"},
  {"2#pi^{0}", kSignal2PiZero && kGoodTruthMatch, kRed, "2#pi^{0}"},
  {"#geq3#pi^{0}", kSignal3PlusPiZero && kGoodTruthMatch, kRed-7, "#geq3#pi^{0}"}
};

std::vector<TrueCategory<Cut>> ncpizero_final_states_by_charged_pi = {
  {"0#pi^{#pm}", kSignal0ChargedPi && kGoodTruthMatch, kBlue+4, "0#pi^{#pm}"},
  {"1#pi^{#pm}", kSignal1ChargedPi && kGoodTruthMatch, kBlue+2, "1#pi^{#pm}"},
  {"2#pi^{#pm}", kSignal2ChargedPi && kGoodTruthMatch, kBlue, "2#pi^{#pm}"},
  {"#geq3#pi^{#pm}", kSignal3PlusChargedPi && kGoodTruthMatch, kBlue-7, "#geq3#pi^{#pm}"}
};

std::vector<TrueCategory<Cut>> ncpizero_final_states_by_proton = {
  {"0p", kSignal0Proton && kGoodTruthMatch, kGreen+4, "0p"},
  {"1p", kSignal1Proton && kGoodTruthMatch, kGreen+2, "1p"},
  {"2p", kSignal2Proton && kGoodTruthMatch, kGreen, "2p"},
  {"#geq3p", kSignal3PlusProton && kGoodTruthMatch, kGreen-7, "#geq3p"}
};



std::vector<TrueCategory<Cut>> ncpizero_sel_categories = {
  {"Signal (NC #pi^{0})", kSignal && kGoodTruthMatch, kMagenta+2, "Signal"},
  {"Other NC", kNCOther, kOrange+2, "NC"},
  {"CC #nu_{#mu}", kCCNuMu, kGreen+2, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"Dirt", kDirt, kOrange+3, "Dirt"},
  {"Non-FV #nu", kNonFVNu, kGray+2, "NonFVNu"},
  {"Cosmic", kCosmicSlice, kRed+1, "Cosmic"},
  {"Bad Reco Signal", kSignal && !kGoodTruthMatch, kBlack, "BadRecoSignal"}
};



