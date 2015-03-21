#include "VParameters.h"

VParameters::VParameters()
{

	fTeVDataFile = "";
	fXRayDataFile = "";
	iNumberOfTrials = 1000;
	fTimeWindow = 1.;
	sOutPutFileName = "";

}

void VParameters::initialise()
{

   

}

void VParameters::print()
{

	cout << "TeV Data:         " << fTeVDataFile.c_str() << endl;
	cout << "X-Ray Data:       " << fXRayDataFile.c_str() << endl;
	cout << "Number of Trials: " << iNumberOfTrials << endl;
	cout << "Time Window:      " << fTimeWindow << endl;
	cout << "Output File:      " << sOutPutFileName.c_str() << endl;
	cout << endl;

}
