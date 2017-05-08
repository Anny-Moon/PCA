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
	printf("You can also give me 'k' as the second argument. Otherwise I will put k = 10.\n");
	printf("I will calculate total angle with k number of excludet terms VS number of scaling step.\n");
	printf("------------------------\n");
	printf("If you have more than one chain (which should be separated \n");
	printf("with one ore more empty lines) in that file, I will take all of them \n");
	printf("for the statistics. All chains should have same number of sites in this case.\n");
	printf("------------------------\n");
	printf("\n");
	exit(1);
    }
    
    printf("Polymer name: %s\n", p[1]);
    globalVerbose = false;
    
    // create the full name of input file
    char str [100];
    sprintf(str,"xyz_%s.dat",p[1]);
    DataHandler::setPath("");// write your own path if you want;
    sprintf(str,"%s",DataHandler::fullName(str).c_str());
    
    //checking that all chains in the file have the same size, so can be taken for statistics
    _PCA_CHECK_BLOCKS_SIZE_IN_FILE(str);
    printf("Number of blocks: %i\n",File::countBlocks(str));
    printf("Number of sites in each block: %i\n",File::countLinesInBlock(str));
    
    // name of output file with configurations
    char confFile[100];
    sprintf(confFile,"results/%s_configurations.dat",p[1]);
    
    // name of output file with number of monomers during scaling procedure
    char numMonomersFile[100];
    sprintf(numMonomersFile,"results/%s_numMonomers.dat",p[1]);
    
    // name of output file with scaling parameter
    char scalingParamFile[100];
    sprintf(scalingParamFile,"results/%s_scalingParam.dat",p[1]);
    
    // finding optimal scaling parameter
    Polymer* polymer;	
    polymer = new Polymer(str,0,1);
    double tmp;
    int N = polymer->getNumMonomers();
    tmp = PolymerScaling::findCriticalScalingParam(N);
    PolymerScaling::ScalingParam sp(tmp);
    
    delete polymer;
    
    //number of excluded terms from summation in the observable
    int k = 10;
    if(p[2]!=NULL)
	k = atoi(p[2]);
    
    printf("k = %i\n",k);
    
    // name of main output file
    char* resultFile;
    resultFile = new char [100];
    sprintf(resultFile,"results/%s_k%iVSsteps.dat",p[1],k); //name of output file with total angle
    
    
    
    // scaling
    PolymerScaling::observableVSscalingStepsWithStatistics(
	PolymerScaling::Observable::totalAngle,
	str,
	0,
	sp,
	resultFile,
	confFile,
	numMonomersFile,
	scalingParamFile,
	k
    );
    
    delete [] resultFile;
    printf("Everything is OK!\n");
return 0;
}