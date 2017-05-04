/*  Copyright 2017 Anna Sinelnikova
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
#include "Vector.h"
#include "Utilities.h"
#include "File.h"
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
	printf("Then I will open 'data/xyz_<name>.dat'.\n");
	printf("For example: ./pca 5dn7\n");
	printf("------------------------\n");
	printf("If you have more than one chain (which should be separated ");
	printf("with one ore more empty lines) in that file, I will take all of them ");
	printf("for the statistics. All chains should have same number of sites in this case.\n");
	printf("------------------------\n");
	printf("\n");
	exit(1);
    }
    
    printf("------------------------\n");
    printf("I will perform rescaling procedure.\n");
    printf("------------------------\n");
    
    printf("Polymer name: %s\n", p[1]);
    // create the full name of the input file
    char str [100];
    sprintf(str,"xyz_%s.dat",p[1]); //name of input file
    sprintf(str,"%s",DataHandler::fullName(str).c_str());
    
    // name of output file with configurations
    char confFile[100];
    sprintf(confFile,"results/%s_configurations.dat",p[1]);
    
    // name of output file with number of monomers during scaling procedure
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    // name od output file with scaling parameter VS step
    char* resultFile;
    resultFile = new char [100];
    sprintf(resultFile,"results/%s_scalingParamVSsteps.dat",p[1]); 
    
    // finding optimal scaling parameter
    Polymer polymer(str,0,1);
    double tmp;
    tmp = PolymerScaling::findCriticalScalingParam(polymer.getNumMonomers());
    PolymerScaling::ScalingParam sp(tmp);
    
		
    // scaling
    PolymerScaling::observableVSscalingSteps(
	PolymerScaling::Observable::scalingParameter,
	 polymer,
	sp,
	resultFile,
	confFile,
	numMonomersFile,
	NULL
    );
    
    delete [] resultFile;
    
    printf("Everything is OK!\n");
    
return 0;
}