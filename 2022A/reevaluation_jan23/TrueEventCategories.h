const SpillCut kCosmicSpill([](const caf::SRSpillProxy* sp) {
    return sp->mc.nnu == 0;
  });

const SpillCut kMultiNu([](const caf::SRSpillProxy* sp) {
    return sp->mc.nnu > 1;
  });

// Choose the neutrino that deposited the most energy in the TPC, this neutrino will
// be used to determine the event type (e.g. CCNuMu) and be the target of selection.
const SpillVar kBestNuID([](const caf::SRSpillProxy* sp) {
    int id = std::numeric_limits<int>::max(), counter = 0;
    double most_en = -std::numeric_limits<double>::max();

    for(auto const& nu : sp->mc.nu)
      {
        double visE = nu.plane[0][0].visE + nu.plane[0][1].visE + nu.plane[0][2].visE;

        if(visE > most_en)
          {
            most_en = visE;
            id      = counter;
          }
        ++counter;
      }
    return id;
  });

// Chose the slice that has the highest match to our "best neutrino" this is the
// slice we are aiming to select.
const SpillVar kTrueBestSlice([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp))
      return 999999;

    auto const& nuid = sp->mc.nu[kBestNuID(sp)].index;

    float best_eff(-1.f);
    unsigned id = 0, returnid = 999999;

    for(auto const &slc : sp->slc)
      {
        if(slc.tmatch.index == nuid && slc.tmatch.eff > best_eff)
          {
            best_eff = slc.tmatch.eff;
            returnid = id;
          }
        ++id;
      }

    return returnid;
  });

// Determine if this event contains multiple interactions in the AV. Note this is 
// different to the kMultiNu cut as kMultiNu does not exclude dirt neutrinos.
const SpillCut kPileUp([](const caf::SRSpillProxy* sp) {
    if(sp->mc.nnu < 2) return false;

    int nnuint = 0;

    for(auto const& nu : sp->mc.nu)
      {
        if(PtInVolAbsX(nu.position, avnd))
          ++nnuint;
      }

    return nnuint > 1;
  });

const SpillCut kTrueFV([](const caf::SRSpillProxy *sp) {
    return !kCosmicSpill(sp) && PtInVolAbsX(sp->mc.nu[kBestNuID(sp)].position, fvndAbs);
  });

const SpillCut kDirt([](const caf::SRSpillProxy *sp) {
    return !kCosmicSpill(sp) && !PtInVolAbsX(sp->mc.nu[kBestNuID(sp)].position, avnd);
  });

const SpillCut kNC([](const caf::SRSpillProxy* sp) {
    return !kDirt(sp) && !kCosmicSpill(sp) && sp->mc.nu[kBestNuID(sp)].isnc;
  });

const SpillCut kCC([](const caf::SRSpillProxy* sp) {
    return !kDirt(sp) && !kCosmicSpill(sp) && sp->mc.nu[kBestNuID(sp)].iscc;
  });

const SpillCut kCCNuMu([](const caf::SRSpillProxy* sp) {
    return kCC(sp) && std::abs(sp->mc.nu[kBestNuID(sp)].pdg) == 14;
  });

const SpillCut kCCNuE([](const caf::SRSpillProxy* sp) {
    return kCC(sp) && std::abs(sp->mc.nu[kBestNuID(sp)].pdg) == 12;
  });
    
const SpillVar kNPiPlus([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp)) return std::numeric_limits<unsigned>::max();

    unsigned int npiplus = 0;

    for(auto const& prim : sp->mc.nu[kBestNuID(sp)].prim)
      if(prim.pdg == 211) npiplus++;

    return npiplus;
  });

const SpillVar kNPiMinus([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp)) return std::numeric_limits<unsigned>::max();

    unsigned int npiminus = 0;

    for(auto const& prim : sp->mc.nu[kBestNuID(sp)].prim)
      if(prim.pdg == -211) npiminus++;

    return npiminus;
  });

const SpillVar kNPiZero([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp)) return std::numeric_limits<unsigned>::max();

    unsigned int npizero = 0;

    for(auto const& prim : sp->mc.nu[kBestNuID(sp)].prim)
      if(prim.pdg == 111) npizero++;

    return npizero;
  });

const SpillVar kNChargedPi = kNPiPlus + kNPiMinus;
const SpillVar kNPi = kNChargedPi + kNPiZero;

const SpillVar kNProton([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp)) return std::numeric_limits<unsigned>::max();

    unsigned int nproton = 0;

    for(auto const& prim : sp->mc.nu[kBestNuID(sp)].prim)
      if(prim.pdg == 2212) nproton++;

    return nproton;
  });

const SpillVar kNProtonThresh([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp)) return std::numeric_limits<unsigned>::max();

    unsigned int nproton = 0;

    for(auto const& prim : sp->mc.nu[kBestNuID(sp)].prim)
      {
	if(prim.pdg == 2212 && prim.genE > 0.02)
	  ++nproton;
      }

    return nproton;
  });

const SpillCut kNCPiZeroIncl([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0;
  });

const SpillCut kNC1PiZero([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) == 1;
  });

const SpillCut kNCMultiPiZero([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 1;
  });

const SpillCut kNCPiZeroProton([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNProton(sp) > 0;
  });

const SpillCut kNCPiZeroNoProton([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNProton(sp) == 0;
  });

const SpillCut kNCPiZeroProtonThresh([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNProtonThresh(sp) > 0;
  });

const SpillCut kNCPiZeroNoProtonThresh([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNProtonThresh(sp) == 0;
  });

const SpillCut kNCPiZeroChargedPion([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNChargedPi(sp) > 0;
  });

const SpillCut kNCPiZeroNoChargedPion([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) > 0 && kNChargedPi(sp) == 0;
  });

const SpillCut kNCIsolatedPiZero([](const caf::SRSpillProxy* sp) {
    return kNC(sp) && kNPiZero(sp) == 1 && kNProtonThresh(sp) == 0 && kNChargedPi(sp) == 0;
  });

const SpillCut kNCOther = kNC && !kNCPiZeroIncl;
const SpillCut kOther   = !kNC && !kCCNuMu && !kCCNuE && !kDirt && !kCosmicSpill;

std::vector<TrueCategory> ncpizero_categories = {
  {"NC #pi^{0} Inclusive", kNCPiZeroIncl, kBlack, "NCPiZeroIncl"},
  {"NC 1 #pi^{0}", kNC1PiZero, kBlack, "NC1PiZero"},
  {"NC Multi #pi^{0}", kNCMultiPiZero, kBlack, "NCMultiPiZero"},
  {"NC #pi^{0} Proton", kNCPiZeroProton, kBlack, "NCPiZeroProton"},
  {"NC #pi^{0} 0 Proton", kNCPiZeroNoProton, kBlack, "NCPiZeroNoProton"},
  {"NC #pi^{0} Proton Thresh", kNCPiZeroProtonThresh, kBlack, "NCPiZeroProtonThresh"},
  {"NC #pi^{0} 0 Proton Thresh", kNCPiZeroNoProtonThresh, kBlack, "NCPiZeroNoProtonThresh"},
  {"NC #pi^{0} #pi^{#pm}", kNCPiZeroChargedPion, kBlack, "NCPiZeroChargedPion"},
  {"NC #pi^{0} 0 #pi^{#pm}", kNCPiZeroNoChargedPion, kBlack, "NCPiZeroNoChargedPion"},
  {"NC Isolated #pi^{0}", kNCIsolatedPiZero, kBlack, "NCIsolatedPiZero"},
  {"Other NC", kNCOther, kBlack, "NC"},
  {"CC #nu_{#mu}", kCCNuMu, kBlack, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kBlack, "CCNuE"},
  {"NC", kNC, kBlack, "NC"},
  {"Dirt", kDirt, kBlack, "Dirt"},
  {"Intime Cosmic", kCosmicSpill, kBlack, "IntimeCosmic"},
  {"Neutrino", !kCosmicSpill, kBlack, "Neutrino"},
  {"Other", kOther, kBlack, "Other"},
  {"TOTAL", kNoSpillCut, kBlack, "Total"},
};
