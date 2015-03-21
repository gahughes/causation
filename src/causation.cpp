#include <TApplication.h>
#include <TGClient.h>
#include <TMinuit.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStopwatch.h>

#include <string>
#include <vector>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#include <VReadRunParameter.h>
#include <VLoop.h>

using namespace std;

int main(int argc, char *argv[]) 
{

   int seed = time(NULL)*getpid();
   srand(seed);

// Read Runparameters and Commandline args
   VReadRunParameter *fReadRunParameter = new VReadRunParameter();
   if( !fReadRunParameter->readCommandline( argc, argv ) ) exit( -1 );

// Get the run parameters
   fReadRunParameter->getRunParameter()->initialise();
   fReadRunParameter->getRunParameter()->print();
// Do the reading if the light curves
   fReadRunParameter->readTeVData( fReadRunParameter->getRunParameter()->fTeVDataFile );
   fReadRunParameter->readXRayData( fReadRunParameter->getRunParameter()->fXRayDataFile );

// LOOP
   VLoop *fLoop = new VLoop( fReadRunParameter->getRunParameter() );
   //fTrace->initialize();
   fLoop->loop();
   
// Delete classes
   delete fLoop;
   delete fReadRunParameter;

   cout << "Program Finished Successfully." << endl;
   cout << endl;

   return 0;

}
