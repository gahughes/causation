//! VReadRunParameter  reader for runparameter (now from command line, later from configuration file)

#ifndef VREADRUNPARAMETER_H
#define VREADRUNPARAMETER_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <TRandom3.h>

#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

#include <VParameters.h>

class VReadRunParameter 
{

    private:
        bool fDebug;
        void printHelp();               //!< print a short help
	
	VParameters *fRunPara;		// The run parameters
        TRandom3 *fRandom;

    public:
        VReadRunParameter();
        ~VReadRunParameter() {}

	// Returns the run parameters
	VParameters* getRunParameter() { return fRunPara; }

	// Read the command line args
        bool readCommandline( int argc, char *arg[] );
	// Just a pretty picture
	void printStartMessage();
	// Read in the light curves
	void readTeVData(string a);
	void readXRayData(string a);

};
#endif
