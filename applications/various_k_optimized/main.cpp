/*  Copyright 2018 Anna Sinelnikova
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Utilities.h"
#include "FileHandler/FilePCA.h"
#include "Polymer.h"
#include "PolymerObservable.h"
#include "PolymerScaling.h"
#include "DataHandler.h"
#include "Logo.h"

using namespace PCA;
using namespace std;

int main(int np, char **p)
{	
    Logo::print();

    if(p[1]==NULL){
	printf("------------------------\n");
	printf("Give me the name of the chain as the argument.\n");
	printf("Then I will open 'data/<name>.pca'.\n");
	printf("For example: ./pca 1abs\n");
	printf("I will calculate total angle VS number of scaling step for different k values.\n");
	printf("------------------------\n");
	printf("\n");
	exit(1);
    }
    
    printf("------------------------\n");
    printf("I will calculate dependency of total angle on scaling step for\n");
    printf("different values of 'k' (excluded from summation terms)\n");
    printf("------------------------\n");
    
    printf("Polymer name: %s\n", p[1]);    
    
    // create the full name of the input file
    char str [100];
    sprintf(str,"%s.pca",p[1]); //name of input file
    DataHandler::setPath("");// write your own path if you want;
    sprintf(str,"%s",DataHandler::fullName(str).c_str());
    
    int confNumber = 0; //number of chain in file
    FilePCA reader(str,confNumber); // can be any reader, a child class from FileCoordinates
    
    // name of output file with configurations
    char confFile[100];
    sprintf(confFile,"results/%s_rescaled.pca",p[1]);
    
    // name of output file with number of monomers during scaling procedure
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    // name of output file with scaling parameter during scaling procedure
    char* scalingParamFile;
    scalingParamFile = new char [1000];
    sprintf(scalingParamFile,"results/%s_scalingParam.dat",p[1]); 
    
    
    
    // scaling
    std::vector<Polymer> polymer = PolymerScaling::scalingArray(str, scalingParamFile);
    delete [] scalingParamFile;
    
    // print configurations and their length in files
    FILE *confFp, *numMonomersFp;
    confFp = fopen(confFile, "w");
    numMonomersFp = fopen(numMonomersFile, "w");
    
    for (int i=0;i<polymer.size();i++){
	polymer[i].setRadiusVectorsFromVectorsT();
	polymer[i].writeRadiusVectorsInFile(confFp);
	fprintf(confFp,"\n");
	
	fprintf(numMonomersFp,"%i\n",polymer[i].getNumMonomers());
    }
    
    fclose(confFp);
    fclose(numMonomersFp);
    
    // calculate Total Angle for different values of k and print in files
    int N = polymer[0].getNumMonomers();
    double answ;
    char* resultFile;
    FILE* resultFp;
    
    for (int k=1;k<N-10;k++){
	//printf("k = %i\n",k);
	resultFile = new char [1000];
	sprintf(resultFile,"results/%s_k%iVSsteps.dat",p[1],k); //name of output file with total angle
	resultFp = fopen(resultFile, "w");
	    for (int i=0;i<=polymer.size()-k;i++){
		answ=PolymerObservable::totalAngle(polymer[i], k);
		fprintf(resultFp,"%i\t%.15le\n", i, answ);
	    }
	delete [] resultFile;
	fclose(resultFp);
    }
    printf("Everything is OK!\n");
    
return 0;
}