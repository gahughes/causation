#ifndef VGLOBALRUNPARAMETER_H
#define VGLOBALRUNPARAMETER_H

#include <TChain.h>
#include <TSystem.h>
#include <TTree.h>
#include <TROOT.h>

#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TH1F.h"

#include "Math/Functor.h"
#include "Math/WrappedFunction.h"
#include "Math/IFunction.h"
#include "Math/Integrator.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

// Global Defines Stuff
// GEOMETERY
#define PI		3.1415
#define D2R             PI/180.0
#define R2D             180.0/PI
#define NDIM		3
#define NANG		7	

using namespace std;

class VGlobalRunParameter
{


  private:

//	TTree *outTree;

  public:

	VGlobalRunParameter();
	~VGlobalRunParameter() {}



};

#endif
