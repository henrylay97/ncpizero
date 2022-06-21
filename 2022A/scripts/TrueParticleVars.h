#include "TVector3.h"

const ParticleCut kDepositsEnergy([](const caf::SRParticleProxy* prt) {
    auto const& plane = prt->plane;
    double en = plane[0][0].visE + plane[0][1].visE + plane[0][2].visE
      + plane[1][0].visE + plane[1][1].visE + plane[1][2].visE;

    return en > 0.;
  });

const ParticleVar kDepositedEnergy([](const caf::SRParticleProxy* prt) {
    auto const& plane = prt->plane;
    double en = plane[0][0].visE + plane[0][1].visE + plane[0][2].visE
      + plane[1][0].visE + plane[1][1].visE + plane[1][2].visE;

    return en;
  });

const ParticleVar kTrueEnergy([](const caf::SRParticleProxy* prt) {
    /* if(prt->parent < 20000000 && prt->start_process == 0 && prt->pdg==13 && kDepositsEnergy(prt)  */
    /*    && prt->length > std::numeric_limits<double>::epsilon()) */
    /*   std::cout << prt->startE << " " << prt->genE << " "  */
    /* 		<< prt->length << " " << kDepositedEnergy(prt)  */
    /* 		<< "\n\tgen: " << prt->gen.x << " " << prt->gen.y << " " << prt->gen.z */
    /* 		<< "\n\tstart: " << prt->start.x << " " << prt->start.y << " " << prt->start.z << " " << prt->start_process */
    /* 		<< "\n\tend: " << prt->end.x << " " << prt->end.y << " " << prt->end.z << " " << prt->end_process */
    /* 		<< std::endl; */

    return prt->startE;
  });

const ParticleVar kTrueTheta([](const caf::SRParticleProxy* prt) {
    auto const& startp = prt->startp;
    TVector3 startpvec = TVector3(startp.x, startp.y, startp.z);

    return TMath::RadToDeg() * startpvec.Theta();
  });

const ParticleVar kTrueCosTheta([](const caf::SRParticleProxy* prt) {
    auto const& startp = prt->startp;
    TVector3 startpvec = TVector3(startp.x, startp.y, startp.z);

    return TMath::Cos(startpvec.Theta());
  });

const ParticleVar kTruePhi([](const caf::SRParticleProxy* prt) {
    auto const& startp = prt->startp;
    TVector3 startpvec = TVector3(startp.x, startp.y, startp.z);

    return TMath::RadToDeg() * startpvec.Phi();
  });

const ParticleVar kTrueMomentum([](const caf::SRParticleProxy* prt) {
    auto const& startp = prt->startp;
    TVector3 startpvec = TVector3(startp.x, startp.y, startp.z);

    return startpvec.Mag();
  });

const ParticleCut kPrimaryMuonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;
    
    return prt->pdg == 13;
  });

const ParticleCut kCosmicMuonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent < 20000000 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon())
      return false;
    
    return prt->pdg == 13;
  });

const ParticleCut kDirtMuonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || PtInVolAbsX(prt->start, avnd))
      return false;
    
    return prt->pdg == 13;
  });

const ParticleCut kPrimaryElectronCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;

    return prt->pdg == 11;
  });

const ParticleCut kPrimaryChargedPionCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;

    return abs(prt->pdg) == 211;
  });

const ParticleCut kPrimaryNeutralPionCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;

    return prt->pdg == 111;
  });

const ParticleCut kPrimaryPhotonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;

    return prt->pdg == 22;
  });

const ParticleCut kPrimaryProtonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent > 19999999 || prt->start_process != 0 || !kDepositsEnergy(prt) ||
       prt->length < std::numeric_limits<double>::epsilon() || !PtInVolAbsX(prt->start, avnd))
      return false;

    return prt->pdg == 2212;
  });

std::vector<Plot<ParticleVar>> particlePlots = { { "True Energy", kTrueEnergy, Binning::Simple(24,0,3), ";E (GeV)", "energy", {.59,.57,.89,.85} },
						 { "True Momentum", kTrueMomentum, Binning::Simple(24,0,3), ";p (GeV/c)", "momentum", {.59,.57,.89,.85} },
						 { "True Theta", kTrueTheta, Binning::Simple(36,0,180), ";#theta(#circ)", "theta", {.59,.57,.89,.85} },
						 { "True Cos Theta", kTrueCosTheta, Binning::Simple(40,-1,1), ";cos(#theta)", "cos_theta", {.59,.57,.89,.85} },
						 { "True Phi", kTruePhi, Binning::Simple(36,-180,180), ";#phi(#circ)", "phi", {.59,.57,.89,.85} },
};
