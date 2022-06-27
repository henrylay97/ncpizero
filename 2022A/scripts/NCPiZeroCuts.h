const SpillCut kPassesFlashTrig([](const caf::SRSpillProxy* sp) {
    return sp->pass_flashtrig;
  });

const SpillCut kHasSlc([](const caf::SRSpillProxy* sp) {
    return sp->nslc != 0;
  });

const SpillCut kHasNuSlc([](const caf::SRSpillProxy* sp) {
    for(auto const& slc : sp->slc)
      if(!slc.is_clear_cosmic) return true;

    return false;
  });

const SpillCut kHasNuFVSlc([](const caf::SRSpillProxy* sp) {
    for(auto const& slc : sp->slc)
      {
	if(slc.is_clear_cosmic) continue;

	if(PtInVolAbsX(slc.vertex, fvndAbs)) return true;
      }
    return false;
  });

const SpillCut kHasCRUMBSSlc([](const caf::SRSpillProxy* sp) {
    auto const& slc = sp->slc[kBestSlcID(sp)];

    if(isnan(slc.crumbs_result.score)) return false;

    return slc.crumbs_result.score > 0;
  });

const SpillCut kIsFV([](const caf::SRSpillProxy* sp) {
    auto const& slc = sp->slc[kBestSlcID(sp)];
    
    return PtInVolAbsX(slc.vertex, fvndAbs);
  });


const SpillCut kHasNoTrks([](const caf::SRSpillProxy* sp) {
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return slc.reco.ntrk == 0;
  });

const SpillCut kHasNoDazzleMuons([](const caf::SRSpillProxy* sp) {
    return kNDazzleMuons(sp) == 0;
  });

const SpillCut kHasNoDazzlePions([](const caf::SRSpillProxy* sp) {
    return kNDazzlePions(sp) == 0;
  });

const SpillCut kHasNoDazzleOther([](const caf::SRSpillProxy* sp) {
    return kNDazzleOther(sp) == 0;
  });

const SpillCut kHasAtLeast2Shws([](const caf::SRSpillProxy* sp) {
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return slc.reco.nshw > 1;
  });

std::vector<CutDef> ncpizero_cuts = { { "No Cut", "no_cut", kNoSpillCut },
				      //				      { "Passes Flash Trigger", "pass_flash_trig", kPassesFlashTrig },
				      { "Has Slc", "has_slc", kHasSlc },
				      { "Has Nu Slc", "has_nu_slc", kHasNuSlc },
				      { "Has Nu FV Slc", "has_nu_fv_slc", kHasNuFVSlc },
				      { "Has CRUMBS Slc", "has_crumbs_slc", kHasCRUMBSSlc },
				      { "Is FV", "is_fv", kIsFV },
				      { "Has No Dazzle Muons", "has_no_dazzle_muons", kHasNoDazzleMuons },
				      { "Has No Dazzle Pions", "has_no_dazzle_pions", kHasNoDazzlePions },
				      { "Has No Dazzle Other", "has_no_dazzle_other", kHasNoDazzleOther },
				      { "Has At Least 2 Showers", "has_two_shw", kHasAtLeast2Shws },
};
