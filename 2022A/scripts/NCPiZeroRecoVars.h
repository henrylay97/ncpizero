const SpillVar kBestSlcID([](const caf::SRSpillProxy* sp) -> unsigned {
    unsigned i = 0;
    double bestCrumbsScore = -std::numeric_limits<double>::max();
    unsigned returnID = 0;

    for(auto const& slc : sp->slc)
      {
	if(slc.is_clear_cosmic || isnan(slc.crumbs_result.score) || !PtInVolAbsX(slc.vertex, fvndAbs)) 
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

	if(PtInVolAbsX(slc.vertex, fvndAbs)) ++i;
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

    return PtInVolAbsX(slc.vertex, fvndAbs) ? 1 : 0;
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

const SpillVar kLeadingShwID([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) == 0) return -1.;
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

const SpillVar kSubLeadingShwID([](const caf::SRSpillProxy* sp) -> double {
    if(kNShowers(sp) < 2) return -1.;
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

std::vector<Plot<SpillVar>> recoPlots = { { "Flash Trigger", kFlashTrigVar, Binning::Simple(2,0,2), ";Flash Trigger;Events", "flash_trigger", {.59,.57,.89,.85} },
					  { "N Slices", kNSlices, Binning::Simple(30,0,30), ";nSlices;Events", "n_slices", {.59,.57,.89,.85} },
					  { "N Nu Slices", kNNuSlices, Binning::Simple(10,0,10), ";nNuSlices;Events", "n_nu_slices", {.59,.57,.89,.85} },
					  { "N FV Slices", kNFVSlices, Binning::Simple(10,0,10), ";nFVSlices;Events", "n_fv_slices", {.59,.57,.89,.85} },
					  { "CRUMBS Score", kCRUMBSScore, Binning::Simple(42,-1.5,.6), ";CRUMBS Score;Events", "crumbs_score", {.22,.57,.52,.85} }, 
					  { "FV Cut", kIsFVVar, Binning::Simple(2,0,2), ";FV Cut;Events", "fv_cut", {.59,.57,.89,.85} }, 
					  { "N Dazzle Muons", kNDazzleMuons, Binning::Simple(6,0,6), ";nDazzleMuons;Events", "n_dazzle_muons", {.59,.57,.89,.85} },
					  { "N Showers", kNShowers, Binning::Simple(10,0,10), ";nShowers;Events", "n_showers", {.59,.57,.89,.85} }, 
					  { "N Tracks", kNTracks, Binning::Simple(10,0,10), ";nTracks;Events", "n_tracks", {.59,.57,.89,.85} }, 
					  { "N Stubs", kNStubs, Binning::Simple(10,0,10), ";nStubs;Events", "n_stubs", {.59,.57,.89,.85} }, 
					  { "Summed Slice Energy", kSummedSliceEnergy, Binning::Simple(40,0,4), ";Summed Slice Energy (GeV);Events", "summed_slice_energy", {.59,.57,.89,.85} }, 
					  { "Leading Shower Energy", kLeadingShwEnergy, Binning::Simple(40,0,1), ";Leading Shower Energy (GeV);Events", "leading_shw_energy", {.59,.57,.89,.85} },
					  { "Leading Shower dEdx", kLeadingShwdEdx, Binning::Simple(40,0,10), ";Leading Shower dE/dx (MeV/cm);Events", "leading_shw_dedx", {.59,.57,.89,.85} },
					  { "Leading Shower Conversion Gap", kLeadingShwCnvGap, Binning::Simple(40,0,20), ";Leading Shower Conversion Gap (cm);Events", "leading_shw_cnv_gap", {.59,.57,.89,.85} },
					  { "Leading Shower Density", kLeadingShwDensity, Binning::Simple(40,0,20), ";Leading Shower Density (MeV/cm);Events", "leading_shw_density", {.59,.57,.89,.85} },
					  { "Leading Shower Length", kLeadingShwLen, Binning::Simple(40,0,200), ";Leading Shower Length (cm);Events", "leading_shw_len", {.59,.57,.89,.85} },
					  { "Leading Shower Opening Angle", kLeadingShwOpenAngle, Binning::Simple(36,0,90), ";Leading Shower Opening Angle (#circ);Events", "leading_open_angle", {.59,.57,.89,.85} },
					  { "Leading Shower Cosmic Dist", kLeadingShwCosmicDist, Binning::Simple(40,0,400), ";Leading Shower Cosmic Dist (cm);Events", "leading_cosmic_dist", {.59,.57,.89,.85} },
					  { "SubLeading Shower Energy", kSubLeadingShwEnergy, Binning::Simple(40,0,1), ";SubLeading Shower Energy (GeV);Events", "subleading_shw_energy", {.59,.57,.89,.85} },
					  { "SubLeading Shower dEdx", kSubLeadingShwdEdx, Binning::Simple(40,0,10), ";SubLeading Shower dE/dx (MeV/cm);Events", "subleading_shw_dedx", {.59,.57,.89,.85} },
					  { "SubLeading Shower Conversion Gap", kSubLeadingShwCnvGap, Binning::Simple(40,0,20), ";SubLeading Shower Conversion Gap (cm);Events", "subleading_shw_cnv_gap", {.59,.57,.89,.85} },
					  { "SubLeading Shower Density", kSubLeadingShwDensity, Binning::Simple(40,0,20), ";SubLeading Shower Density (MeV/cm);Events", "subleading_shw_density", {.59,.57,.89,.85} },
					  { "SubLeading Shower Length", kSubLeadingShwLen, Binning::Simple(40,0,200), ";SubLeading Shower Length (cm);Events", "subleading_shw_len", {.59,.57,.89,.85} },
					  { "SubLeading Shower Opening Angle", kSubLeadingShwOpenAngle, Binning::Simple(36,0,90), ";SubLeading Shower Opening Angle (#circ);Events", "subleading_open_angle", {.59,.57,.89,.85} },
					  { "SubLeading Shower Cosmic Dist", kSubLeadingShwCosmicDist, Binning::Simple(40,0,400), ";SubLeading Shower Cosmic Dist (cm);Events", "subleading_cosmic_dist", {.59,.57,.89,.85} },
};
