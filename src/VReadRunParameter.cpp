#include <VReadRunParameter.h>

VReadRunParameter::VReadRunParameter()
{

    fDebug = false;
    if( fDebug ) cout << "VReadRunParameter::VReadRunParameter()" << endl;
    fRunPara = new VParameters();

}

bool VReadRunParameter::readCommandline( int argc, char *argv[] )
{

    int i = 1;
// no command line parameters
    if( argc == 1 )
    {
        printHelp();
        return false;
    }
// read all command line parameters
    while( i++ < argc )
    {
        string iTemp  = argv[i-1];
        string iTemp1 = argv[i-1];                // this is to get the camera name correctly
        string iTemp2 = "";
        if( i < argc )
        {
            iTemp2 = argv[i];
        }
// print help text
        if( iTemp.find( "help" ) < iTemp.size() )
        {
            printHelp();
            return false;
        }

	if( iTemp.find( "tevdata"  ) < iTemp.size() )
	{
	    fRunPara->fTeVDataFile = iTemp.substr( iTemp.rfind( "=" )+1, iTemp.size() ).c_str();
	} 

	if( iTemp.find( "xraydata"  ) < iTemp.size() )
	{
	    fRunPara->fXRayDataFile = iTemp.substr( iTemp.rfind( "=" )+1, iTemp.size() ).c_str();
	} 

	if( iTemp.find( "output"  ) < iTemp.size() )
	{
	    fRunPara->sOutPutFileName = iTemp.substr( iTemp.rfind( "=" )+1, iTemp.size() ).c_str();
	} 

	if( iTemp.find( "trials"  ) < iTemp.size() )
	{
	    fRunPara->iNumberOfTrials = atoi(iTemp.substr( iTemp.rfind( "=" )+1, iTemp.size() ).c_str());
	} 

	if( iTemp.find( "window"  ) < iTemp.size() )
	{
	    fRunPara->fTimeWindow = atof(iTemp.substr( iTemp.rfind( "=" )+1, iTemp.size() ).c_str());
	} 

    }

   if( fRunPara->fTeVDataFile == "" )
   {
     cout << "Error TeV File needed " << fRunPara->fTeVDataFile.c_str() << endl;
     cout << "Exiting ... " << endl;
     exit(-1);
   }

   if( fRunPara->fXRayDataFile == "" )
   {
     cout << "Error X-Ray File needed " << fRunPara->fXRayDataFile.c_str() << endl;
     cout << "Exiting ... " << endl;
     exit(-1);
   }

   printStartMessage();

   return true;

}
void VReadRunParameter::printHelp()
{

	printStartMessage();
	int temp = system("cat ../README/README.commandline");

}

void VReadRunParameter::printStartMessage()
{

  cout << endl;
  cout << "  Y |          / " << endl;
  cout << "    |         / " << endl;
  cout << "    |      __| " << endl;
  cout << "    |     / " << endl;
  cout << "    |   _/ " << endl;
  cout << "    |  / " << endl;
  cout << "    ------------------ " << endl;
  cout << "                   X " << endl;
  cout << " " << endl;
  cout << "Causation or just Correlation? " << endl;
  cout << " " << endl;
  cout << "Gareth Hughes " << endl;
  cout << "ETH Zurich " << endl;
  cout << "ghughes@phys.ethz.ch " << endl;
  cout << " " << endl;
  cout << endl;


}

void VReadRunParameter::readXRayData( string fInfile )
{

  vector<double> day;
  vector<double> eday;
  vector<double> flux;
  vector<double> eflux;

  string line;
  string temp;

  ifstream myfile;
  myfile.open ( fInfile.c_str() );

  if (myfile.is_open())
  {
    while ( getline(myfile,line) )
    {

      istringstream stream( line );

      while( !stream.eof() )
      {

        stream >> temp; 
        day.push_back(atof(temp.c_str()));
        eday.push_back(0.);

        stream >> temp; 
        flux.push_back(atof(temp.c_str()));

        stream >> temp; 
        eflux.push_back(atof(temp.c_str()));

      }

    }
    myfile.close();
  }
  else cout << "Unable to open file " << fInfile.c_str() << endl;; 

  myfile.close();

  fRunPara->fXRayDate      = day;
  fRunPara->fXRayeDate     = eday;
  fRunPara->fXRayFlux      = flux;
  fRunPara->fXRayFluxError = eflux;

}
void VReadRunParameter::readTeVData( string fInfile )
{

  vector<double> day;
  vector<double> eday;
  vector<double> flux;
  vector<double> eflux;

  string line;
  string temp;

  ifstream myfile;
  myfile.open ( fInfile.c_str() );

  if (myfile.is_open())
  {
    while ( getline(myfile,line) )
    {

      istringstream stream( line );

      while( !stream.eof() )
      {

        stream >> temp; 
        day.push_back(atof(temp.c_str()));
        eday.push_back(0.);

        stream >> temp; 
        flux.push_back(atof(temp.c_str()));

        stream >> temp; 
        eflux.push_back(atof(temp.c_str()));

      }

    }
    myfile.close();
  }
  else cout << "Unable to open file " << fInfile.c_str() << endl;; 

  myfile.close();

  fRunPara->fTeVDate      = day;
  fRunPara->fTeVeDate     = eday;
  fRunPara->fTeVFlux      = flux;
  fRunPara->fTeVFluxError = eflux;

}


