#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "File.h"
#include "Polymer.h"
#include "PolymerScaling.h"
#include "Logo.h"

using namespace PCA;

int main(int np, char **p)
{	
    double tmp;
    char str [100];
    bool currentVerbose;
    
    Logo::print();
    
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
	printf("------------------------\n");
	printf("Pass me 'n' (or any other symbol) as the second argument ");
	printf("and I will not calculate totalAngle or anything else during scaling ");
	printf("procedure. It will save your time if you are inteested only in scaling ");
	printf("procedure itself (i.e. smoothing curve). ");
	printf("I will take only the first chain from the file you gave me.\n");
	printf("------------------------\n");
	exit(1);
    }
    
    sprintf(str,"data/xyz_%s.dat",p[1]); //name of input file
    
    char resultFile[100];
    
    char confFile[100];
    sprintf(confFile,"results/%s_configurations.dat",p[1]);
    
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    char scalingParamFile[100];
    sprintf(scalingParamFile,"results/%s_scalingParam.dat",p[1]);
    
    
//    globalVerbose = false;
//    PolymerScaling::setVerbose(false);

    

    if(p[2]==NULL){
	printf("------------------------\n");
	printf("I will calculate dependency of total angle on scaling step\n");
	printf("------------------------\n");
	sprintf(resultFile,"results/%s_totalAngleVSsteps.dat",p[1]); //name of output file with total angle
	
	currentVerbose = globalVerbose;
	globalVerbose = false;
	Polymer polymer(str,0,1);
	globalVerbose = currentVerbose;
	
        polymer.setMonomerLengthsFromRadiusVectors();
	tmp = PolymerScaling::findCriticalScalingParam(polymer.getNumMonomers());
	PolymerScaling::ScalingParam sp(tmp);
    
	if(File::checkAllBlocksHaveTheSameSize(str)){
	    PolymerScaling::observableVSscalingStepsWithStatistics(
		PolymerScaling::Observable::totalAngle,
		str,
		0,
		sp,
		resultFile,
		confFile,
		numMonomersFile,
		scalingParamFile
	    );
	}

	else{
	    printf("Error:\n");
	    printf("All the chains in your file should be of the same size. ");
	    printf("But it is not the case.\nLook:\n");
	    File::showNumberOfLinesInBlocks(str);
	    exit(1);
	}
    }
    
    else{
	printf("------------------------\n");
	printf("I will perform scaling procedure without calculating any functions.\n");
	printf("If it is not what you wanted, don't pass me the second argument when you call me\n");
	printf("------------------------\n");
	
	Polymer polymer(str,0,1);
	polymer.setMonomerLengthsFromRadiusVectors();
	tmp = PolymerScaling::findCriticalScalingParam(polymer.getNumMonomers());
	PolymerScaling::ScalingParam sp(tmp);
    
	
	sprintf(resultFile,"results/%s_scalingParamVSsteps.dat",p[1]); //name of output file with total angle
	PolymerScaling::observableVSscalingSteps(
	    PolymerScaling::Observable::scalingParameter,
	    polymer,
	    sp,
	    resultFile,
	    confFile,
	    numMonomersFile,
	    NULL
	);
    }

printf("Everything is OK!\n");
return 0;
}