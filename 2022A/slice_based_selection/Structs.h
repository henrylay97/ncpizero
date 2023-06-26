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

template <typename T>
struct TrueCategory {
  TString name = "";
  T cut;
  int colour = kBlack;
  TString label = "";
  TString description = "";
  TString latex_name = "";
};

template <typename T>
struct CutDef {
  TString name = "";
  TString label = "";
  T cut;
  int colour = kBlack;
};
