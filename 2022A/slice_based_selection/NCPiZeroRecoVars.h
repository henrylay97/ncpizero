#include "TVector3.h"

const Var kIsClearCosmicVar([](const caf::SRSliceProxy* slc) -> bool {
    return slc->is_clear_cosmic;
  });

const Var kIsFVVar([](const caf::SRSliceProxy *slc) -> bool {
    if(isnan(slc->vertex.x))
      return false;

    return PtInVolAbsX(slc->vertex, fvndpizero);
  });

const Var kCRUMBSScore([](const caf::SRSliceProxy *slc) -> double {
    if(slc->is_clear_cosmic || isnan(slc->crumbs_result.score))
      return -1.5;

    return slc->crumbs_result.score;
  });

Plot<Var> CRUMBSScorePlot = { "CRUMBS Score", kCRUMBSScore, Binning::Simple(42, -1.5, .6),
			      ";CRUMBS Score; Slices", "crumbs_score", {.22, .57, .52, .85} };

const Var kNTracks([](const caf::SRSliceProxy *slc) -> unsigned {
    return slc->reco.ntrk;
  });

const Var kNShowers([](const caf::SRSliceProxy *slc) -> unsigned {
    return slc->reco.nshw;
  });

const Var kNPFPs = kNTracks + kNShowers;
    
const Var kNStubs([](const caf::SRSliceProxy *slc) -> unsigned {
    return slc->reco.nstub;
  });

const Var kNDazzleMuons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      if(trk.dazzle.pdg == 13)
	++i;
    
    return i;
  });

const Var kNDazzlePions([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      if(trk.dazzle.pdg == 211)
	++i;
    
    return i;
  });

const Var kNDazzleProtons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      if(trk.dazzle.pdg == 2212)
	++i;
    
    return i;
  });

const Var kNDazzleOther([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      if(trk.dazzle.pdg == 0)
	++i;
    
    return i;
  });

const Var kNChi2Muons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      {
	auto const& chi2 = trk.chi2pid[trk.bestplane];
	
	std::vector<std::pair<int, float>> chi2s = { { 13, chi2.chi2_muon },
						     { 211, chi2.chi2_pion },
						     { 321, chi2.chi2_kaon },
						     { 2212, chi2.chi2_proton }
	};
	
	std::sort(chi2s.begin(), chi2s.end(),
		  [](auto const& a, auto const& b)
		  { return a.second < b.second; });

	if(chi2s[0].first == 13)
	  ++i;
      }

    return i;
  });

const Var kNChi2Pions([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      {
	auto const& chi2 = trk.chi2pid[trk.bestplane];
	
	std::vector<std::pair<int, float>> chi2s = { { 13, chi2.chi2_muon },
						     { 211, chi2.chi2_pion },
						     { 321, chi2.chi2_kaon },
						     { 2212, chi2.chi2_proton }
	};
	
	std::sort(chi2s.begin(), chi2s.end(),
		  [](auto const& a, auto const& b)
		  { return a.second < b.second; });

	if(chi2s[0].first == 211)
	  ++i;
      }

    return i;
  });

const Var kNChi2Kaons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      {
	auto const& chi2 = trk.chi2pid[trk.bestplane];
	
	std::vector<std::pair<int, float>> chi2s = { { 13, chi2.chi2_muon },
						     { 211, chi2.chi2_pion },
						     { 321, chi2.chi2_kaon },
						     { 2212, chi2.chi2_proton }
	};
	
	std::sort(chi2s.begin(), chi2s.end(),
		  [](auto const& a, auto const& b)
		  { return a.second < b.second; });

	if(chi2s[0].first == 321)
	  ++i;
      }

    return i;
  });

const Var kNChi2Protons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      {
	auto const& chi2 = trk.chi2pid[trk.bestplane];
	
	std::vector<std::pair<int, float>> chi2s = { { 13, chi2.chi2_muon },
						     { 211, chi2.chi2_pion },
						     { 321, chi2.chi2_kaon },
						     { 2212, chi2.chi2_proton }
	};
	
	std::sort(chi2s.begin(), chi2s.end(),
		  [](auto const& a, auto const& b)
		  { return a.second < b.second; });

	if(chi2s[0].first == 2212)
	  ++i;
      }

    return i;
  });

const Var kNRazzleElectrons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      if(shw.razzle.pdg == 11)
	++i;
    
    return i;
  });

const Var kNRazzlePhotons([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      if(shw.razzle.pdg == 22)
	++i;
    
    return i;
  });

const Var kNRazzleOther([](const caf::SRSliceProxy *slc) -> unsigned {
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      if(shw.razzle.pdg == 0)
	++i;
    
    return i;
  });

const Var kSummedSliceEnergy([](const caf::SRSliceProxy* slc) -> double {
    double en = 0.;

    for(auto const& trk : slc->reco.trk)
      en += trk.calo[trk.bestplane].ke * 1e-3;

    for(auto const& shw : slc->reco.shw)
      en += shw.bestplane_energy;

    return en;
  });

const Var kLongestTrkID([](const caf::SRSliceProxy* slc) -> int {
    if(kNTracks(slc) == 0)
      return -1.;

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& trk : slc->reco.trk)
      {
        list.push_back(std::pair<int, double>(i, trk.len));
        ++i;
      }

    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
                                           const std::pair<int, double> &y)
              { return x.second > y.second; });

    return list[0].first;
  });

const Var kLongestTrkLen([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -50.;

    return slc->reco.trk[kLongestTrkID(slc)].len;
  });

const Var kLongestTrkDazzleMuonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -.5;

    auto const& trk = slc->reco.trk[kLongestTrkID(slc)];

    return isnan(trk.dazzle.muonScore) ? -.5 : trk.dazzle.muonScore;
  });

const Var kLongestTrkDazzlePionScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -.5;

    auto const& trk = slc->reco.trk[kLongestTrkID(slc)];

    return isnan(trk.dazzle.pionScore) ? -.5 : trk.dazzle.pionScore;
  });

const Var kLongestTrkDazzleProtonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -.5;

    auto const& trk = slc->reco.trk[kLongestTrkID(slc)];

    return isnan(trk.dazzle.protonScore) ? -.5 : trk.dazzle.protonScore;
  });

const Var kLongestTrkDazzleOtherScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -.5;

    auto const& trk = slc->reco.trk[kLongestTrkID(slc)];

    return isnan(trk.dazzle.otherScore) ? -.5 : trk.dazzle.otherScore;
  });

const Var kHighestDazzleMuonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -5.;

    float max = -5.;

    for(auto const& trk : slc->reco.trk)
      {
	if(trk.dazzle.muonScore > max)
	  max = trk.dazzle.muonScore;
      }

    return max;
  });

Plot<Var> HighestDazzleMuonScorePlot = { "Highest Dazzle Muon Score", kHighestDazzleMuonScore, Binning::Simple(40,0,1), 
					 ";Highest Dazzle Muon Score;Slices", "highest_dazzle_muon_score",  {.42,.57,.72,.85} };

const Var kHighestRazzlePhotonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -5.;

    float max = -5.;

    for(auto const& shw : slc->reco.shw)
      {
	if(shw.razzle.photonScore > max)
	  max = shw.razzle.photonScore;
      }

    return max;
  });

const Var kSecondHighestRazzlePhotonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -5.;

    float max = -5.;

    for(auto const& shw : slc->reco.shw)
      {
	if(shw.razzle.photonScore > max)
	  max = shw.razzle.photonScore;
      }

    return max;
  });

const Var kLongestTrkPDGPlot([](const caf::SRSliceProxy* slc) -> double {
    if(kNTracks(slc) == 0)
      return -.5;

    const int pdg = slc->reco.trk[kLongestTrkID(slc)].truth.p.pdg;

    switch(pdg) {
    case 11:
      return 0.5;
    case -11:
      return 1.5;
    case 13:
      return 2.5;
    case -13:
      return 3.5;
    case 211:
      return 4.5;
    case -211:
      return 5.5;
    case 2212:
      return 6.5;
    case 22:
      return 7.5;
    default:
      return 8.5;
    }
  });

const Var kLeadingShwID([](const caf::SRSliceProxy* slc) -> int {
    if(kNShowers(slc) == 0)
      return -1;

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      {
        list.push_back(std::pair<int, double>(i, shw.bestplane_energy));
        ++i;
      }

    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
                                           const std::pair<int, double> &y)
              { return x.second > y.second; });

    return list[0].first;
  });

const Var kSubLeadingShwID([](const caf::SRSliceProxy* slc) -> int {
    if(kNShowers(slc) < 2)
      return -1;

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      {
        list.push_back(std::pair<int, double>(i, shw.bestplane_energy));
        ++i;
      }

    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
                                           const std::pair<int, double> &y)
              { return x.second > y.second; });

    return list[1].first;
  });

const Var kPhotonCandidate1ID([](const caf::SRSliceProxy* slc) -> int {
    if(kNShowers(slc) == 0)
      return -1;

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      {
        list.push_back(std::pair<int, double>(i, shw.razzle.photonScore));
        ++i;
      }

    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
                                           const std::pair<int, double> &y)
              { return x.second > y.second; });

    return list[0].first;
  });

const Var kPhotonCandidate2ID([](const caf::SRSliceProxy* slc) -> int {
    if(kNShowers(slc) < 2)
      return -1;

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc->reco.shw)
      {
        list.push_back(std::pair<int, double>(i, shw.razzle.photonScore));
        ++i;
      }

    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
                                           const std::pair<int, double> &y)
              { return x.second > y.second; });

    return list[1].first;
  });

const Var kPhotonCandidate1Energy([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.bestplane_energy;
  });

const Var kPhotonCandidate1dEdx([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return isinf(shw.bestplane_dEdx) ? -1. : shw.bestplane_dEdx;
  });

const Var kPhotonCandidate1CnvGap([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.conversion_gap;
  });

const Var kPhotonCandidate1Density([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;
    
    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.density;
  });

const Var kPhotonCandidate1Len([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.len;
  });

const Var kPhotonCandidate1OpenAngle([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return TMath::RadToDeg() * shw.open_angle;
  });

const Var kPhotonCandidate1CosmicDist([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.cosmicDist;
  });

const Var kPhotonCandidate1DensityGrad([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.selVars.densityGradient;
  });

const Var kPhotonCandidate1DensityGradPower([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.selVars.densityGradientPower;
  });

const Var kPhotonCandidate1TrkLength([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.selVars.trackLength;
  });

const Var kPhotonCandidate1TrkWidth([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return shw.selVars.trackWidth;
  });

const Var kPhotonCandidate1PDGPlot([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -.5;

    const int pdg = slc->reco.shw[kPhotonCandidate1ID(slc)].truth.p.pdg;

    switch(pdg) {
    case 11:
      return 0.5;
    case -11:
      return 1.5;
    case 13:
      return 2.5;
    case -13:
      return 3.5;
    case 211:
      return 4.5;
    case -211:
      return 5.5;
    case 2212:
      return 6.5;
    case 22:
      return 7.5;
    default:
      return 8.5;
    }
  });

const Var kPhotonCandidate1RazzleElectronScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return isnan(shw.razzle.electronScore) ? -.5 : shw.razzle.electronScore;
  });

Plot<Var> PhotonCandidate1RazzleElectronScorePlot = { "Photon Candidate 1 Razzle Electron Score", kPhotonCandidate1RazzleElectronScore, Binning::Simple(40,0,1),
						    ";Photon Candidate 1 Razzle Electron Score;Slices", "photon_candidate_1_razzle_electron_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate1RazzlePhotonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return isnan(shw.razzle.photonScore) || shw.razzle.photonScore < -1 ? 5. : shw.razzle.photonScore; 
  });

Plot<Var> PhotonCandidate1RazzlePhotonScorePlot = { "Photon Candidate 1 Razzle Photon Score", kPhotonCandidate1RazzlePhotonScore, Binning::Simple(40,0,1),
						    ";Photon Candidate 1 Razzle Photon Score;Slices", "photon_candidate_1_razzle_photon_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate1RazzleOtherScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) == 0)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate1ID(slc)];

    return isnan(shw.razzle.otherScore) ? -.5 : shw.razzle.otherScore;
  });

Plot<Var> PhotonCandidate1RazzleOtherScorePlot = { "Photon Candidate 1 Razzle Other Score", kPhotonCandidate1RazzleOtherScore, Binning::Simple(40,0,1),
						    ";Photon Candidate 1 Razzle Other Score;Slices", "photon_candidate_1_razzle_other_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate1MomentumZ([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return 0.;

    auto const& phot1 = slc->reco.shw[kPhotonCandidate1ID(slc)];
    TVector3 phot1Dir(phot1.dir.x, phot1.dir.y, phot1.dir.z);

    return (phot1Dir * phot1.bestplane_energy).Z();
  });

const Var kPhotonCandidate2Energy([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.bestplane_energy;
  });

const Var kPhotonCandidate2dEdx([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return isinf(shw.bestplane_dEdx) ? -1. : shw.bestplane_dEdx;
  });

const Var kPhotonCandidate2CnvGap([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.conversion_gap;
  });

const Var kPhotonCandidate2Density([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;
    
    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.density;
  });

const Var kPhotonCandidate2Len([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.len;
  });

const Var kPhotonCandidate2OpenAngle([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return TMath::RadToDeg() * shw.open_angle;
  });

const Var kPhotonCandidate2CosmicDist([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.cosmicDist;
  });

const Var kPhotonCandidate2DensityGrad([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.selVars.densityGradient;
  });

const Var kPhotonCandidate2DensityGradPower([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.selVars.densityGradientPower;
  });

const Var kPhotonCandidate2TrkLength([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.selVars.trackLength;
  });

const Var kPhotonCandidate2TrkWidth([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -1.;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return shw.selVars.trackWidth;
  });

const Var kPhotonCandidate2PDGPlot([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -.5;

    const int pdg = slc->reco.shw[kPhotonCandidate2ID(slc)].truth.p.pdg;

    switch(pdg) {
    case 11:
      return 0.5;
    case -11:
      return 1.5;
    case 13:
      return 2.5;
    case -13:
      return 3.5;
    case 211:
      return 4.5;
    case -211:
      return 5.5;
    case 2212:
      return 6.5;
    case 22:
      return 7.5;
    default:
      return 8.5;
    }
  });

const Var kPhotonCandidate2RazzleElectronScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return isnan(shw.razzle.electronScore) ? -.5 : shw.razzle.electronScore;
  });

Plot<Var> PhotonCandidate2RazzleElectronScorePlot = { "Photon Candidate 2 Razzle Electron Score", kPhotonCandidate2RazzleElectronScore, Binning::Simple(40,0,1),
						    ";Photon Candidate 2 Razzle Electron Score;Slices", "photon_candidate_2_razzle_electron_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate2RazzlePhotonScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return isnan(shw.razzle.photonScore) || shw.razzle.photonScore < -1 ? 5. : shw.razzle.photonScore; 
  });

Plot<Var> PhotonCandidate2RazzlePhotonScorePlot =  { "Photon Candidate 2 Razzle Photon Score", kPhotonCandidate2RazzlePhotonScore, Binning::Simple(40,0,1),
						     ";Photon Candidate 2 Razzle Photon Score;Slices", "photon_candidate_2_razzle_photon_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate2RazzleOtherScore([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -.5;

    auto const& shw = slc->reco.shw[kPhotonCandidate2ID(slc)];

    return isnan(shw.razzle.otherScore) ? -.5 : shw.razzle.otherScore;
  });

Plot<Var> PhotonCandidate2RazzleOtherScorePlot = { "Photon Candidate 2 Razzle Other Score", kPhotonCandidate2RazzleOtherScore, Binning::Simple(40,0,1),
						    ";Photon Candidate 2 Razzle Other Score;Slices", "photon_candidate_2_razzle_other_score",  {.42,.57,.72,.85} };

const Var kPhotonCandidate2MomentumZ([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return 0.;

    auto const& phot2 = slc->reco.shw[kPhotonCandidate2ID(slc)];
    TVector3 phot2Dir(phot2.dir.x, phot2.dir.y, phot2.dir.z);

    return (phot2Dir * phot2.bestplane_energy).Z();
  });

const Var kInvariantMass([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return 0.;

    auto const& phot1 = slc->reco.shw[kPhotonCandidate1ID(slc)];
    auto const& phot2 = slc->reco.shw[kPhotonCandidate2ID(slc)];

    TVector3 phot1Dir(phot1.dir.x, phot1.dir.y, phot1.dir.z);
    TVector3 phot2Dir(phot2.dir.x, phot2.dir.y, phot2.dir.z);

    const double cosine = phot1Dir.Dot(phot2Dir) / (phot1Dir.Mag() * phot2Dir.Mag());

    if(phot1.bestplane_energy < 0 || phot2.bestplane_energy < 0)
      return 0.;

    return sqrt(2 * (1e+6) * phot1.bestplane_energy * phot2.bestplane_energy * (1. - cosine));
  });

const Var kPiZeroRecoMomentum([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return 0.;

    auto const& phot1 = slc->reco.shw[kPhotonCandidate1ID(slc)];
    auto const& phot2 = slc->reco.shw[kPhotonCandidate2ID(slc)];

    TVector3 phot1Dir(phot1.dir.x, phot1.dir.y, phot1.dir.z);
    TVector3 phot2Dir(phot2.dir.x, phot2.dir.y, phot2.dir.z);

    return ((phot1Dir * phot1.bestplane_energy) + (phot2Dir * phot2.bestplane_energy)).Mag();
  });

const Var kCosPiZeroTheta([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2)
      return -2.;

    auto const& phot1 = slc->reco.shw[kPhotonCandidate1ID(slc)];
    auto const& phot2 = slc->reco.shw[kPhotonCandidate2ID(slc)];

    TVector3 phot1Dir(phot1.dir.x, phot1.dir.y, phot1.dir.z);
    TVector3 phot2Dir(phot2.dir.x, phot2.dir.y, phot2.dir.z);

    if(phot1.bestplane_energy < 0 || phot2.bestplane_energy < 0)
      return -2.;

    if(phot1Dir.X() == -999 || phot2Dir.X() == -999)
      return -2.;

    auto const& pizerodir = (phot1Dir * phot1.bestplane_energy) + (phot2Dir * phot2.bestplane_energy);

    return (pizerodir.Mag() == 0) ? -2. : pizerodir.Z() / pizerodir.Mag();
  });

const Var kCosCoMDecayAngle([](const caf::SRSliceProxy* slc) -> double {
    if(kNShowers(slc) < 2 || kPiZeroRecoMomentum(slc) == 0)
      return 0.;

    return abs(kPhotonCandidate1Energy(slc) - kPhotonCandidate2Energy(slc)) / kPiZeroRecoMomentum(slc);
  });

const Binning binsBool   = Binning::Simple(2, -0.5, 1.5, {"False", "True"});
const Binning binsPDGTrk = Binning::Simple(10,-1,9, {"No Trk", "e^{-}", "e^{+}", "#mu^{-}", "#mu^{+}", "#pi^{+}", "#pi^{-}", "p", "#gamma", "Other"});
const Binning binsPDGShw = Binning::Simple(10,-1,9, {"No Shw", "e^{-}", "e^{+}", "#mu^{-}", "#mu^{+}", "#pi^{+}", "#pi^{-}", "p", "#gamma", "Other"});

std::vector<Plot<Var>> reco_plots = { { "Is Clear Cosmic", kIsClearCosmicVar, binsBool, ";Is Clear Cosmic?;Slices", "is_clear_cosmic", {.6, .57, .82, .85} },
				      { "Is FV", kIsFVVar, binsBool, ";Is FV?;Slices", "is_fv", {.22, .57, .52, .85} },
				      CRUMBSScorePlot,
				      { "N Showers", kNShowers, Binning::Simple(10,0,10), ";nShowers;Slices", "n_showers", {.59,.57,.89,.85} },
				      { "N Tracks", kNTracks, Binning::Simple(10,0,10), ";nTracks;Slices", "n_tracks", {.59,.57,.89,.85} },
				      { "N Stubs", kNStubs, Binning::Simple(10,0,10), ";nStubs;Slices", "n_stubs", {.59,.57,.89,.85} },
				      { "N Dazzle Muons", kNDazzleMuons, Binning::Simple(6,0,6), ";nDazzleMuons;Slices", "n_dazzle_muons", {.59,.57,.89,.85} },
				      { "N Dazzle Pions", kNDazzlePions, Binning::Simple(6,0,6), ";nDazzlePions;Slices", "n_dazzle_pions", {.59,.57,.89,.85} },
				      { "N Dazzle Protons", kNDazzleProtons, Binning::Simple(6,0,6), ";nDazzleProtons;Slices", "n_dazzle_protons", {.59,.57,.89,.85} },
				      { "N Dazzle Other", kNDazzleOther, Binning::Simple(6,0,6), ";nDazzleOther;Slices", "n_dazzle_other", {.59,.57,.89,.85} },
				      { "N Chi2 Muons", kNChi2Muons, Binning::Simple(6,0,6), ";nChi2Muons;Slices", "n_chi2_muons", {.59,.57,.89,.85} },
				      { "N Chi2 Pions", kNChi2Pions, Binning::Simple(6,0,6), ";nChi2Pions;Slices", "n_chi2_pions", {.59,.57,.89,.85} },
				      { "N Chi2 Kaons", kNChi2Kaons, Binning::Simple(6,0,6), ";nChi2Kaons;Slices", "n_chi2_kaons", {.59,.57,.89,.85} },
				      { "N Chi2 Protons", kNChi2Protons, Binning::Simple(6,0,6), ";nChi2Protons;Slices", "n_chi2_protons", {.59,.57,.89,.85} },
				      { "N Razzle Electrons", kNRazzleElectrons, Binning::Simple(6,0,6), ";nRazzleElectrons;Slices", "n_razzle_electrons", {.59,.57,.89,.85} },
				      { "N Razzle Photons", kNRazzlePhotons, Binning::Simple(6,0,6), ";nRazzlePhotons;Slices", "n_razzle_photons", {.59,.57,.89,.85} },
				      { "N Razzle Other", kNRazzleOther, Binning::Simple(6,0,6), ";nRazzleOther;Slices", "n_razzle_other", {.59,.57,.89,.85} },
				      { "Summed Slice Energy", kSummedSliceEnergy, Binning::Simple(40,0,4), ";Summed Slice Energy (GeV);Slices", "summed_slice_energy", {.59,.57,.89,.85} },
				      { "Longest Track Length", kLongestTrkLen, Binning::Simple(60,-100,200), ";Longest Track Length (cm);Slices", "longest_trk_length", {.59,.57,.89,.85} },
				      { "Longest Track Dazzle Muon Score", kLongestTrkDazzleMuonScore, Binning::Simple(40,0,1), ";Longest Track Dazzle Muon Score;Slices", "longest_trk_dazzle_muon_score",  {.42,.57,.72,.85} },
				      HighestDazzleMuonScorePlot,
				      { "Longest Track Dazzle Pion Score", kLongestTrkDazzlePionScore, Binning::Simple(40,0,1), ";Longest Track Dazzle Pion Score;Slices", "longest_trk_dazzle_pion_score",  {.42,.57,.72,.85} },
				      { "Longest Track Dazzle Proton Score", kLongestTrkDazzleProtonScore, Binning::Simple(40,0,1), ";Longest Track Dazzle Proton Score;Slices", "longest_trk_dazzle_proton_score",  {.42,.57,.72,.85} },
				      { "Longest Track Dazzle Other Score", kLongestTrkDazzleOtherScore, Binning::Simple(40,0,1), ";Longest Track Dazzle Other Score;Slices", "longest_trk_dazzle_other_score",  {.42,.57,.72,.85} },
				      { "Longest Track PDG", kLongestTrkPDGPlot, binsPDGTrk, ";Longest Track PDG;Slices", "longest_trk_pdg",  {.32,.57,.62,.85} },
				      { "Photon Candidate 1 Energy", kPhotonCandidate1Energy, Binning::Simple(40,0,1), ";Photon Candidate 1 Energy (GeV);Slices", "photon_candidate_1_energy", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Momentum Z", kPhotonCandidate1MomentumZ, Binning::Simple(40,0,1), ";Photon Candidate 1 Momentum Z (GeV/c);Slices", "photon_candidate_1_momentum_z", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 dEdx", kPhotonCandidate1dEdx, Binning::Simple(40,0,10), ";Photon Candidate 1 dE/dx (MeV/cm);Slices", "photon_candidate_1_dedx", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Conversion Gap", kPhotonCandidate1CnvGap, Binning::Simple(40,0,20), ";Photon Candidate 1 Conversion Gap (cm);Slices", "photon_candidate_1_cnv_gap", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Density", kPhotonCandidate1Density, Binning::Simple(40,0,20), ";Photon Candidate 1 Density (MeV/cm);Slices", "photon_candidate_1_density", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Length", kPhotonCandidate1Len, Binning::Simple(40,0,200), ";Photon Candidate 1 Length (cm);Slices", "photon_candidate_1_len", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Opening Angle", kPhotonCandidate1OpenAngle, Binning::Simple(36,0,90), ";Photon Candidate 1 Opening Angle (#circ);Slices", "photon_candidate_1_open_angle", {.59 ,.57,.89,.85} },
				      { "Photon Candidate 1 Cosmic Dist", kPhotonCandidate1CosmicDist, Binning::Simple(40,0,400), ";Photon Candidate 1 Cosmic Dist (cm);Slices", "photon_candidate_1_cosmic_dist", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Density Gradient", kPhotonCandidate1DensityGrad, Binning::Simple(40,0,4), ";Photon Candidate 1 Density Gradient (MeV/cm);Slices", "photon_candidate_1_density_grad", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Density Gradient Power", kPhotonCandidate1DensityGradPower, Binning::Simple(4,0,4), ";Photon Candidate 1 Density Gradient Power;Slices", "photon_candidate_1_density_grad_power", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Track Stub Length", kPhotonCandidate1TrkLength, Binning::Simple(24,0,24), ";Photon Candidate 1 Track Stub Length (cm);Slices", "photon_candidate_1_trk_stub_length", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 Track Stub Width", kPhotonCandidate1TrkWidth, Binning::Simple(24,0,24), ";Photon Candidate 1 Track Stub Width (cm);Slices", "photon_candidate_1_trk_stub_width", {.59,.57,.89,.85} },
				      { "Photon Candidate 1 PDG", kPhotonCandidate1PDGPlot, binsPDGShw, ";Photon Candidate 1 PDG;Slices", "photon_candidate_1_pdg",  {.22,.57,.52,.85} },
				      { "Photon Candidate 1 Razzle Electron Score", kPhotonCandidate1RazzleElectronScore, Binning::Simple(40,0,1), ";Photon Candidate 1 Razzle Electron Score;Slices", "photon_candidate_1_razzle_electron_score",  {.42,.57,.72,.85} },
				      PhotonCandidate1RazzlePhotonScorePlot,
				      { "Photon Candidate 1 Razzle Other Score", kPhotonCandidate1RazzleOtherScore, Binning::Simple(40,0,1), ";Photon Candidate 1 Razzle Other Score;Slices", "photon_candidate_1_razzle_other_score",  {.42,.57,.72,.85} },
				      { "Photon Candidate 2 Energy", kPhotonCandidate2Energy, Binning::Simple(40,0,1), ";Photon Candidate 2 Energy (GeV);Slices", "photon_candidate_2_energy", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Momentum Z", kPhotonCandidate2MomentumZ, Binning::Simple(40,0,1), ";Photon Candidate 2 Momentum Z (GeV/c);Slices", "photon_candidate_2_momentum_z", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 dEdx", kPhotonCandidate2dEdx, Binning::Simple(40,0,10), ";Photon Candidate 2 dE/dx (MeV/cm);Slices", "photon_candidate_2_dedx", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Conversion Gap", kPhotonCandidate2CnvGap, Binning::Simple(40,0,20), ";Photon Candidate 2 Conversion Gap (cm);Slices", "photon_candidate_2_cnv_gap", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Density", kPhotonCandidate2Density, Binning::Simple(40,0,20), ";Photon Candidate 2 Density (MeV/cm);Slices", "photon_candidate_2_density", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Length", kPhotonCandidate2Len, Binning::Simple(40,0,200), ";Photon Candidate 2 Length (cm);Slices", "photon_candidate_2_len", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Opening Angle", kPhotonCandidate2OpenAngle, Binning::Simple(36,0,90), ";Photon Candidate 2 Opening Angle (#circ);Slices", "photon_candidate_2_open_angle", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Cosmic Dist", kPhotonCandidate2CosmicDist, Binning::Simple(40,0,400), ";Photon Candidate 2 Cosmic Dist (cm);Slices", "photon_candidate_2_cosmic_dist", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Density Gradient", kPhotonCandidate2DensityGrad, Binning::Simple(40,0,4), ";Photon Candidate 2 Density Gradient (MeV/cm);Slices", "photon_candidate_2_density_grad", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Density Gradient Power", kPhotonCandidate2DensityGradPower, Binning::Simple(4,0,4), ";Photon Candidate 2 Density Gradient Power;Slices", "photon_candidate_2_density_grad_power", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Track Stub Length", kPhotonCandidate2TrkLength, Binning::Simple(24,0,24), ";Photon Candidate 2 Track Stub Length (cm);Slices", "photon_candidate_2_trk_stub_length", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 Track Stub Width", kPhotonCandidate2TrkWidth, Binning::Simple(24,0,24), ";Photon Candidate 2 Track Stub Width (cm);Slices", "photon_candidate_2_trk_stub_width", {.59,.57,.89,.85} },
				      { "Photon Candidate 2 PDG", kPhotonCandidate2PDGPlot, binsPDGShw, ";Photon Candidate 2 PDG;Slices", "photon_candidate_2_pdg", {.22,.57,.52,.85} },
				      { "Photon Candidate 2 Razzle Electron Score", kPhotonCandidate2RazzleElectronScore, Binning::Simple(40,0,1), ";Photon Candidate 2 Razzle Electron Score;Slices", "photon_candidate_2_razzle_electron_score",  {.42,.57,.72,.85} },
				      PhotonCandidate2RazzlePhotonScorePlot,
				      { "Photon Candidate 2 Razzle Other Score", kPhotonCandidate2RazzleOtherScore, Binning::Simple(40,0,1), ";Photon Candidate 2 Razzle Other Score;Slices", "photon_candidate_2_razzle_other_score",  {.42,.57,.72,.85} },
				      { "Invariant Mass", kInvariantMass, Binning::Simple(30,0,400), ";Invariant Mass (MeV/c^{2});Slices", "invariant_mass", {.59,.57,.89,.85} },
				      { "Invariant Mass Eta", kInvariantMass, Binning::Simple(60,0,600), ";Invariant Mass (MeV/c^{2});Slices", "invariant_mass_eta", {.59,.57,.89,.85} },
				      { "Pi Zero Momentum", kPiZeroRecoMomentum, Binning::Simple(40,0,1), ";p_{#pi_{0}} (GeV/c);Slices", "pi_zero_momentum", {.59,.57,.89,.85} },
				      { "Cosine Pi Zero Theta", kCosPiZeroTheta, Binning::Simple(40,-1,1), ";cos(#theta_{#pi_{0}});Slices", "cos_pi_zero_theta", {.22,.57,.52,.85} },
				      { "Summed Shower Momentum Z", kPhotonCandidate1MomentumZ + kPhotonCandidate2MomentumZ, Binning::Simple(40,0,2), ";Summed Shower Momentum Z (GeV);Slices", "summed_shw_momentum_z", {.59,.57,.89,.85} },
				      { "Cosine CoM Decay Angle", kCosCoMDecayAngle, Binning::Simple(40,0,1), ";cos(#theta_{CoM});Slices", "cos_com_decay_angle", {.59,.57,.89,.85} },
				      { "Cosine CoM Decay Angle High", kCosCoMDecayAngle, Binning::Simple(50,0.9,1), ";cos(#theta_{CoM});Slices", "cos_com_decay_angle_high", {.59,.57,.89,.85} },
};
				      
