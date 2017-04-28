#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Utilities.h"
#include "File.h"
#include "Polymer.h"
#include "PolymerObservable.h"
#include "PolymerScaling.h"

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
	printf("------------------------\n");
	printf("Pass me 'n' (or any other symbol) as the second argument ");
	printf("and I will not calculate totalAngle or anything else during scaling ");
	printf("procedure. It will save your time if you are inteested only in scaling ");
	printf("procedure itself (i.e. smoothing curve). ");
	printf("I will take only the first chain from the file you gave me.\n");
	printf("------------------------\n");
	exit(1);
    }
    
//    sprintf(str,"../../data/xyz_%s.dat",p[1]); //name of input file
    sprintf(str,"xyz_%s.dat",p[1]); //name of input file

    
    
    
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
    
    if(p[2]==NULL){
	printf("------------------------\n");
	printf("I will calculate dependency of total angle on scaling step\n");
	printf("------------------------\n");
	
	
	polymer = new Polymer(str,0,1);
	tmp = PolymerScaling::findCriticalScalingParam(polymer->getNumMonomers());
	PolymerScaling::ScalingParam sp(tmp);
	delete polymer;
	
	
	
	for (int k=1;k<=2;k++){
//	    Timer::tick(k);
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
        
	    

//	    if(File::checkAllBlocksHaveTheSameSize(str)){
		PolymerScaling::observableVSscalingStepsWithStatistics(
			PolymerScaling::Observable::totalAngle,
//			PolymerScaling::Observable::test,
//			PolymerScaling::Observable::averageMonomersLength,
			str,
			0,
			sp,
			resultFile,
			confFile,
			numMonomersFile,
			scalingParamFile,
			k
		);
//	    }

/*	    else{
		printf("Error:\n");
		printf("All the chains in your file should be of the same size. ");
		printf("But it is not the case.\nLook:\n");
		File::showNumberOfLinesInBlocks(str);
		exit(1);
	    }
	    */
//	    delete polymer;
	    delete [] resultFile;
//	    Timer::tock(k);    
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
    
    
/*
// histograms during scaling
{
    Polymer* polymerP;
    polymerP = new Polymer (str,0,1);
    
    char str_hist[100];
    int i, j, k, numMonomers;
    double tmp, answ;
    FILE *fp, *fpN;
    
    fpN = fopen (numMonomersFile, "w");
    numMonomers = polymerP->getNumMonomers();
    tmp = PolymerScaling::findCriticalScalingParam(numMonomers);
    PolymerScaling::ScalingParam sp(tmp);
    
    for(k=0; numMonomers>5; k++){
	printf("N = %i\n", numMonomers);
	sprintf(str_hist,"results/histograms/%s_dist_cos_%i.dat",p[1], k);
	fp = fopen(str_hist, "w");
    
	const Vector* t = polymerP->getVectorsT();
	numMonomers = polymerP->getNumMonomers();
	answ = 0;
	for(i=0;i<numMonomers;i++){
	    for(j=i+1;j<numMonomers;j++){
		if(abs(i-j)>4){
		    tmp = Vector::dotProduct(t[i],t[j]) / (t[i].norm() * t[j].norm());
		    answ+=tmp;
		    fprintf(fp,"%g\n", tmp);
		}
	    }
	}
        
	fclose(fp);
	PolymerScaling::scalingLoop(&polymerP, sp, NULL, fpN,NULL,50);
    }
    fclose (fpN);
    delete polymerP;
}
*/
    printf("Everything is OK!\n");
return 0;
}