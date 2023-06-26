const SpillMultiVar kNuEnSignal([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> nuEn;

    for(auto const& nu : sp->mc.nu)
      {
	if(PtInVolAbsX(nu.position, fvndpizero) && nu.isnc)
	  {
	    unsigned npizero = 0;
	    for(auto const& prim : nu.prim)
	      if(prim.pdg == 111)
		++npizero;

	    if(npizero > 0)
	      nuEn.push_back(nu.E);
	  }
      }

    return nuEn;
  });

Plot<SpillMultiVar> nuEnSignalPlot = { "True Neutrino Energy", kNuEnSignal, Binning::Simple(32,0,4), ";E_{#nu} (GeV);Slices", "nu_en_signal", {.59,.57,.89,.85} };

const Var kSlcCounter([](const caf::SRSliceProxy *slc) -> double {
    return 1.;
  });

Plot<Var> slcCounterPlot = { "Slc Counter", kSlcCounter, Binning::Simple(10,0,5), ";Slice Counter;Slices", "slc_counter", {.59,.57,.89,.85} };

const Var kTrueNuEn([](const caf::SRSliceProxy *slc) -> double {
    return slc->truth.E;
  });

const Var kTrueNuBjorkenX([](const caf::SRSliceProxy* slc) -> float {
    return slc->truth.bjorkenX;
  });

const Var kTrueNuInelasticityY([](const caf::SRSliceProxy* slc) -> float {
    return slc->truth.inelasticityY;
  });

const Var kTrueNuQ2([](const caf::SRSliceProxy* slc) -> float {
    return slc->truth.Q2;
  });

const Var kTrueLeptonP([](const caf::SRSliceProxy* slc) -> float {
    auto const& nu = slc->truth;
    return TVector3(nu.prim[0].genp.x, nu.prim[0].genp.y, nu.prim[0].genp.z).Mag();
  });

const Var kTrueLeptonAngle([](const caf::SRSliceProxy* slc) -> float {
    auto const& nu = slc->truth;
    const TVector3 lepDir = TVector3(nu.prim[0].genp.x, nu.prim[0].genp.y, nu.prim[0].genp.z);
    const TVector3 nuDir  = TVector3(nu.momentum.x, nu.momentum.y, nu.momentum.z);

    return TMath::RadToDeg() * nuDir.Angle(lepDir);
  });

std::vector<Plot<Var>> nuPlots = { { "True Neutrino Energy", kTrueNuEn, Binning::Simple(32,0,4), ";E_{#nu} (GeV);Slices", "nu_en", {.59,.57,.84,.85} },
				   { "Bjorken X", kTrueNuBjorkenX, Binning::Simple(20,0,1), ";Bjorken X;Slices", "bjorken_x",  {.59,.57,.84,.85} },
				   { "Inelasticity Y", kTrueNuInelasticityY, Binning::Simple(20,0,1), ";Inelasticity Y;Slices", "inelasticity_y",  {.59,.57,.84,.85} },
				   { "Momentum Transfer", kTrueNuQ2, Binning::Simple(20,0,1), ";Q^{2} (GeV^{2});Slices", "q2",  {.59,.57,.84,.85} },
				   { "Lepton Momentum", kTrueLeptonP, Binning::Simple(24,0,3), ";p_{l} (GeV);Slices", "lepton_mom", {.59,.57,.84,.85} },
				   { "Lepton Angle", kTrueLeptonAngle, Binning::Simple(24,0,180), ";#theta_{#nu l} (#circ);Slices ", "lepton_angle", {.59,.57,.84,.85} }
};
