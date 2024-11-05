TH1D *histamplitude;
TH1D *histtime_raw:
TH2D *histwalk;
TProfile *phistwalk;
TH1D *histtime_corr:


int analyze() {
  // pull data
  TFile *inputfile = new TFile("file_analysis.root");
  histamplitude = (TH1D*) inputfile->Get( "histamplitude" );
  histtime_raw = (TH1D*) inputfile->Get( "histtime_raw" );
  histwalk = (TH1D*) inputfile->Get( "histwalk" );
  phistwalk = (TH1D*) inputfile->Get( "phistwalk" );
  histtime_corr = (TH1D*) inputfile->Get( "histtime_corr" );
   
  new TCanvas();
  histamplitude->Draw();
  new TCanvas();
  // fit data to a gaussian distribution
  histtime_corr->Fit("gaus");
  // extract parameters
  double mean = fit->GetParameter(1);
  double emean = fit->GetParError(1);
  double sigma = fit->GetParameter(2);
  double esigma = fit->GetParError(2);
  // report
  cout << "Measure delta time: " << mean << " with error " << emean << endl;
  cout << "Associated resolution: " << sigma << " with error " << esigma << endl;
  histtime_raw=>Draw("same");

  new TCanvas();
  histwalk->Draw();
  new TCanvas();
  phistwalk->Draw();

  if(0) { // switch this to "1" when you are ready to find a correction
    // model a walk correction, pick one or implement one better
    // using a polynomial 4th degree
    TF1 *model0 = new TF1("model0","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
    phistwalk->Fit(model0);
    // once happy, get your correction function, implement it in readtree.C and rerun
  }
  
  return 0;
}
