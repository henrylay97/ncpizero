#include "TVector3.h"

const ParticleVar kTrueEnergy([](const caf::SRParticleProxy* prt) {
    return prt->genE;
  });

const ParticleVar kTrueTheta([](const caf::SRParticleProxy* prt) {
    auto const& genp = prt->genp;
    TVector3 genpvec = TVector3(genp.x, genp.y, genp.z);

    return TMath::RadToDeg() * genpvec.Theta();
  });

const ParticleVar kTruePhi([](const caf::SRParticleProxy* prt) {
    auto const& genp = prt->genp;
    TVector3 genpvec = TVector3(genp.x, genp.y, genp.z);

    return TMath::RadToDeg() * genpvec.Phi();
  });

const ParticleVar kTrueMomentum([](const caf::SRParticleProxy* prt) {
    auto const& genp = prt->genp;
    TVector3 genpvec = TVector3(genp.x, genp.y, genp.z);

    return genpvec.Mag();
  });

const ParticleCut kPrimaryMuonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;
    
    return prt->pdg == 13;
  });

const ParticleCut kPrimaryElectronCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;

    return prt->pdg == 11;
  });

const ParticleCut kPrimaryChargedPionCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;

    return abs(prt->pdg) == 211;
  });

const ParticleCut kPrimaryNeutralPionCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;

    return prt->pdg == 111;
  });

const ParticleCut kPrimaryPhotonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;

    return prt->pdg == 22;
  });

const ParticleCut kPrimaryProtonCut([](const caf::SRParticleProxy* prt) {
    if(prt->parent != 10000000) return false;

    return prt->pdg == 2212;
  });

std::vector<Plot<ParticleVar>> particlePlots = { { "True Energy", kTrueEnergy, Binning::Simple(24,0,3), ";E (GeV)", "energy", {.59,.57,.89,.85} },
						 { "True Momentum", kTrueMomentum, Binning::Simple(24,0,3), ";p (GeV/c)", "momentum", {.59,.57,.89,.85} },
						 { "True Theta", kTrueTheta, Binning::Simple(36,0,180), ";#theta(#circ)", "theta", {.59,.57,.89,.85} },
						 { "True Phi", kTruePhi, Binning::Simple(36,-180,180), ";#phi(#circ)", "phi", {.59,.57,.89,.85} },
};
