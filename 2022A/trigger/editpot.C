{
  TFile *file = new TFile("./test.flat.caf.root", "UPDATE");
  TTree* tree = (TTree*) file->Get("recTree");
  TH1F *hist = (TH1F*) file->Get("TotalPOT");

  TH1F *treehist = new TH1F("treehist", "treehist", 1, 0, 1);
  tree->Draw("0.5>>treehist", "rec.hdr.pot", "goff");
  std::cout << treehist->GetBinContent(1) << std::endl;

  std::cout << hist->GetBinContent(1) << std::endl;
  hist->SetBinContent(1, treehist->GetBinContent(1));

  std::cout << hist->GetBinContent(1) << std::endl;
  hist->Write();
}
