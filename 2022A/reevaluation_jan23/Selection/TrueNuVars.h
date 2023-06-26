#include "TVector3.h"

const SpillVar kTrueNuEn([](const caf::SRSpillProxy* sp) -> float {
    return sp->mc.nu[kBestNuID(sp)].E;
  });

const SpillVar kTrueNuBjorkenX([](const caf::SRSpillProxy* sp) -> float {
    return sp->mc.nu[kBestNuID(sp)].bjorkenX;
  });

const SpillVar kTrueNuInelasticityY([](const caf::SRSpillProxy* sp) -> float {
    return sp->mc.nu[kBestNuID(sp)].inelasticityY;
  });

const SpillVar kTrueNuQ2([](const caf::SRSpillProxy* sp) -> float {
    return sp->mc.nu[kBestNuID(sp)].Q2;
  });

const SpillVar kTrueLeptonP([](const caf::SRSpillProxy* sp) -> float {
    auto const& nu = sp->mc.nu[kBestNuID(sp)];
    return TVector3(nu.prim[0].genp.x, nu.prim[0].genp.y, nu.prim[0].genp.z).Mag();
  });

const SpillVar kTrueLeptonAngle([](const caf::SRSpillProxy* sp) -> float {
    auto const& nu = sp->mc.nu[kBestNuID(sp)];
    const TVector3 lepDir = TVector3(nu.prim[0].genp.x, nu.prim[0].genp.y, nu.prim[0].genp.z);
    const TVector3 nuDir  = TVector3(nu.momentum.x, nu.momentum.y, nu.momentum.z);

    return TMath::RadToDeg() * nuDir.Angle(lepDir);
  });

std::vector<Plot<SpillVar>> nuPlots = { { "True Neutrino Energy", kTrueNuEn, Binning::Simple(32,0,4), ";E_{#nu} (GeV);Events", "nu_en", {.59,.57,.89,.85} },
					{ "Bjorken X", kTrueNuBjorkenX, Binning::Simple(20,0,1), ";Bjorken X;Events", "bjorken_x",  {.59,.57,.89,.85} },
					{ "Inelasticity Y", kTrueNuInelasticityY, Binning::Simple(20,0,1), ";Inelasticity Y;Events", "inelasticity_y",  {.59,.57,.89,.85} },
					{ "Momentum Transfer", kTrueNuQ2, Binning::Simple(20,0,1), ";Q^{2} (GeV^{2});Events", "q2",  {.59,.57,.89,.85} },
					{ "Lepton Momentum", kTrueLeptonP, Binning::Simple(24,0,3), ";p_{l} (GeV);Events", "lepton_mom", {.59,.57,.89,.85} },
					{ "Lepton Angle", kTrueLeptonAngle, Binning::Simple(24,0,180), ";#theta_{#nu l} (#circ);Events", "lepton_angle", {.59,.57,.89,.85} }
};
