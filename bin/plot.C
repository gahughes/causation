void plot( string sInFile )
{

  TFile *infile = new TFile(sInFile.c_str());

  TGraphErrors *gCorrelation = (TGraphErrors*)infile->Get("gCorrelation");
  TGraphErrors *gTeVLC       = (TGraphErrors*)infile->Get("gTeVLC");
  TGraphErrors *gXrayLC      = (TGraphErrors*)infile->Get("gXrayLC");

  TCanvas *c1 = new TCanvas("c1","c1",0,0,500,500);
  gCorrelation->Draw("P");
  //TCanvas *c2 = new TCanvas("c2","c2",0,0,500,500);
  //gTeVLC->Draw("AP");
  //TCanvas *c3 = new TCanvas("c3","c3",0,0,500,500);
  //gXrayLC->Draw("AP");

}
