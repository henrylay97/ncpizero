const SpillVar kDummyVar([](const caf::SRSpillProxy* sp) -> float {
    return .5;
  });

Plot<SpillVar> DummyPlot = { "Dummy Plot", kDummyVar, Binning::Simple(1,0,1), ";Dummy Var;Events", "dummy_var", {.59,.57,.89,.85}};
