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
	VParameters *fRunPara;
//	VGlobalRunParameter *fGlobal;

	TFile *fOutPutFile;

  public:

	VLoop( VParameters* );
	virtual ~VLoop() {}

	//void initialize();
	void loop();
	void normalizeData();

        vector<double> normalizeData( vector<double> fInVector);
        vector<double> orderData( vector<double> fInVector);
        vector<double> randomData( vector<double> fInVector, vector<double> fInVectorError );
        vector<vector <int> > matchDates( vector<double> a, vector<double> b );
        double runMooij( vector<double> a, vector<double> b );

        TGraphErrors *gCorrelation;
        TGraphErrors *gXrayLC;
        TGraphErrors *gTeVLC;

};

#endif 

