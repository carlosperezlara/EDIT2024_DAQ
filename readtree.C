TH1D *histamplitude = new TH1D("histamplitude","histamplitude;Amplitude  (mV);Counts",100,0,1000);
TH1D *histtime_raw  = new TH1D("histtime_raw","histtime_raw;Delta Time  (ns);Counts",100,-1,+1);
TH2D *histwalk = new TH2D("histwalk","histwalk;Amplitude  (mV);Delta Time  (ns)",100,0,1000,100,-1,+1);
TProfile *phistwalk = new TProfle("phistwalk","phistwalk;Amplitude  (mV);Delta Time  (ns)",100,0,1000);
TH1D *histtime_corr = new TH1D("histtime_corr","histtime_corr;Delta Time  (ns);Counts",100,-1,+1);

double walk_correction(double amp) {
  // when ready, implement your correction function here
  double corr = 0;
  return corr;
}

int readtree() {
  // pull data
  TFile *inputfile = new TFile("file.root");
  TTree *tree = (TTree*) inputfile->Get("pulse");

  // define and associate transient variables to tree
  Float_t LP2_20_Det;
  Float_t LP2_20_Ref;
  Float_t Amp_Det;
  
  uint nev = tree->GetEntries(); // getting number of events
  // profile data
  for(uint ie=0; ie<nev; ++ie) { // loop over all events
    tree->GetEntry(ie); // pull full event into memory

    double raw_delta_time = LP2_20_Det - LP2_20_Ref;
    histamplitude->Fill( Amp_Det );                // record amplitude
    histtime_raw->Fill( LP2_20_Det - LP2_20_Ref ); // record delta time
    histwalk->Fill( Amp_Det, raw_delta_time );     // record walk

    double real_delta_time = raw_delta_time - walk_correction( Amp_Det );
    histtime_corr->Fill( real_delta_time );
  }

  // save data to disk
  TFile *outputfile = new TFile("file_analysis.root","RECREATE");
  histamplitude->Write( "histamplitude" );
  histtime_raw->Write( "histtime_raw" );
  histwalk->Write( "histwalk" );
  phistwalk->Write( "phistwalk" );
  histtime_corr->Write( "histtime_corr" );
  outpufile->Close();
  
  return 0;
}
