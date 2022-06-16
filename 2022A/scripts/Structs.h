struct Plot {
  std::string name = "";
  SpillVar variable; 
  Binning binning;
  std::string axes_labels;
  std::string label;
  std::vector<float> legBox = {.1, .1, .4, .3};
};

struct TrueCategory {
  std::string name = "";
  SpillCut cut = kNoSpillCut;
  int colour = kBlack;
  std::string label = "";
};
