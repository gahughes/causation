#ifndef VParameter_H
#define VParameter_H

#include <TDatime.h>
#include <TNamed.h>
#include <TROOT.h>
#include <TSystem.h>

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string>

#include <VGlobalRunParameter.h>

using namespace std;

class VParameters
{

  private:

  public:

// Input Parameters:
	VParameters();
	~VParameters() {}

	void print();
	void initialise();

// Input Filenames
        string sOutPutFileName;
        string fTeVDataFile;
        string fXRayDataFile;
	int    iNumberOfTrials;
	float  fTimeWindow;

// Parameters read from LCs
        vector<double> fTeVDate;
        vector<double> fTeVeDate;
        vector<double> fTeVFlux;
        vector<double> fTeVFluxError;
        vector<double> fXRayDate;
        vector<double> fXRayeDate;
        vector<double> fXRayFlux;
        vector<double> fXRayFluxError;

};

#endif
