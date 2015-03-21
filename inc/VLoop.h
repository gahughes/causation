#ifndef VSEGMENTLOOP_H
#define VSEGMENTLOOP_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <TRandom3.h>

#include <VParameters.h>
#include <VGlobalRunParameter.h>

#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"



using namespace std;

class VLoop : VParameters
{

  private:
	TRandom3 *rand;
	VParameters *fRunPara; 		// run parameters

	TFile *fOutPutFile; 		// output root file

  public:

	VLoop( VParameters* );
	virtual ~VLoop() {}

	void loop();			// The main loop

	// Function to read in light curve and make it Gaussian with a width of 1
        vector<double> normalizeData( vector<double> fInVector);
	// Obsolete
        //vector<double> orderData( vector<double> fInVector);
	// Produce a new equally large vector of doubles based on the input and its errror
        vector<double> randomData( vector<double> fInVector, vector<double> fInVectorError );
	// Match the two light curves within the time window
        vector<vector <int> > matchDates( vector<double> a, vector<double> b );
	// Run algorithum 3 from the paper http://arxiv.org/abs/1412.3773
        double runMooij( vector<double> a, vector<double> b );

        TGraphErrors *gCorrelation;	// Correlation Plot
        TGraphErrors *gXrayLC;		// X-Ray Light Curve
        TGraphErrors *gTeVLC;		// TeV Light Curve

};

#endif 

