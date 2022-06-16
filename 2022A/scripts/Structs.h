#include "TString.h"

struct Plot {
  TString name = "";
  SpillVar variable; 
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
