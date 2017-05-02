#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Utilities.h"
#include "File.h"
#include "Polymer.h"
#include "PolymerObservable.h"
#include "PolymerScaling.h"
#include "DataHandler.h"
//#include <string>

using namespace PCA;
using namespace std;

int main(int np, char **p)
{	
    double tmp;
    char str [100];
    bool currentVerbose;
    
    if(p[1]==NULL){
	printf("------------------------\n");
	printf("Give me the name of the chain as the argument.\n");
	printf("Then I will open 'data/xyz_<name>.dat'.\n");
	printf("For example: ./pca 5dn7\n");
	printf("I will calculate total angle VS number of scaling step.\n");
	printf("------------------------\n");
	printf("If you have more than one chain (which should be separated ");
	printf("with one ore more empty lines) in that file, then I will take all of them ");
	printf("for the statistics. All chains should have same number of sites in this case.\n");
	printf("------------------------\n");
	printf("\n");
	exit(1);
    }
    
    sprintf(str,"xyz_%s.dat",p[1]); //name of input file
    sprintf(str,"%s",DataHandler::fullName(str).c_str());
    _PCA_CHECK_BLOCKS_SIZE_IN_FILE(str);
    
    
    char confFile[100];
    sprintf(confFile,"results/%s_configurations.dat",p[1]);
    
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    char scalingParamFile[100];
    sprintf(scalingParamFile,"results/%s_scalingParam.dat",p[1]);
    
    
    globalVerbose = false;
//    PolymerScaling::setVerbose(false);
    char* resultFile;
    Polymer* polymer;
    
    printf("------------------------\n");
    printf("I will calculate dependency of total angle on scaling step\n");
    printf("------------------------\n");
	
	
    polymer = new Polymer(str,0,1);
    tmp = PolymerScaling::findCriticalScalingParam(polymer->getNumMonomers());
    PolymerScaling::ScalingParam sp(tmp);
    delete polymer;
	
	
	
    for (int k=1;k<=2;k++){
	printf("k = %i\n",k);
	resultFile = new char [100];
	sprintf(resultFile,"results/%s_k%iVSsteps.dat",p[1],k); //name of output file with total angle
    
//	    currentVerbose = globalVerbose;
//	    globalVerbose = false;
//	    polymer = new Polymer(str,0,1);
//	    globalVerbose = currentVerbose;

//	    FILE* lengthsFp;
//	    lengthsFp = fopen("lengths.dat", "w");
//    	    polymer->setMonomerLengthsFromRadiusVectors();
//    	    polymer->writeMonomerLengthsInFile(lengthsFp);
//    	    fclose(lengthsFp);
        
        
    	//    printf("Radius of gyration: %g\n\n", PolymerObservable::radiusOfGyration(polymer));
        
	    

	PolymerScaling::observableVSscalingStepsWithStatistics(
	    PolymerScaling::Observable::totalAngle,
//		PolymerScaling::Observable::test,
//		PolymerScaling::Observable::averageMonomersLength,
	    str,
	    0,
	    sp,
	    resultFile,
	    confFile,
	    numMonomersFile,
	    scalingParamFile,
	    k
	);
//	    delete polymer;
	delete [] resultFile;
//	    Timer::tock(k);    
    }
    
    printf("Everything is OK!\n");
return 0;
}