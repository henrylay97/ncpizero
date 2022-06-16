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
