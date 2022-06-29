const SpillVar kPiZeroID([](const caf::SRSpillProxy* sp) -> unsigned {
    if(!kSignal(sp)) return 999999;

    for(int i = 0; i < sp->mc.nu[kBestNuID(sp)].nprim; ++i) {
      auto const& prim = sp->mc.nu[kBestNuID(sp)].prim[i];
      if(prim.pdg == 111) return i;
    }

    return 999999;
  });

const SpillCut kSignalTwoGamma([](const caf::SRSpillProxy* sp) {
    if(!kSignal(sp)) return false;

    for(int i = 0; i < sp->mc.nu[kBestNuID(sp)].nprim; ++i) {
      auto const& prim = sp->mc.nu[kBestNuID(sp)].prim[i];
      if(prim.pdg == 111 && prim.daughters.size() == 2) return true;
    }
    
    return false;
  });

/*
const SpillVar kPiZeroPhotonIDs([](const caf::SRSpillProxy* sp) -> std::pair<unsigned, unsigned> {
    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return std::pair<unsigned, unsigned>(999999,999999);

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return std::pair<unsigned, unsigned>(999999,999999);

    int photon_one_id = daughters[0];
    int photon_two_id = daughters[1];

    double en_one(-999999.), en_two(-999999.);

    unsigned one_id(999999), two_id(999999);

    for(int i = 0; i < sp->ntrue_particles; ++i)
      {
        auto const& part = sp->true_particles[i];
        if(part.G4ID == photon_one_id)
          {
            en_one = part.genE;
            one_id = i;
          }
        if(part.G4ID == photon_two_id)
          {
            en_two = part.genE;
            two_id = i;
          }
      }

    return en_one > en_two ? std::pair<unsigned, unsigned>(one_id, two_id) : std::pair<unsigned, unsigned>(two_id, one_id);
  });
*/

const SpillVar kPiZeroSimpleRecoStatus([](const caf::SRSpillProxy *sp) {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_one_id = daughters[0];
    int photon_two_id = daughters[1];

    bool reco_one = false, reco_two = false;

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_one_id 
	   && shw.truth.bestmatch.hit_completeness > 0
	   && shw.truth.bestmatch.hit_purity > 0)
	    reco_one = true;
	else if(shw.truth.bestmatch.G4ID == photon_two_id 
		&& shw.truth.bestmatch.hit_completeness > 0
		&& shw.truth.bestmatch.hit_purity > 0)
	    reco_two = true;
      }

    if(reco_one && reco_two)
      return 1.;
    else if(reco_one)
      return 2.;
    else if(reco_two)
      return 3.;
    else 
      return 4.;
  });
	
const SpillVar kPiZeroThresholdRecoStatus([](const caf::SRSpillProxy *sp) {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_one_id = daughters[0];
    int photon_two_id = daughters[1];

    bool reco_one = false, reco_two = false;

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_one_id 
	   && shw.truth.bestmatch.hit_completeness > 0.5
	   && shw.truth.bestmatch.hit_purity > 0.5)
	    reco_one = true;
	else if(shw.truth.bestmatch.G4ID == photon_two_id 
		&& shw.truth.bestmatch.hit_completeness > 0.5
		&& shw.truth.bestmatch.hit_purity > 0.5)
	    reco_two = true;
      }

    if(reco_one && reco_two)
      return 1.;
    else if(reco_one)
      return 2.;
    else if(reco_two)
      return 3.;
    else 
      return 4.;
  });

const SpillVar kPiZeroHighThresholdRecoStatus([](const caf::SRSpillProxy *sp) {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_one_id = daughters[0];
    int photon_two_id = daughters[1];

    bool reco_one = false, reco_two = false;

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_one_id 
	   && shw.truth.bestmatch.hit_completeness > 0.8
	   && shw.truth.bestmatch.hit_purity > 0.8)
	    reco_one = true;
	else if(shw.truth.bestmatch.G4ID == photon_two_id 
		&& shw.truth.bestmatch.hit_completeness > 0.8
		&& shw.truth.bestmatch.hit_purity > 0.8)
	    reco_two = true;
      }

    if(reco_one && reco_two)
      return 1.;
    else if(reco_one)
      return 2.;
    else if(reco_two)
      return 3.;
    else 
      return 4.;
  });

const SpillVar kPiZeroPhotonOneRecoShws([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_one_id = daughters[0];

    int nshw(0);

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_one_id) 
	  ++nshw;
      }

    return nshw;
  });

const SpillVar kPiZeroPhotonOneRecoTrks([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_one_id = daughters[0];

    int ntrk(0);

    for(auto const& trk : sp->reco.trk)
      {
	if(trk.truth.bestmatch.G4ID == photon_one_id) 
	  ++ntrk;
      }

    return ntrk;
  });

const SpillVar kPiZeroPhotonTwoRecoShws([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_two_id = daughters[1];

    int nshw(0);

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_two_id) 
	  ++nshw;
      }

    return nshw;
  });

const SpillVar kPiZeroPhotonTwoRecoTrks([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) 
      return -1.;

    const unsigned pion_id = kPiZeroID(sp);
    if(pion_id == 999999)
      return -1.;

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return -1.;

    int photon_two_id = daughters[1];

    int ntrk(0);

    for(auto const& trk : sp->reco.trk)
      {
	if(trk.truth.bestmatch.G4ID == photon_two_id) 
	  ++ntrk;
      }

    return ntrk;
  });
