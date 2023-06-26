#include "TVector3.h"

const SpillVar kBestSlcID([](const caf::SRSpillProxy* sp) -> unsigned {
    unsigned i = 0;
    double bestCrumbsScore = -std::numeric_limits<double>::max();
    unsigned returnID = 0;

    for(auto const& slc : sp->slc)
      {
	if(slc.is_clear_cosmic || isnan(slc.crumbs_result.score) || !PtInVolAbsX(slc.vertex, fvndpizero)) 
	  { ++i; continue; }

	if(slc.crumbs_result.score > bestCrumbsScore)
	  {
	    bestCrumbsScore = slc.crumbs_result.score;
	    returnID        = i;
	  }

	++i;
      }
    return returnID;
  });

const SpillVar kFlashTrigVar([](const caf::SRSpillProxy *sp) ->unsigned {
    return sp->pass_flashtrig ? 1 : 0;
  });

const SpillVar kNSlices([](const caf::SRSpillProxy* sp) -> unsigned {
    return sp->nslc;
  });

const SpillVar kNNuSlices([](const caf::SRSpillProxy* sp) -> unsigned {
    unsigned i = 0;

    for(auto const& slc : sp->slc)
      {
	if(!slc.is_clear_cosmic) ++i;
      }

    return i;
  });

const SpillVar kNFVSlices([](const caf::SRSpillProxy* sp) -> unsigned {
    unsigned i = 0;

    for(auto const& slc : sp->slc)
      {
	if(slc.is_clear_cosmic) continue;

	if(PtInVolAbsX(slc.vertex, fvndpizero)) ++i;
      }

    return i;
  });

const SpillVar kCRUMBSScore([](const caf::SRSpillProxy* sp) -> double {
    if(sp->nslc==0) return -1.5;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    if(slc.is_clear_cosmic || isnan(slc.crumbs_result.score)) return -1.5;
    return slc.crumbs_result.score;
  });

const SpillVar kIsFVVar([](const caf::SRSpillProxy* sp) -> double {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return PtInVolAbsX(slc.vertex, fvndpizero) ? 1 : 0;
  });

const SpillVar kNTracks([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return slc.reco.ntrk;
  });

const SpillVar kNDazzleMuons([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& trk : slc.reco.trk)
      {
	if(trk.dazzle.pdg == 13) ++i;
      }

    return i;
  });

const SpillVar kNDazzlePions([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& trk : slc.reco.trk)
      {
	if(trk.dazzle.pdg == 211) ++i;
      }

    return i;
  });

const SpillVar kNDazzleProtons([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& trk : slc.reco.trk)
      {
	if(trk.dazzle.pdg == 2212) ++i;
      }

    return i;
  });

const SpillVar kNDazzleOther([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& trk : slc.reco.trk)
      {
	if(trk.dazzle.pdg == 0) ++i;
      }

    return i;
  });

const SpillVar kNRazzleElectrons([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& shw : slc.reco.shw)
      {
	if(shw.razzle.pdg == 11) ++i;
      }

    return i;
  });

const SpillVar kNRazzlePhotons([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& shw : slc.reco.shw)
      {
	if(shw.razzle.pdg == 22) ++i;
      }

    return i;
  });

const SpillVar kNRazzleOther([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    unsigned i = 0;

    for(auto const& shw : slc.reco.shw)
      {
	if(shw.razzle.pdg == 0) ++i;
      }

    return i;
  });

const SpillVar kNShowers([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return slc.reco.nshw;
  });

const SpillVar kNStubs([](const caf::SRSpillProxy* sp) -> unsigned {
    if(sp->nslc==0) return 0;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    return slc.reco.nstub;
  });

const SpillVar kSummedSliceEnergy([](const caf::SRSpillProxy* sp) -> double {
    if(sp->nslc==0) return 0.;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    double en = 0.;

    for(auto const& trk : slc.reco.trk)
      en += trk.calo[trk.bestplane].ke * 1e-3;
    
    for(auto const& shw : slc.reco.shw)
      en += shw.bestplane_energy;
          
    return en;
  });

const SpillVar kLeadingShwID([](const caf::SRSpillProxy* sp) -> int {
    if(kNShowers(sp) == 0) return -1;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc.reco.shw)
      {
	list.push_back(std::pair<int, double>(i, shw.bestplane_energy));
	++i;
      }
    
    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
					   const std::pair<int, double> &y)
	      { return x.second > y.second; });
    
    return list[0].first;
  });

const SpillVar kSubLeadingShwID([](const caf::SRSpillProxy* sp) -> int {
    if(kNShowers(sp) < 2) return -1;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& shw : slc.reco.shw)
      {
	list.push_back(std::pair<int, double>(i, shw.bestplane_energy));
	++i;
      }
    
    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
					   const std::pair<int, double> &y)
	      { return x.second > y.second; });
    
    return list[1].first;
  });

const SpillVar kLeadingShwEnergy([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.bestplane_energy;
  });

const SpillVar kLeadingShwdEdx([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.bestplane_dEdx;
  });

const SpillVar kLeadingShwCnvGap([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.conversion_gap;
  });

const SpillVar kLeadingShwDensity([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.density;
  });

const SpillVar kLeadingShwLen([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.len;
  });

const SpillVar kLeadingShwOpenAngle([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return TMath::RadToDeg() * shw.open_angle;
  });

const SpillVar kLeadingShwCosmicDist([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.cosmicDist;
  });

const SpillVar kLeadingShwDensityGrad([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.selVars.densityGradient;
  });

const SpillVar kLeadingShwDensityGradPower([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.selVars.densityGradientPower;
  });

const SpillVar kLeadingShwTrkLength([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.selVars.trackLength;
  });

const SpillVar kLeadingShwTrkWidth([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    
    return shw.selVars.trackWidth;
  });

const SpillVar kLeadingShwPDGPlot([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -.5;

    const int pdg = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)].truth.p.pdg;

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

const SpillVar kLeadingShwRazzleElectronScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];

    return shw.razzle.electronScore;
  });

const SpillVar kLeadingShwRazzlePhotonScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];

    return shw.razzle.photonScore;
  });

const SpillVar kLeadingShwRazzleOtherScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];

    return shw.razzle.otherScore;
  });

const SpillVar kSubLeadingShwEnergy([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.bestplane_energy;
  });

const SpillVar kSubLeadingShwdEdx([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.bestplane_dEdx;
  });

const SpillVar kSubLeadingShwCnvGap([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.conversion_gap;
  });

const SpillVar kSubLeadingShwDensity([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.density;
  });

const SpillVar kSubLeadingShwLen([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.len;
  });

const SpillVar kSubLeadingShwOpenAngle([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return TMath::RadToDeg() * shw.open_angle;
  });

const SpillVar kSubLeadingShwCosmicDist([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.cosmicDist;
  });

const SpillVar kSubLeadingShwDensityGrad([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.selVars.densityGradient;
  });

const SpillVar kSubLeadingShwDensityGradPower([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.selVars.densityGradientPower;
  });

const SpillVar kSubLeadingShwTrkLength([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.selVars.trackLength;
  });

const SpillVar kSubLeadingShwTrkWidth([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    
    return shw.selVars.trackWidth;
  });

const SpillVar kLongestTrkID([](const caf::SRSpillProxy* sp) -> int {
    if(kNTracks(sp) == 0) return -1.;
    auto const& slc = sp->slc[kBestSlcID(sp)];

    std::vector<std::pair<int, double> > list;
    unsigned i = 0;

    for(auto const& trk : slc.reco.trk)
      {
	list.push_back(std::pair<int, double>(i, trk.len));
	++i;
      }
    
    std::sort(list.begin(), list.end(), [](const std::pair<int, double> &x,
					   const std::pair<int, double> &y)
	      { return x.second > y.second; });
    
    return list[0].first;
  });

const SpillVar kSubLeadingShwPDGPlot([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -.5;

    const int pdg = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)].truth.p.pdg;

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

const SpillVar kSubLeadingShwRazzleElectronScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    return shw.razzle.electronScore;
  });

const SpillVar kSubLeadingShwRazzlePhotonScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    return shw.razzle.photonScore;
  });

const SpillVar kSubLeadingShwRazzleOtherScore([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -.5;
    auto const& shw = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    return shw.razzle.otherScore;
  });

const SpillVar kLongestTrkLen([](const caf::SRSpillProxy* sp) -> double {
    if(kNTracks(sp) == 0) return -1;
    auto const& trk = sp->slc[kBestSlcID(sp)].reco.trk[kLongestTrkID(sp)];

    return trk.len;
  });

const SpillVar kLongestTrkPDGPlot([](const caf::SRSpillProxy* sp) -> double {
    if(kNTracks(sp) == 0) return -.5;

    const int pdg = sp->slc[kBestSlcID(sp)].reco.trk[kLongestTrkID(sp)].truth.p.pdg;

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

const SpillVar kInvariantMass([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    auto const& lead = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    auto const& sublead = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    TVector3 leadDir(lead.dir.x, lead.dir.y, lead.dir.z);
    TVector3 subleadDir(sublead.dir.x, sublead.dir.y, sublead.dir.z);

    const double cosine = leadDir.Dot(subleadDir) / (leadDir.Mag() * subleadDir.Mag());

    return sqrt(2 * (1e+6) * lead.bestplane_energy * sublead.bestplane_energy * (1. - cosine));
  });

const SpillVar kPiZeroRecoMomentum([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    auto const& lead = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    auto const& sublead = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    TVector3 leadDir(lead.dir.x, lead.dir.y, lead.dir.z);
    TVector3 subleadDir(sublead.dir.x, sublead.dir.y, sublead.dir.z);

    return ((leadDir * lead.bestplane_energy) + (subleadDir * sublead.bestplane_energy)).Mag();
  });

const SpillVar kCosPiZeroTheta([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    auto const& lead = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    auto const& sublead = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];

    TVector3 leadDir(lead.dir.x, lead.dir.y, lead.dir.z);
    TVector3 subleadDir(sublead.dir.x, sublead.dir.y, sublead.dir.z);

    auto const& pizerodir = (leadDir * lead.bestplane_energy) + (subleadDir * sublead.bestplane_energy);
    
    return pizerodir.Z() / pizerodir.Mag();
  });

const SpillVar kLeadingShwMomentumZ([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    auto const& lead = sp->slc[kBestSlcID(sp)].reco.shw[kLeadingShwID(sp)];
    TVector3 leadDir(lead.dir.x, lead.dir.y, lead.dir.z);

    return (leadDir * lead.bestplane_energy).Z();
  });

const SpillVar kSubLeadingShwMomentumZ([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    auto const& sublead = sp->slc[kBestSlcID(sp)].reco.shw[kSubLeadingShwID(sp)];
    TVector3 subleadDir(sublead.dir.x, sublead.dir.y, sublead.dir.z);

    return (subleadDir * sublead.bestplane_energy).Z();
  });

const SpillVar kCosCoMDecayAngle([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return 0.;

    return (kLeadingShwEnergy(sp) - kSubLeadingShwEnergy(sp)) / kPiZeroRecoMomentum(sp);
  });

const Binning binsPDGTrk = Binning::Simple(10,-1,9, {"No Trk", "e^{-}", "e^{+}", "#mu^{-}", "#mu^{+}", "#pi^{+}", "#pi^{-}", "p", "#gamma", "Other"});
const Binning binsPDGShw = Binning::Simple(10,-1,9, {"No Shw", "e^{-}", "e^{+}", "#mu^{-}", "#mu^{+}", "#pi^{+}", "#pi^{-}", "p", "#gamma", "Other"});


std::vector<Plot<SpillVar>> recoPlots = { { "Flash Trigger", kFlashTrigVar, Binning::Simple(2,0,2), ";Flash Trigger;Events", "flash_trigger", {.59,.57,.89,.85} },
					  { "N Slices", kNSlices, Binning::Simple(30,0,30), ";nSlices;Events", "n_slices", {.59,.57,.89,.85} },
					  { "N Nu Slices", kNNuSlices, Binning::Simple(10,0,10), ";nNuSlices;Events", "n_nu_slices", {.59,.57,.89,.85} },
					  { "N FV Slices", kNFVSlices, Binning::Simple(10,0,10), ";nFVSlices;Events", "n_fv_slices", {.59,.57,.89,.85} },
					  { "CRUMBS Score", kCRUMBSScore, Binning::Simple(42,-1.5,.6), ";CRUMBS Score;Events", "crumbs_score", {.22,.57,.52,.85} }, 
					  { "FV Cut", kIsFVVar, Binning::Simple(2,0,2), ";FV Cut;Events", "fv_cut", {.22,.57,.52,.85} }, 
					  { "N Dazzle Muons", kNDazzleMuons, Binning::Simple(6,0,6), ";nDazzleMuons;Events", "n_dazzle_muons", {.59,.57,.89,.85} },
					  { "N Dazzle Pions", kNDazzlePions, Binning::Simple(6,0,6), ";nDazzlePions;Events", "n_dazzle_pions", {.59,.57,.89,.85} },
					  { "N Dazzle Protons", kNDazzleProtons, Binning::Simple(6,0,6), ";nDazzleProtons;Events", "n_dazzle_protons", {.59,.57,.89,.85} },
					  { "N Dazzle Other", kNDazzleOther, Binning::Simple(6,0,6), ";nDazzleOther;Events", "n_dazzle_other", {.59,.57,.89,.85} },
					  { "N Razzle Electrons", kNRazzleElectrons, Binning::Simple(6,0,6), ";nRazzleElectrons;Events", "n_razzle_electrons", {.59,.57,.89,.85} },
					  { "N Razzle Photons", kNRazzlePhotons, Binning::Simple(6,0,6), ";nRazzlePhotons;Events", "n_razzle_photons", {.59,.57,.89,.85} },
					  { "N Razzle Other", kNRazzleOther, Binning::Simple(6,0,6), ";nRazzleOther;Events", "n_razzle_other", {.59,.57,.89,.85} },
					  { "N Showers", kNShowers, Binning::Simple(10,0,10), ";nShowers;Events", "n_showers", {.59,.57,.89,.85} }, 
					  { "N Tracks", kNTracks, Binning::Simple(10,0,10), ";nTracks;Events", "n_tracks", {.59,.57,.89,.85} }, 
					  { "N Stubs", kNStubs, Binning::Simple(10,0,10), ";nStubs;Events", "n_stubs", {.59,.57,.89,.85} }, 
					  { "Summed Slice Energy", kSummedSliceEnergy, Binning::Simple(40,0,4), ";Summed Slice Energy (GeV);Events", "summed_slice_energy", {.59,.57,.89,.85} }, 
					  { "Leading Shower Energy", kLeadingShwEnergy, Binning::Simple(40,0,1), ";Leading Shower Energy (GeV);Events", "leading_shw_energy", {.59,.57,.89,.85} },
					  { "Leading Shower Momentum Z", kLeadingShwMomentumZ, Binning::Simple(40,0,1), ";Leading Shower Momentum Z (GeV/c);Events", "leading_shw_momentum_z", {.59,.57,.89,.85} },
					  { "Leading Shower dEdx", kLeadingShwdEdx, Binning::Simple(40,0,10), ";Leading Shower dE/dx (MeV/cm);Events", "leading_shw_dedx", {.59,.57,.89,.85} },
					  { "Leading Shower Conversion Gap", kLeadingShwCnvGap, Binning::Simple(40,0,20), ";Leading Shower Conversion Gap (cm);Events", "leading_shw_cnv_gap", {.59,.57,.89,.85} },
					  { "Leading Shower Density", kLeadingShwDensity, Binning::Simple(40,0,20), ";Leading Shower Density (MeV/cm);Events", "leading_shw_density", {.59,.57,.89,.85} },
					  { "Leading Shower Length", kLeadingShwLen, Binning::Simple(40,0,200), ";Leading Shower Length (cm);Events", "leading_shw_len", {.59,.57,.89,.85} },
					  { "Leading Shower Opening Angle", kLeadingShwOpenAngle, Binning::Simple(36,0,90), ";Leading Shower Opening Angle (#circ);Events", "leading_shw_open_angle", {.59,.57,.89,.85} },
					  { "Leading Shower Cosmic Dist", kLeadingShwCosmicDist, Binning::Simple(40,0,400), ";Leading Shower Cosmic Dist (cm);Events", "leading_shw_cosmic_dist", {.59,.57,.89,.85} },
					  { "Leading Shower Density Gradient", kLeadingShwDensityGrad, Binning::Simple(40,0,4), ";Leading Shower Density Gradient (MeV/cm);Events", "leading_shw_density_grad", {.59,.57,.89,.85} },
					  { "Leading Shower Density Gradient Power", kLeadingShwDensityGradPower, Binning::Simple(4,0,4), ";Leading Shower Density Gradient Power;Events", "leading_shw_density_grad_power", {.59,.57,.89,.85} },
					  { "Leading Shower Track Stub Length", kLeadingShwTrkLength, Binning::Simple(24,0,24), ";Leading Shower Track Stub Length (cm);Events", "leading_shw_trk_stub_length", {.59,.57,.89,.85} },
					  { "Leading Shower Track Stub Width", kLeadingShwTrkWidth, Binning::Simple(24,0,24), ";Leading Shower Track Stub Width (cm);Events", "leading_shw_trk_stub_width", {.59,.57,.89,.85} },
					  { "Leading Shower PDG", kLeadingShwPDGPlot, binsPDGShw, ";Leading Shower PDG;Events", "leading_shw_pdg",  {.22,.57,.52,.85} },
					  { "Leading Shower Razzle Electron Score", kLeadingShwRazzleElectronScore, Binning::Simple(40,0,1), ";Leading Shower Razzle Electron Score;Events", "leading_shw_razzle_electron_score",  {.42,.57,.72,.85} },
					  { "Leading Shower Razzle Photon Score", kLeadingShwRazzlePhotonScore, Binning::Simple(40,0,1), ";Leading Shower Razzle Photon Score;Events", "leading_shw_razzle_photon_score",  {.42,.57,.72,.85} },
					  { "Leading Shower Razzle Other Score", kLeadingShwRazzleOtherScore, Binning::Simple(40,0,1), ";Leading Shower Razzle Other Score;Events", "leading_shw_razzle_other_score",  {.42,.57,.72,.85} },
					  { "SubLeading Shower Energy", kSubLeadingShwEnergy, Binning::Simple(40,0,1), ";SubLeading Shower Energy (GeV);Events", "subleading_shw_energy", {.59,.57,.89,.85} },
					  { "SubLeading Shower Momentum Z", kSubLeadingShwMomentumZ, Binning::Simple(40,0,1), ";SubLeading Shower Momentum Z (GeV/c);Events", "subleading_shw_momentum_z", {.59,.57,.89,.85} },
					  { "SubLeading Shower dEdx", kSubLeadingShwdEdx, Binning::Simple(40,0,10), ";SubLeading Shower dE/dx (MeV/cm);Events", "subleading_shw_dedx", {.59,.57,.89,.85} },
					  { "SubLeading Shower Conversion Gap", kSubLeadingShwCnvGap, Binning::Simple(40,0,20), ";SubLeading Shower Conversion Gap (cm);Events", "subleading_shw_cnv_gap", {.59,.57,.89,.85} },
					  { "SubLeading Shower Density", kSubLeadingShwDensity, Binning::Simple(40,0,20), ";SubLeading Shower Density (MeV/cm);Events", "subleading_shw_density", {.59,.57,.89,.85} },
					  { "SubLeading Shower Length", kSubLeadingShwLen, Binning::Simple(40,0,200), ";SubLeading Shower Length (cm);Events", "subleading_shw_len", {.59,.57,.89,.85} },
					  { "SubLeading Shower Opening Angle", kSubLeadingShwOpenAngle, Binning::Simple(36,0,90), ";SubLeading Shower Opening Angle (#circ);Events", "subleading_shw_open_angle", {.59,.57,.89,.85} },
					  { "SubLeading Shower Cosmic Dist", kSubLeadingShwCosmicDist, Binning::Simple(40,0,400), ";SubLeading Shower Cosmic Dist (cm);Events", "subleading_shw_cosmic_dist", {.59,.57,.89,.85} },
					  { "SubLeading Shower Density Gradient", kSubLeadingShwDensityGrad, Binning::Simple(40,0,4), ";SubLeading Shower Density Gradient (MeV/cm);Events", "subleading_shw_density_grad", {.59,.57,.89,.85} },
					  { "SubLeading Shower Density Gradient Power", kSubLeadingShwDensityGradPower, Binning::Simple(4,0,4), ";SubLeading Shower Density Gradient Power;Events", "subleading_shw_density_grad_power", {.59,.57,.89,.85} },
					  { "SubLeading Shower Track Stub Length", kSubLeadingShwTrkLength, Binning::Simple(24,0,24), ";SubLeading Shower Track Stub Length (cm);Events", "subleading_shw_trk_stub_length", {.59,.57,.89,.85} },
					  { "SubLeading Shower Track Stub Width", kSubLeadingShwTrkWidth, Binning::Simple(24,0,24), ";SubLeading Shower Track Stub Width (cm);Events", "subleading_shw_trk_stub_width", {.59,.57,.89,.85} },
					  { "SubLeading Shower PDG", kSubLeadingShwPDGPlot, binsPDGShw, ";SubLeading Shower PDG;Events", "subleading_shw_pdg", {.22,.57,.52,.85} },
					  { "SubLeading Shower Razzle Electron Score", kSubLeadingShwRazzleElectronScore, Binning::Simple(40,0,1), ";SubLeading Shower Razzle Electron Score;Events", "subleading_shw_razzle_electron_score",  {.42,.57,.72,.85} },
					  { "SubLeading Shower Razzle Photon Score", kSubLeadingShwRazzlePhotonScore, Binning::Simple(40,0,1), ";SubLeading Shower Razzle Photon Score;Events", "subleading_shw_razzle_photon_score",  {.42,.57,.72,.85} },
					  { "SubLeading Shower Razzle Other Score", kSubLeadingShwRazzleOtherScore, Binning::Simple(40,0,1), ";SubLeading Shower Razzle Other Score;Events", "subleading_shw_razzle_other_score",  {.42,.57,.72,.85} },
					  { "Invariant Mass", kInvariantMass, Binning::Simple(30,0,400), ";Invariant Mass (MeV/c^{2});Events", "invariant_mass", {.59,.57,.89,.85} },
					  { "Longest Track Length", kLongestTrkLen, Binning::Simple(40,0,150), ";Longest Track Length (cm);Events", "longest_trk_length", {.59,.57,.89,.85} },
					  { "Longest Track PDG", kLongestTrkPDGPlot, binsPDGTrk, ";Longest Track PDG;Events", "longest_trk_pdg",  {.32,.57,.62,.85} },
					  { "Pi Zero Momentum", kPiZeroRecoMomentum, Binning::Simple(40,0,1), ";p_{#pi_{0}} (GeV/c);Events", "pi_zero_momentum", {.59,.57,.89,.85} },
					  { "Cosine Pi Zero Theta", kCosPiZeroTheta, Binning::Simple(40,-1,1), ";cos(#theta_{#pi_{0}});Events", "cos_pi_zero_theta", {.22,.57,.52,.85} },
					  { "Summed Shower Momentum Z", kLeadingShwMomentumZ + kSubLeadingShwMomentumZ, Binning::Simple(40,0,2), ";Summed Shower Momentum Z (GeV);Events", "summed_shw_momentum_z", {.59,.57,.89,.85} },
					  { "Cosine CoM Decay Angle", kCosCoMDecayAngle, Binning::Simple(40,0,1), ";cos(#theta_{CoM});Events", "cos_com_decay_angle", {.59,.57,.89,.85} },
};

std::vector<Plot<SpillVar>> recoInvertedPlots = { { "Invariant Mass", kInvariantMass, Binning::Simple(30,0,400), ";Invariant Mass (MeV/c^{2});Events", "invariant_mass_inverted", {.59,.57,.89,.85} },
};
