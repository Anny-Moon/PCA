#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "File.h"
#include "Polymer.h"
#include "PolymerScaling.h"

using namespace PCA;

int main(int np, char **p)
{	
    double tmp;
    char str [100];
    
    if(p[1]==NULL){
	printf("\tGive me the name of the chain as the argument.\n");
	printf("\tThen I will open 'data/xyz_<name>.dat'.\n");
	printf("\tFor example: ./pca 5dn7\n");
	exit(1);
    }
    
    if(p[2]==NULL){
	printf("------------------------\n");
	printf("If you have several chains of the same size in the file ");
	printf(" and want me to consider it like statistics, then pass 's' ");
	printf("(or any symbol) as the second argument\n");
	printf("------------------------\n");
    }
    
    sprintf(str,"data/xyz_%s.dat",p[1]); //name of input file
    
    char resultFile[100];
    sprintf(resultFile,"results/%s_totalAngleVSsteps.dat",p[1]); //name of output file with total angle
    
    char confFile[100];
    sprintf(confFile,"results/%s_configurartions.dat",p[1]);
    
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    char scalingParamFile[100];
    sprintf(scalingParamFile,"results/%s_scalingParam.dat",p[1]);
    
    
//    globalVerbose = false;
//    PolymerScaling::setVerbose(false);

    Polymer polymer(str,0,1);
    polymer.setMonomerLengthsFromRadiusVectors();
    
//    FILE  *lfp;
//    lfp=fopen("results/lengths.dat","w");
//    polymer.writeMonomerLengthsInFile(lfp);
//    fclose(lfp);

    tmp = PolymerScaling::findCriticalScalingParam(polymer.getNumMonomers());
    PolymerScaling::ScalingParam sp(tmp);
    
    if(p[2]==NULL){ //scaling without statistics
	PolymerScaling::observableVSscalingSteps(
	    PolymerScaling::Observable::totalAngle,
    	    polymer,
    	    sp,
    	    resultFile,
    	    confFile,
    	    numMonomersFile,
    	    scalingParamFile
    	);
    }
    
    else{ //scaling with statistics
	printf("------------------------\n");
	printf("I will take all the chains from the file '%s' ", str);
	printf("for the statistics.\n");
	printf("------------------------\n");

	
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
	    printf("All the chains in your file should be of the same size. ");
	    printf("But it is not the case.\nLook:\n");
	    File::showNumberOfLinesInBlocks(str);
	    exit(1);
	}
    }
printf("Everything is OK!\n");
return 0;
}