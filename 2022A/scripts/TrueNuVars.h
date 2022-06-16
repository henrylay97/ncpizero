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

std::vector<Plot> nuPlots = { { "True Neutrino Energy", kTrueNuEn, Binning::Simple(12,0,3), ";E_{#nu} (GeV)", "nu_en", {.31,.2,.55,.35} },
			      { "Bjorken X", kTrueNuBjorkenX, Binning::Simple(10,0,1), ";Bjorken X", "bjorken_x", {.29,.22,.54,.37} },
			      { "Inelasticity Y", kTrueNuInelasticityY, Binning::Simple(10,0,1), ";Inelasticity Y", "inelasticity_y", {.37,.22,.62,.37} },
			      { "Momentum Transfer", kTrueNuQ2, Binning::Simple(10,0,1), ";Q^{2} (GeV^{2})", "q2", {.29,.22,.54,.37} },
			      { "Lepton Momentum", kTrueLeptonP, Binning::Simple(10,0,5), ";p_{l} (GeV)", "lepton_mom", {.43, .4, .68, .55} },
			      { "Lepton Angle", kTrueLeptonAngle, Binning::Simple(12,0,180), ";#theta_{#nu l} (#circ)", "lepton_angle", {.27,.22,.52,.37} }
};
