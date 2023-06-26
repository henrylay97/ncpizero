const Var kPiZeroID([](const caf::SRSliceProxy* slc) -> unsigned {
    if(!kSignal(slc))
      return 999999;

    std::vector<std::pair<int, double>> pizeros;

    for(int i = 0; i < slc->truth.nprim; ++i) {
      auto const& prim = slc->truth.prim[i];
      if(prim.pdg == 111) 
	pizeros.push_back({i, prim.genE});
    }

    if(pizeros.size() == 0)
      return 999999;

    std::sort(pizeros.begin(), pizeros.end(),
	      [](auto& a, auto& b)
	      { return a.second > b.second; });

    return pizeros[0].first;
  });
const Var kPiZeroTrueEnergy([](const caf::SRSliceProxy* slc) -> double {
    if(!kSignal(slc)) 
      return -1.;
    
    return slc->truth.prim[kPiZeroID(slc)].startE;
  });

std::vector<Plot<Var>> effPlots = { { "True Pi0 Energy", kPiZeroTrueEnergy, Binning::Simple(30,0,1.5), ";True E_{#pi^{0}};Efficiency", "pizero_true_energy", {.25,.76,.89,.85} },
				    { "True Neutrino Energy", kTrueNuEn, Binning::Simple(24,0,3), ";True E_{#nu} (GeV);Efficiency", "nu_en", {.25,.76,.89,.85} },
};
