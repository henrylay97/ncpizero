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


const SpillVar kPiZeroLeadingPhotonID([](const caf::SRSpillProxy* sp) -> unsigned {
    if(!kSignalTwoGamma(sp)) return false;

    const unsigned pion_id = kPiZeroID(sp);

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return 999999;

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

    return en_one > en_two ? one_id : two_id;
  });

const SpillVar kPiZeroSubLeadingPhotonID([](const caf::SRSpillProxy* sp) -> unsigned {
    if(!kSignalTwoGamma(sp)) return false;

    const unsigned pion_id = kPiZeroID(sp);

    auto const& pion = sp->mc.nu[kBestNuID(sp)].prim[pion_id];
    auto const& daughters = pion.daughters;

    if(daughters.size() != 2)
      return 999999;

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

    return en_one > en_two ? two_id : one_id;
  });


const SpillVar kPiZeroSimpleRecoStatus([](const caf::SRSpillProxy *sp) {
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_one_id = sp->true_particles[kPiZeroLeadingPhotonID(sp)].G4ID;
    int photon_two_id = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].G4ID;

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
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_one_id = sp->true_particles[kPiZeroLeadingPhotonID(sp)].G4ID;
    int photon_two_id = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].G4ID;

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
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_one_id = sp->true_particles[kPiZeroLeadingPhotonID(sp)].G4ID;
    int photon_two_id = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].G4ID;

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

const SpillVar kPiZeroLeadingPhotonRecoShws([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_one_id = sp->true_particles[kPiZeroLeadingPhotonID(sp)].G4ID;

    int nshw(0);

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_one_id) 
	  ++nshw;
      }

    return nshw;
  });

const SpillVar kPiZeroLeadingPhotonRecoTrks([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_one_id = sp->true_particles[kPiZeroLeadingPhotonID(sp)].G4ID;

    int ntrk(0);

    for(auto const& trk : sp->reco.trk)
      {
	if(trk.truth.bestmatch.G4ID == photon_one_id) 
	  ++ntrk;
      }

    return ntrk;
  });

const SpillVar kPiZeroSubLeadingPhotonRecoShws([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_two_id = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].G4ID;

    int nshw(0);

    for(auto const& shw : sp->reco.shw)
      {
	if(shw.truth.bestmatch.G4ID == photon_two_id) 
	  ++nshw;
      }

    return nshw;
  });

const SpillVar kPiZeroSubLeadingPhotonRecoTrks([](const caf::SRSpillProxy *sp) -> int {
    if(!kSignalTwoGamma(sp)) return -1.;
    
    int photon_two_id = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].G4ID;

    int ntrk(0);

    for(auto const& trk : sp->reco.trk)
      {
	if(trk.truth.bestmatch.G4ID == photon_two_id) 
	  ++ntrk;
      }

    return ntrk;
  });

const SpillVar kPiZeroTrueEnergy([](const caf::SRSpillProxy *sp) -> double {
    if(!kSignal(sp)) 
      return -1.;
    
    return sp->mc.nu[kBestNuID(sp)].prim[kPiZeroID(sp)].startE;
  });

const SpillVar kPiZeroPhotonOpeningAngle([](const caf::SRSpillProxy *sp) -> double {
    if(!kSignalTwoGamma(sp)) return -1.;

    auto const& leadDir    = sp->true_particles[kPiZeroLeadingPhotonID(sp)].startp;
    auto const& subleadDir = sp->true_particles[kPiZeroSubLeadingPhotonID(sp)].startp;

    TVector3 leadDirVec    = TVector3(leadDir.x, leadDir.y, leadDir.z);
    TVector3 subleadDirVec = TVector3(subleadDir.x, subleadDir.y, subleadDir.z);

    return TMath::RadToDeg() * leadDirVec.Angle(subleadDirVec);
  });

std::vector<Plot<SpillVar>> effPlots = { { "Pi0 Energy", kPiZeroTrueEnergy, Binning::Simple(30,0,1.5), ";True E_{#pi^{0}};Efficiency", "pizero_true_energy", {.59,.57,.89,.85} },
					 { "Pi0 Opening Angle", kPiZeroPhotonOpeningAngle, Binning::Simple(30,0,180), ";True #theta_{#gamma#gamma};Efficiency", "pizero_opening_angle", {.59,.57,.89,.85} },
					 { "True Neutrino Energy", kTrueNuEn, Binning::Simple(24,0,3), ";E_{#nu} (GeV);Events", "nu_en", {.59,.57,.89,.85} },
};

std::vector<Plot<SpillVar>> triggerEffPlots = { { "Pi0 Energy", kPiZeroTrueEnergy, Binning::Simple(30,0,1.5), ";True E_{#pi^{0}};Efficiency", "pizero_true_energy", {.59,.57,.89,.75} },
					 { "Pi0 Opening Angle", kPiZeroPhotonOpeningAngle, Binning::Simple(30,0,180), ";True #theta_{#gamma#gamma};Efficiency", "pizero_opening_angle", {.59,.65,.89,.83} },
					 { "True Neutrino Energy", kTrueNuEn, Binning::Simple(24,0,3), ";E_{#nu} (GeV);Events", "nu_en", {.59,.57,.89,.75} },
};

std::vector<Plot<SpillVar>> triggerEffPlotsNuE = { { "Pi0 Energy", kPiZeroTrueEnergy, Binning::Simple(30,0,1.5), ";True E_{#pi^{0}};Efficiency", "pizero_true_energy", {.59,.57,.89,.75} },
						   { "Pi0 Opening Angle", kPiZeroPhotonOpeningAngle, Binning::Simple(30,0,180), ";True #theta_{#gamma#gamma};Efficiency", "pizero_opening_angle", {.59,.65,.89,.83} },
						   { "True Neutrino Energy", kTrueNuEn, Binning::Simple(25,0,5), ";E_{#nu} (GeV);Events", "nu_en", {.59,.57,.89,.75} },
};
					  
