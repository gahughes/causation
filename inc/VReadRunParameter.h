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
        void printHelp();                         //!< print a short help
	
	VParameters *fRunPara;
        TRandom3 *fRandom;

    public:
        VReadRunParameter();
        ~VReadRunParameter() {}

	VParameters* getRunParameter()
	{
	  return fRunPara;
	}

        bool readCommandline( int argc, char *arg[] );
	void printStartMessage();
	void readTeVData(string a);
	void readXRayData(string a);

};
#endif
