#include "TString.h"

template <typename T>
struct Plot {
  TString name = "";
  T variable; 
  Binning binning;
  TString axes_labels;
  TString label;
  std::vector<float> legBox = {.1, .1, .4, .3};
};

struct TrueCategory {
  TString name = "";
  SpillCut cut = kNoSpillCut;
  int colour = kBlack;
  TString label = "";
};

struct Particle {
  TString name = "";
  int colour = kBlack;
  TString label = "";
  ParticleCut cut = kNoParticleCut;
};

struct CutDef {
  TString name = "";
  TString label = "";
  SpillCut cut = kNoSpillCut;
};
