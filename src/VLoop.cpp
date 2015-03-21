
#include "VLoop.h"

VLoop::VLoop( VParameters *irunpara  )
{

  // Run Parameters
  fRunPara = irunpara;

  // Randoms
  int seed = time(NULL)*getpid();
  rand = new TRandom3(seed);

  // Outout root file
  fOutPutFile = new TFile(fRunPara->sOutPutFileName.c_str(),"RECREATE");

}

void VLoop::loop()
{

   // Cxy and Cyx from Algo 3
   double C_tev_xray = 0.;
   double C_xray_tev = 0.;

   // The square of the above
   double C_tev_xray2 = 0.;
   double C_xray_tev2 = 0.;

   // Double vector of ints representing the matched values from each light curve
   vector< vector<int> > iMatched = matchDates( fRunPara->fXRayDate, fRunPara->fTeVDate );

   // Data and error vectors
   vector<double> fTeVData;
   vector<double> fTeVError;
   vector<double> fXRayData;
   vector<double> fXRayError;

   // Add the correct matched values from the LCs
   for( unsigned int i = 0; i < iMatched.size(); i++ )
   {

      fXRayData.push_back( fRunPara->fXRayFlux[iMatched[i][0]] );
      fXRayError.push_back( fRunPara->fXRayFluxError[iMatched[i][0]] );

      fTeVData.push_back( fRunPara->fTeVFlux[iMatched[i][1]] );
      fTeVError.push_back( fRunPara->fTeVFluxError[iMatched[i][1]] );

   }

// Create the output graphs

//  Correllated plots
  Int_t iMatch = iMatched.size();
  gCorrelation = new TGraphErrors(iMatch,&fTeVData[0],&fXRayData[0],&fTeVError[0],&fXRayError[0]);
  gCorrelation->SetTitle("");
  gCorrelation->GetXaxis()->SetTitle("TeV Data");
  gCorrelation->GetYaxis()->SetTitle("X-ray Data");
  gCorrelation->SetName("gCorrelation");
  gCorrelation->Write();

// TeV LC
  Int_t iTeVLC = fRunPara->fTeVDate.size();
  gTeVLC = new TGraphErrors(iTeVLC,&fRunPara->fTeVDate[0],&fRunPara->fTeVFlux[0],&fRunPara->fTeVeDate[0],&fRunPara->fTeVFluxError[0]);
  gTeVLC->SetTitle("");
  gTeVLC->GetXaxis()->SetTitle("MJD");
  gTeVLC->GetYaxis()->SetTitle("TeV Flux");
  gTeVLC->SetName("gTeVLC");
  gTeVLC->Write();

// X-Ray LC
  Int_t iXRayLC = fRunPara->fXRayDate.size();
  gXrayLC = new TGraphErrors(iXRayLC,&fRunPara->fXRayDate[0],&fRunPara->fXRayFlux[0],&fRunPara->fXRayeDate[0],&fRunPara->fXRayFluxError[0]);
  gXrayLC->SetTitle("");
  gXrayLC->GetXaxis()->SetTitle("MJD");
  gXrayLC->GetYaxis()->SetTitle("X-ray Flux");
  gXrayLC->SetName("gXrayLC");
  gXrayLC->Write();

// Close the output file
  fOutPutFile->Close();

  for( int k = 0; k < fRunPara->iNumberOfTrials; k++ )
  {

// Create the Randomized data from the matched sets
    vector<double> randomTeV  = randomData( fTeVData, fTeVError);  
    vector<double> randomXRay = randomData( fXRayData, fXRayError);  

// Normalize these data to gaussian with width 1
    vector<double> normalTeV  = normalizeData( randomTeV );
    vector<double> normalXRay = normalizeData( randomXRay );

// Calculate from algo 3
    double temp1 = runMooij( normalTeV, normalXRay );
    double temp2 = runMooij( normalXRay, normalTeV );

// Add up the answers
    C_tev_xray += temp1;
    C_xray_tev += temp2;

// Add up the squares
    C_tev_xray2 += temp1*temp1;
    C_xray_tev2 += temp2*temp2;

  }

// Calc the average
  double C_tev_xray_mean = C_tev_xray/fRunPara->iNumberOfTrials;
  double C_tev_xray_error = sqrt(C_tev_xray2/fRunPara->iNumberOfTrials-(C_tev_xray/fRunPara->iNumberOfTrials)*(C_tev_xray/fRunPara->iNumberOfTrials));

// Calc the average
  double C_xray_tev_mean = C_xray_tev/fRunPara->iNumberOfTrials;
  double C_xray_tev_error = sqrt(C_xray_tev2/fRunPara->iNumberOfTrials-(C_xray_tev/fRunPara->iNumberOfTrials)*(C_xray_tev/fRunPara->iNumberOfTrials));

// Output the answer
  cout << C_tev_xray_mean << " +/- " << C_tev_xray_error << endl;
  cout << C_xray_tev_mean << " +/- " << C_xray_tev_error << endl;

  cout << endl;
  if( C_tev_xray_mean < ( C_xray_tev_mean - fabs(C_xray_tev_error + C_tev_xray_error) ) )
    cout << "TeV Causes X-Ray" << endl;
  else if( C_tev_xray_mean > ( C_xray_tev_mean + fabs(C_xray_tev_error + C_tev_xray_error) ) )
    cout << "X-Ray Causes TeV" << endl;
  else
    cout <<  "Uncertain!" << endl;
  cout << endl;

}

// Normalize a vector to the same mean but with a 1 sigma width
vector<double> VLoop::normalizeData( vector<double> fInVector)
{


  if( fInVector.size() == 0 )
  {
    cout << "Vector has 0 size!" << endl;
    exit(-1);
  }

  double sum  = 0.;
  double sum2 = 0.;

  for( unsigned int i = 0; i < fInVector.size(); i++ )
  {
    sum  += fInVector[i];
    sum2 += fInVector[i]*fInVector[i];
  }

  double mean = sum/fInVector.size();
  double var = sum2/fInVector.size() - (sum/fInVector.size())*(sum/fInVector.size());
  double sigma = 0. ;

  if( var >= 0. )
    sigma = sqrt(var);

  vector<double> out;

  for( unsigned int i = 0; i < fInVector.size(); i++ )
    out.push_back( mean + (fInVector[i]-mean)/sigma );

  return out;

}

// Obsolete
/*
vector<double> VLoop::orderData( vector<double> fInVector)
{


  if( fInVector.size() == 0 )
  {
    cout << "Vector has 0 size!" << endl;
    exit(-1);
  }

  vector<double> out = fInVector;
  double temp1;
  double temp2;

// Bubble Sort

  bool bSwapped = true;
  while( bSwapped )
  {
    bSwapped = false;
    for( int unsigned i = 1; i < out.size(); i++ )
    {
      if( out[i] < out[i-1] )
      {

        temp1 = out[i-1];
        temp2 = out[i];
        out[i]   = temp1;
        out[i-1] = temp2;
	
	bSwapped = true;

      }
    }
  }

  return out;

}
*/
// Create Random Vector from input vector and its errors
vector<double> VLoop::randomData( vector<double> fInVector, vector<double> fInVectorError )
{


  if( fInVector.size() == 0 )
  {
    cout << "Vector has 0 size!" << endl;
    exit(-1);
  }

  vector<double> out;

  for( unsigned int i = 0; i < fInVector.size(); i++ )
  {
    out.push_back( rand->Gaus(fInVector[i],fInVectorError[i]) );
  }

  return out;

}

// Do algorithum 3 from the paper
double VLoop::runMooij( vector<double> fInX, vector<double> fInY )
{

  double sum = 0.;

// Check everything is ok
  if( fInX.size() != fInY.size() || fInX.size() == 0 || fInY.size() == 0 )
  {
    cout << "This is not going to work!" << endl;
    exit(-1);
  }

  double temp1;
  double temp2;
  double temp3;
  double temp4;

// Bubble Sort

  bool bSwapped = true;
  while( bSwapped )
  {
    bSwapped = false;
    for( int unsigned i = 1; i < fInX.size(); i++ )
    {
      if( fInX[i] < fInX[i-1] )
      {

        temp1 = fInX[i-1];
        temp2 = fInX[i];
        fInX[i]   = temp1;
        fInX[i-1] = temp2;

        temp3 = fInY[i-1];
        temp4 = fInY[i];
        fInY[i]   = temp3;
        fInY[i-1] = temp4;
	
	bSwapped = true;

      }
    }
  }

  for( unsigned int i = 0; i < fInX.size() - 1; i++ )
  {
    if( fInX[i+1] == fInX[i] ) cout << "Ek " << endl;
    if( fInX[i+1] < fInX[i] ) cout << "hmmmm " << endl;
    sum += log(fabs(fInY[i+1]-fInY[i])/(fInX[i+1]-fInX[i]));
  }
  sum /= fInX.size();

  return sum;

}

// Match the dates from the LCs
vector< vector<int> > VLoop::matchDates( vector<double> fInX, vector<double> fInT )
{

   vector<int> temp;
   vector< vector<int> > out;

   for( unsigned int i = 0; i < fInX.size(); i++ )
   {

     for( unsigned int j = 0; j < fInT.size(); j++ )
     {

       if( fabs(fInX[i] - fInT[j]) < fRunPara->fTimeWindow )
       {
         temp.push_back(i);
         temp.push_back(j);
         out.push_back(temp);
         temp.resize(0);
       }

     }

   }

  return out;

}
