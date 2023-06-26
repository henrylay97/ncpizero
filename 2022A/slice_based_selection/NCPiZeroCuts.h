const Cut kNotClearCosmic([](const caf::SRSliceProxy* slc) {
    return !slc->is_clear_cosmic;
  });

const Cut kFV([](const caf::SRSliceProxy* slc) {
    if(isnan(slc->vertex.x))
      return false;

    return PtInVolAbsX(slc->vertex, fvndpizero);
  });

const Cut kCRUMBSCut([](const caf::SRSliceProxy *slc) {
    if(isnan(slc->crumbs_result.score))
      return false;

    return slc->crumbs_result.score > 0;
  });

const Cut kOptimalCRUMBSCut([](const caf::SRSliceProxy *slc) {
    if(isnan(slc->crumbs_result.score))
      return false;

    return slc->crumbs_result.score > -0.025;
  });

const Cut kHasNoDazzleMuons([](const caf::SRSliceProxy *slc) {
    return kNDazzleMuons(slc) == 0;
  });

const Cut kHasNoChi2Muons([](const caf::SRSliceProxy *slc) {
    return kNChi2Muons(slc) == 0;
  });

const Cut kHasAtLeastTwoShowers([](const caf::SRSliceProxy *slc) {
    return slc->reco.nshw > 1;
  });

const Cut kHasAtLeastTwoRazzlePhotons([](const caf::SRSliceProxy *slc) {
    return kNRazzlePhotons(slc) > 1;
  });

const Cut kHasNoRazzleElectrons([](const caf::SRSliceProxy *slc) {
    return kNRazzleElectrons(slc) == 0;
  });

const Cut kHasNoRazzleOther([](const caf::SRSliceProxy *slc) {
    return kNRazzleOther(slc) == 0;
  });

const Cut kHasAtLeastTwoPFPs([](const caf::SRSliceProxy *slc) {
    return kNPFPs(slc) > 1;
  });

const Cut kPhotonCandidate1dEdxCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1dEdx(slc) > 3;
  });

const Cut kPhotonCandidate2dEdxCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate2dEdx(slc) > 3;
  });

const Cut kPhotonCandidate1RazzleElectronCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1RazzleElectronScore(slc) < 0.95;
  });

const Cut kPhotonCandidate2RazzleElectronCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate2RazzleElectronScore(slc) < 0.95;
  });

const Cut kShowersRazzleElectronCut([](const caf::SRSliceProxy *slc) {
    for(auto const& shw : slc->reco.shw)
      {
	if(shw.razzle.electronScore > 0.95)
	  return false;
      }

    return true;
  });

const Cut kPhotonCandidate1RazzlePhotonCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1RazzlePhotonScore(slc) > 0.2;
  });

const Cut kOptimalPhotonCandidate1RazzlePhotonCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1RazzlePhotonScore(slc) > 0.05;
  });

const Cut kPhotonCandidate2RazzlePhotonCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate2RazzlePhotonScore(slc) > 0.2;
  });

const Cut kOptimalPhotonCandidate2RazzlePhotonCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1RazzlePhotonScore(slc) > 0;
  });

const Cut kShowersRazzlePhotonCut([](const caf::SRSliceProxy *slc) {
    for(auto const& shw : slc->reco.shw)
      {
	if(shw.razzle.photonScore < 0.2)
	  return false;
      }

    return true;
  });

const Cut kPhotonCandidate1RazzleOtherCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate1RazzleOtherScore(slc) < 0.8;
  });

const Cut kPhotonCandidate2RazzleOtherCut([](const caf::SRSliceProxy *slc) {
    return kPhotonCandidate2RazzleOtherScore(slc) < 0.8;
  });

const Cut kShowersRazzleOtherCut([](const caf::SRSliceProxy *slc) {
    for(auto const& shw : slc->reco.shw)
      {
	if(shw.razzle.otherScore > 0.8)
	  return false;
      }

    return true;
  });

const Cut kTracksDazzleMuonCut([](const caf::SRSliceProxy *slc) {
    for(auto const& trk : slc->reco.trk)
      {
	if(trk.dazzle.muonScore > 0.6)
	  return false;
      }

    return true;
  });

const Cut kOptimalTracksDazzleMuonCut([](const caf::SRSliceProxy *slc) {
    for(auto const& trk : slc->reco.trk)
      {
	if(trk.dazzle.muonScore > 0.0125)
	  return false;
      }

    return true;
  });

const Cut kTracksLengthCut([](const caf::SRSliceProxy *slc) {
    for(auto const& trk : slc->reco.trk)
      {
	if(trk.len > 50)
	  return false;
      }

    return true;
  });

const FidVol containmentvolume { -195, +195, -195, +195, +5, +495};

const Cut kShowersContainmentCut([](const caf::SRSliceProxy *slc) {
    for(auto const& shw : slc->reco.shw)
      {
	if(!PtInVol(shw.end, containmentvolume))
	  return false;
      }
    
    return true;
  });

const Cut kTracksContainmentCut([](const caf::SRSliceProxy *slc) {
    for(auto const& trk : slc->reco.trk)
      {
	if(!PtInVol(trk.end, containmentvolume))
	  return false;
      }
    
    return true;
  });

const Cut kCosCoMDecayAngleCut([](const caf::SRSliceProxy *slc) {
    return kCosCoMDecayAngle(slc) < 0.99;
  });

const Cut kCosCoMDecayAngleHarshCut([](const caf::SRSliceProxy *slc) {
    return kCosCoMDecayAngle(slc) < 0.975;
  });

std::vector<CutDef<Cut>> ncpizero_cuts = { { "No Cut", "no_cut", kNoCut },
					   { "Not Clear Cosmic", "not_clear_cosmic", kNotClearCosmic },
					   { "FV", "fv", kFV },
					   { "CRUMBS", "crumbs_cut", kCRUMBSCut },
					   { "Has No Dazzle Muons", "has_no_dazzle_muons", kHasNoDazzleMuons },
					   { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
};

const Cut kCRUMBSCutCumulative            = kNoCut && kNotClearCosmic && kFV && kCRUMBSCut;
const Cut kHasNoDazzleMuonsCumulative     = kCRUMBSCutCumulative && kHasNoDazzleMuons;
const Cut kHasAtLeastTwoShowersCumulative = kHasNoDazzleMuonsCumulative && kHasAtLeastTwoShowers;

std::vector<CutDef<Cut>> ncpizero_pfp_cuts = { { "Has At Least 2 PFPs", "has_two_pfps", kHasNoDazzleMuonsCumulative && kHasAtLeastTwoPFPs },
};

std::vector<CutDef<Cut>> ncpizero_razzle_id_cuts = { { "Has At Least 2 Razzle Photons", "has_two_razzle_photons", kHasAtLeastTwoShowersCumulative && kHasAtLeastTwoRazzlePhotons },
						     { "Has No Razzle Electrons", "has_no_razzle_electrons", kHasNoRazzleElectrons },
						     { "Has No Razzle Other", "has_no_razzle_other", kHasNoRazzleOther },
};

std::vector<CutDef<Cut>> ncpizero_razzle_photon_candidates_value_cuts = { { "Photon Candidate 1 Razzle Photon Cut", "photon_candidate_1_razzle_photon_cut", kHasAtLeastTwoShowersCumulative && kPhotonCandidate1RazzlePhotonCut },
									  { "Photon Candidate 2 Razzle Photon Cut", "photon_candidate_2_razzle_photon_cut", kPhotonCandidate2RazzlePhotonCut },
									  { "Photon Candidate 1 Razzle Electron Cut", "photon_candidate_1_razzle_electron_cut", kPhotonCandidate1RazzleElectronCut },
									  { "Photon Candidate 2 Razzle Electron Cut", "photon_candidate_2_razzle_electron_cut", kPhotonCandidate2RazzleElectronCut },
									  { "Photon Candidate 1 Razzle Other Cut", "photon_candidate_1_razzle_other_cut", kPhotonCandidate1RazzleOtherCut },
									  { "Photon Candidate 2 Razzle Other Cut", "photon_candidate_2_razzle_other_cut", kPhotonCandidate2RazzleOtherCut },
};

std::vector<CutDef<Cut>> ncpizero_razzle_value_cuts = { { "Showers Razzle Photon Cut", "showers_razzle_photon_cut", kHasAtLeastTwoShowersCumulative && kShowersRazzlePhotonCut },
							{ "Showers Razzle Electron Cut", "showers_razzle_electron_cut", kShowersRazzleElectronCut },
							{ "Showers Razzle Other Cut", "showers_razzle_other_cut", kShowersRazzleOtherCut },
};

std::vector<CutDef<Cut>> ncpizero_shower_dEdx_value_cuts = { { "Photon Candidate 1 dE/dx Cut", "photon_candidate_1_dEdx_cut", kHasAtLeastTwoShowersCumulative && kPhotonCandidate1dEdxCut },
							     { "Photon Candidate 2 dE/dx Cut", "photon_candidate_2_dEdx_cut", kPhotonCandidate2dEdxCut },
};

std::vector<CutDef<Cut>> ncpizero_muon_rej_cuts = { { "Tracks Dazzle Muon Cut", "tracks_dazzle_muon_cut", kCRUMBSCutCumulative && kTracksDazzleMuonCut },
						    { "Tracks Length Cut", "tracks_length_cut", kTracksLengthCut },
						    { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
};

std::vector<CutDef<Cut>> ncpizero_chi2_muon_rej_cuts = { { "Has No Chi2 Muons", "has_no_chi2_muons", kCRUMBSCutCumulative && kHasNoChi2Muons },
							 { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
};

/* std::vector<CutDef<Cut>> ncpizero_containment_cuts = { { "All Tracks Contained", "all_tracks_contained", kCRUMBSCutCumulative && kTracksContainmentCut }, */
/* 						       //{ "All Showers Contained", "all_showers_contained", kShowersContainmentCut }, */
/* 						       //{ "Tracks Dazzle Muon Cut", "tracks_dazzle_muon_cut", kTracksDazzleMuonCut }, */
/* 						       { "Has No Dazzle Muons", "has_no_dazzle_muons", kHasNoDazzleMuons }, */
/* 						       { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers }, */
/* }; */

std::vector<CutDef<Cut>> ncpizero_effpur_optimal_cuts = { { "No Cut", "no_cut", kNoCut },
							  { "Not Clear Cosmic", "not_clear_cosmic", kNotClearCosmic },
							  { "FV", "fv", kFV },
							  { "CRUMBS", "crumbs_cut", kOptimalCRUMBSCut },
							  { "Dazzle Muon Score Cut", "tracks_dazzle_muon_score_cut", kOptimalTracksDazzleMuonCut },
							  { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
							  { "Photon Candidate 1 Razzle Photon Score Cut", "photon_candidate_1_razzle_photon_score_cut", kOptimalPhotonCandidate1RazzlePhotonCut },
							  { "Photon Candidate 2 Razzle Photon Score Cut", "photon_candidate_2_razzle_photon_score_cut", kOptimalPhotonCandidate2RazzlePhotonCut },
};

std::vector<CutDef<Cut>> ncpizero_effpur_optimal_cuts_efficiency_plot = { { "No Cut", "no_cut", kNoCut, kGray+2 },
									  { "Pre-Selection", "pre_selection", kNotClearCosmic && kFV, kRed+2 },
									  { "Cosmic Rejection", "cosmic_rejection", kNotClearCosmic && kFV && kOptimalCRUMBSCut, kBlue + 2 },
									  { "Muon Rejection", "muon_rejection", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut, kGreen + 2 },
									  { "Photon Selection", "photon_selection", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut && kHasAtLeastTwoShowers && kOptimalPhotonCandidate1RazzlePhotonCut && kOptimalPhotonCandidate2RazzlePhotonCut, kMagenta + 2 },
};

const Cut kOptimalCumulative = kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut && kHasAtLeastTwoShowers &&
  kOptimalPhotonCandidate1RazzlePhotonCut && kOptimalPhotonCandidate2RazzlePhotonCut;

std::vector<CutDef<Cut>> ncpizero_effpur_optimal_cuts_one_pot_plots = { { "No Cut", "no_cut", kNoCut },
									{ "Full Selection", "full_selection", kOptimalCumulative },
};

std::vector<CutDef<Cut>> ncpizero_cos_com_cuts = { { "Photon Candidate 2 Razzle Photon Score Cut", "photon_candidate_2_razzle_photon_score_cut", kOptimalCumulative },
						   { "Cos CoM Decay Angle Cut", "cos_com_decay_angle_cut", kCosCoMDecayAngleCut },
						   { "Cos CoM Decay Angle Harsh Cut", "cos_com_decay_angle_harsh_cut", kCosCoMDecayAngleHarshCut },
};

std::vector<CutDef<Cut>> ncpizero_containment_cuts = { { "All Tracks Contained", "all_tracks_contained", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kTracksContainmentCut },
						       //{ "All Showers Contained", "all_showers_contained", kShowersContainmentCut },
						       { "Dazzle Muon Score Cut", "tracks_dazzle_muon_score_cut", kOptimalTracksDazzleMuonCut },
						       { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
						       { "Photon Candidate 1 Razzle Photon Score Cut", "photon_candidate_1_razzle_photon_score_cut", kOptimalPhotonCandidate1RazzlePhotonCut },
						       { "Photon Candidate 2 Razzle Photon Score Cut", "photon_candidate_2_razzle_photon_score_cut", kOptimalPhotonCandidate2RazzlePhotonCut },
};

std::vector<CutDef<Cut>> ncpizero_effpur_optimal_razzleid_cuts = { { "Dazzle Muon Score Cut", "tracks_dazzle_muon_score_cut", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut },
								   { "Has At Least 2 Showers", "has_two_shw", kHasAtLeastTwoShowers },
								   { "Has At Least 2 Razzle Photons", "has_two_razzle_photons", kHasAtLeastTwoRazzlePhotons }
};

std::vector<CutDef<Cut>> ncpizero_effpur_optimal_razzleid_cuts_efficiency_plot = { { "No Cut", "no_cut", kNoCut, kGray+2 },
										   { "Pre-Selection", "pre_selection", kNotClearCosmic && kFV, kRed+2 },
										   { "Cosmic Rejection", "cosmic_rejection", kNotClearCosmic && kFV && kOptimalCRUMBSCut, kBlue + 2 },
										   { "Muon Rejection", "muon_rejection", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut, kGreen + 2 },
										   { "Photon Selection", "photon_selection", kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut && kHasAtLeastTwoShowers && kHasAtLeastTwoRazzlePhotons, kMagenta + 2 },
};

const Cut kOptimalRazzleIDCumulative = kNotClearCosmic && kFV && kOptimalCRUMBSCut && kOptimalTracksDazzleMuonCut && kHasAtLeastTwoShowers && kHasAtLeastTwoRazzlePhotons;
