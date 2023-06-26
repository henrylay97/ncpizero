const SpillCut kCRTHitVeto([](const caf::SRSpillProxy *sp) {
    for(auto const &hit : sp->crt_hits)
      {
        if(hit.t1 > -2 && hit.t1 < 3.6)
          return false;
      }
    return true;
  });

const SpillCut kCRTTrackVeto([](const caf::SRSpillProxy *sp) {
    for(auto const &track : sp->crt_tracks)
      {
        if(track.time > -2 && track.time < 3.6)
          return false;
      }
    return true;
  });

const SpillCut kCRTHitVetoTight([](const caf::SRSpillProxy *sp) {
    for(auto const &hit : sp->crt_hits)
      {
        if(hit.t1 > 0 && hit.t1 < 1.6)
          return false;
      }
    return true;
  });

const SpillCut kCRTTrackVetoTight([](const caf::SRSpillProxy *sp) {
    for(auto const &track : sp->crt_tracks)
      {
        if(track.time > 0 && track.time < 1.6)
          return false;
      }
    return true;
  });

const std::vector<CutDef> ncpizero_cuts = { {"No Cuts", "no_cuts", kNoSpillCut},
                                            {"CRT Hit Veto", "crt_hit_veto", kCRTHitVeto},
                                            {"CRT Track Veto", "crt_track_veto", kCRTTrackVeto},
                                            {"All", "all", kCRTHitVeto && kCRTTrackVeto},
                                            {"CRT Hit Veto Tight", "crt_hit_veto_tight", kCRTHitVetoTight},
                                            {"CRT Track Veto Tight", "crt_track_veto_tight", kCRTTrackVetoTight},
                                            {"All Tight", "all_tight", kCRTHitVetoTight && kCRTTrackVetoTight},
};
