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

/** @package PCA
*   @file PolymerScaling.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#include "../include/PolymerScaling.h"
#include "../include/Polymer.h"
#include "../include/PolymerObservable.h"
#include "../include/Utilities.h"
#include "../include/File.h"
#include "../include/FileHandler/FilePCA.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "PCAmacros.h"

namespace PCA{

double PolymerScaling::ScalingParam::ACCURACY = 1e4;
bool PolymerScaling::verbose = true;
bool PolymerScaling::optimalScalingParam = true;


PolymerScaling::ScalingParam::ScalingParam(double s_in)
{
    s = s_in;
    findEverythingFromS();
}


PolymerScaling::ScalingParam::ScalingParam(int numerator_in, int denominator_in, int intPart_in)
{
    intPart = intPart_in;
    numerator = numerator_in;
    denominator = denominator_in;
    
    fracPart = (double)numerator/(double)denominator;
    s = (double)intPart + fracPart;
}

PolymerScaling::ScalingParam::ScalingParam(const ScalingParam& sp)
{
    s = sp.s;
    intPart = sp.intPart;
    numerator = sp.numerator;
    denominator = sp.denominator;
    fracPart = sp.fracPart;
}

PolymerScaling::ScalingParam::~ScalingParam(){};

void PolymerScaling::ScalingParam::format(double s_in)
{
    s = s_in;
    findEverythingFromS();
}

void PolymerScaling::ScalingParam::findEverythingFromS()
{
    
    double tmpIntPart;// indeed, for std::modf(..) intPart should be double
    double divisor;
    
    fracPart = modf (s, &tmpIntPart);
    intPart = (int)tmpIntPart;

    if((int)(fracPart*ACCURACY*ACCURACY)==0){
	numerator = 1;
	denominator = 1;
	fracPart = 1.0;
	intPart = intPart - 1;
    }

    else{
	numerator = (int)(fracPart * ACCURACY);
	denominator = ACCURACY;
	
	if(numerator==0){
	    printf("Error in ScalingParam::findEverythingFromS:\nnot enough accuracy for this scaling parameter.\n");
	    exit(1);
	}

	divisor = numerator;
	while(divisor != 1){
    	    divisor = PCA::commonDivisor(numerator, denominator, divisor);
    	    numerator = numerator / divisor;
    	    denominator = denominator / divisor;
	}
    
    }
}

double PolymerScaling::findCriticalScalingParam(int numMonomers)
{
    return (double)numMonomers/(double)(numMonomers-1);
}

int PolymerScaling::findNewScalingParam(int oldNumMonomers, const ScalingParam& etalonS, ScalingParam* newS)
{

    int newNumMonomers;
    double tmp;
        //etalonS->fracpart=(double)*numeratorS/(double)*denominatorS;

    tmp = (double)oldNumMonomers  / etalonS.s;
    newNumMonomers=PCA::rounding(tmp);
    
    if(newNumMonomers == oldNumMonomers)
	newNumMonomers = oldNumMonomers - 1;

    
    newS->format((double)oldNumMonomers / (double)newNumMonomers);
return newNumMonomers;
}

void PolymerScaling::scaling(Polymer** polymer, const ScalingParam& etalonS, ScalingParam* newS)
{
    int i,k;
    int addExtraMonomer;
    int numMonomers, newNumMonomers, partsToAdd, monomersToAdd;
    const Vector* t;
    Vector* newT;
    int tmpIndex;
    Vector tmpVector;
    
    t = (*polymer)->getVectorsT();
    numMonomers = (*polymer)->getNumMonomers();
    
    if(optimalScalingParam)
	newNumMonomers = PolymerScaling::findNewScalingParam(numMonomers, etalonS, newS);
    
    else{
	*newS=etalonS;
	newNumMonomers = numMonomers/newS->s;
	if(newNumMonomers==numMonomers)
	    newNumMonomers = numMonomers - 1;
    }
    
    newT = new Vector [newNumMonomers];
    
    tmpIndex = 0;
    partsToAdd = newS->numerator;
    addExtraMonomer = 0;

    for(i=0;i<newNumMonomers;i++){
	
	k = i % newS->denominator;

        if(k==0){
    	    monomersToAdd = 0;
            newT[i] = t[tmpIndex+addExtraMonomer];
            tmpIndex = tmpIndex + addExtraMonomer;

            while(monomersToAdd < newS->intPart - 1){
        	newT[i] = newT[i] + t[tmpIndex+1];
                tmpIndex = tmpIndex + 1;
                monomersToAdd++;
            }

            tmpIndex = tmpIndex + 1;
	    newT[i] = newT[i] + t[tmpIndex]*newS->fracPart;
            partsToAdd = newS->numerator;
            tmpVector = t[tmpIndex]*partsToAdd / newS->denominator;
	}

        else{
            if(newS->numerator + partsToAdd > newS->denominator){//if you have to add more parts than contains the next link
                monomersToAdd = 0;
                newT[i] = t[tmpIndex] - tmpVector + t[tmpIndex+1];
                tmpIndex = tmpIndex + 1;
                while(monomersToAdd < newS->intPart - 1){
            	    newT[i] = newT[i] + t[tmpIndex+1];
                    tmpIndex = tmpIndex + 1;
                    monomersToAdd++;
                    }

                tmpIndex = tmpIndex + 1;
                newT[i] = newT[i] + t[tmpIndex] * (newS->numerator - newS->denominator + partsToAdd) / newS->denominator;
                partsToAdd = newS->numerator + partsToAdd - newS->denominator;
                tmpVector = t[tmpIndex] * partsToAdd / newS -> denominator;
            }

                else{
            	    monomersToAdd = 0;
            	    newT[i] = t[tmpIndex] - tmpVector;

                    while(monomersToAdd < newS->intPart - 1){
                	newT[i] = newT[i] + t[tmpIndex+1];
                	tmpIndex = tmpIndex + 1;
                	monomersToAdd++;
            	    }
            	
                tmpIndex = tmpIndex + 1;
                newT[i] = newT[i] + t[tmpIndex] * (newS->numerator + partsToAdd)/newS->denominator;
                partsToAdd = newS->numerator + partsToAdd;
                tmpVector = t[tmpIndex] * partsToAdd / newS->denominator;
                }

        }
    addExtraMonomer = 1;
    }    

//    formatAll();
//    numMonomers = newNumMonomers;
//    t = newT;
//    Polymer* tmpPolymer = new Polymer(newNumMonomers, NULL, newT);

    delete *polymer;
    *polymer = new Polymer(newNumMonomers, NULL, newT);
}

void PolymerScaling::scalingLoop(Polymer** polymer, const ScalingParam& etalonS,FILE* confFile, FILE* numMonomersFile, FILE* scalingParamFile, int loopSteps)
{
    int i;
    
    int numMonomers;
    
    ScalingParam newS(etalonS);
    
    numMonomers = (*polymer)->getNumMonomers();
    
    i=0;
    while(numMonomers>etalonS.intPart+1.1 && i<loopSteps){
	
	scaling(polymer,etalonS, &newS);
	    
	numMonomers = (*polymer)->getNumMonomers();
	
	if(confFile != NULL){
	    (*polymer)->setRadiusVectorsFromVectorsT();
	    (*polymer)->writeRadiusVectorsInFile(confFile);
	}
	
	if(numMonomersFile!=NULL){
	    fprintf(numMonomersFile, "%i\n", numMonomers);
	}
	
	if(scalingParamFile != NULL){
	    fprintf(scalingParamFile,"%g\n", newS.s);
	}
	
	i++;
    }
}

void PolymerScaling::observableVSscalingSteps(
	    PolymerScaling::Observable observable,
	    const Polymer& polymer,
	    const ScalingParam& etalonS, char* resultFile,
	    char* confFile, char* numMonomersFile, char* scalingParamFile, int shiftForObservable)
{
    int i;
    double answ;
    int numMonomers;
    Polymer* tmpPolymer;
    
    FILE* resultFp = NULL;
    FILE* confFp=NULL;
    FILE* numMonomersFp=NULL;
    FILE* scalingParamFp=NULL;
    
    numMonomers = polymer.getNumMonomers();
    
    
    _PCA_CATCH_VOID_POINTER(resultFile, "PolymerScaling::observableVSscalingSteps\n\tPass me the name for the result file\n");
    resultFp = fopen(resultFile, "w");
    _PCA_CATCH_FILE_ERROR(resultFp, "create", resultFile,"PolymerScaling::observableVSscalingSteps()");
    
    if(confFile != NULL){
	confFp = fopen(confFile, "w");
	_PCA_CATCH_FILE_ERROR(confFp, "create", confFile,"PolymerScaling::observableVSscalingSteps()");
    }
    
    if(numMonomersFile != NULL){
	numMonomersFp = fopen(numMonomersFile, "w");
	_PCA_CATCH_FILE_ERROR(numMonomersFp, "create", numMonomersFile,"PolymerScaling::observableVSscalingSteps()");
    }
    
    if(scalingParamFile != NULL){
	scalingParamFp = fopen(scalingParamFile, "w");
	_PCA_CATCH_FILE_ERROR(scalingParamFp, "create", scalingParamFile,"PolymerScaling::observableVSscalingSteps()");
    }

    tmpPolymer = new Polymer(polymer);
    
    ScalingParam newS(etalonS);
    
    if(PolymerScaling::verbose && globalVerbose)
	printf("Scaling step:\n");

    i=0;
    while(numMonomers>etalonS.intPart+1.1){
	
	if(PolymerScaling::verbose && globalVerbose)
	    printf("%i ",i);
	
	if(PolymerScaling::verbose && globalVerbose){
	    if((i+1)%10 == 0)
		printf("\n");
	}
	
	numMonomers = tmpPolymer->getNumMonomers();
	
	if(confFp != NULL){
	    tmpPolymer->setRadiusVectorsFromVectorsT();
	    tmpPolymer->writeRadiusVectorsInFile(confFp);
	}
	
	if(numMonomersFp!=NULL){
	    fprintf(numMonomersFp, "%i\n", numMonomers);
	}
	
	if(scalingParamFp != NULL){
	    fprintf(scalingParamFp,"%g\n", newS.s);
	}
	
	switch(observable){
	    case PolymerScaling::Observable::scalingParameter:
		answ = newS.s;
		break;
	    case PolymerScaling::Observable::totalAngle:
		answ = PolymerObservable::totalAngle(*tmpPolymer, shiftForObservable);
		break;
	    case PolymerScaling::Observable::radiusOfGyration:
		tmpPolymer->setRadiusVectorsFromVectorsT();
		answ = PolymerObservable::radiusOfGyration(*tmpPolymer);
		break;
	    case PolymerScaling::Observable::averageMonomersLength:
		tmpPolymer->setMonomerLengthsFromVectorsT();
		answ = PCA::meanValue(numMonomers, tmpPolymer->getMonomerLength());
		break;
	}
	
	fprintf(resultFp, "%i\t%.14le\n",i, answ);
	
	scaling(&tmpPolymer,etalonS, &newS);
	    
	i++;
    }
    
    if(PolymerScaling::verbose && globalVerbose)
	printf("\n");
    
    fclose(resultFp);
    
    if(confFp!=NULL)
	fclose(confFp);

    if(numMonomersFp!=NULL)
	fclose(numMonomersFp);

    if(scalingParamFp!=NULL)
	fclose(scalingParamFp);

}

void PolymerScaling::observableVSscalingStepsWithStatistics(
	    PolymerScaling::Observable observable,
	    char* dataFileName, int statistics,
	    const ScalingParam& etalonS, char* resultFile,
	    char* confFile, char* numMonomersFile, char* scalingParamFile, int shiftForObservable)
{
    int i,k;
    int numMonomers;

    double mean, error;
    double* answ;
    FILE* resultFp = NULL;
    FILE* confFp=NULL;
    FILE* numMonomersFp=NULL;
    FILE* scalingParamFp=NULL;
    FileCoordinates* reader;
    
    Polymer** polymer;


    if(statistics==0)
	statistics = FilePCA::countBlocks(dataFileName);
    answ = new double[statistics];
    
    reader = new FilePCA[statistics];
    polymer = new Polymer*[statistics];

    _PCA_CATCH_VOID_POINTER(resultFile, "PolymerScaling::observableVSscalingStepsWithStatistics\n\tPass me the name for the result file\n");
    resultFp = fopen(resultFile, "w");
    _PCA_CATCH_FILE_ERROR(resultFp, "create", resultFile,"PolymerScaling::observableVSscalingStepsWithStatistics()");
    
    if(confFile != NULL){
	confFp = fopen(confFile, "w");
	_PCA_CATCH_FILE_ERROR(confFp, "create", confFile,"PolymerScaling::observableVSscalingStepsWithStatistics()");
    }
    
    if(numMonomersFile != NULL){
	numMonomersFp = fopen(numMonomersFile, "w");
	_PCA_CATCH_FILE_ERROR(numMonomersFp, "create", numMonomersFile,"PolymerScaling::observableVSscalingStepsWithStatistics()");
    }
    
    if(scalingParamFile != NULL){
	scalingParamFp = fopen(scalingParamFile, "w");
	_PCA_CATCH_FILE_ERROR(scalingParamFp, "create", scalingParamFile,"PolymerScaling::observableVSscalingStepsWithStatistics()");
    }
    
    ScalingParam newS(etalonS);
	
    i=0;// count numbers of sites only for the first chain in statistics
    reader[i] = FilePCA(dataFileName, i);
    polymer[i] = new Polymer(reader[i]);
    numMonomers = polymer[i]->getNumMonomers();

    for(i=1;i<statistics;i++){
	reader[i] = FilePCA(dataFileName, i);
	polymer[i] = new Polymer(reader[i]);
    }
    
    if(PolymerScaling::verbose && globalVerbose)
	printf("Scaling step:\n");
	
    k=0;// zero step of scaling - original chains
    while(numMonomers>etalonS.intPart+1.1){
	
	if(PolymerScaling::verbose && globalVerbose)
	    printf("%i ",k);
	
	if(PolymerScaling::verbose && globalVerbose){
	    if((k+1)%10 == 0)
		printf("\n");
	}
	
	numMonomers = polymer[0]->getNumMonomers();
	
	for(i=0;i<statistics;i++){
	    switch(observable){
		case PolymerScaling::Observable::scalingParameter:
		    answ[i] = newS.s;
		    break;
		case PolymerScaling::Observable::totalAngle:
		    answ[i] = PolymerObservable::totalAngle(*polymer[i], shiftForObservable);
		    break;
		case PolymerScaling::Observable::radiusOfGyration:
		    polymer[i]->setRadiusVectorsFromVectorsT();
		    answ[i] = PolymerObservable::radiusOfGyration(*polymer[i]);
		    break;
		case PolymerScaling::Observable::averageMonomersLength:
		    polymer[i]->setMonomerLengthsFromVectorsT();
		    answ[i] = PCA::meanValue(numMonomers, polymer[i]->getMonomerLength());
		    break;
	    }
	}
	
	if(numMonomers>shiftForObservable){
	    mean = PCA::meanValue(statistics, answ);
	    error = PCA::standardDeviation(statistics, answ);
	    fprintf(resultFp,"%i\t%.14le\t%.14le\n", k, mean, error);
	}
	
	if(confFp != NULL){
	    polymer[0]->setRadiusVectorsFromVectorsT();
	    polymer[0]->writeRadiusVectorsInFile(confFp);
	}

	if(numMonomersFp!=NULL){
	    fprintf(numMonomersFp, "%i\n", numMonomers);
	}

	if(scalingParamFp != NULL){
	    fprintf(scalingParamFp,"%g\n", newS.s);
	}
	
	for(i=0;i<statistics;i++){
	    scaling(&polymer[i], etalonS, &newS);
	//    totAng[i] = PolymerObservable::totalAngle(*polymer[i]);
	}
	
	k++;
    }
    
    if(PolymerScaling::verbose && globalVerbose)
	printf("\n");
    
    fclose(resultFp);
    delete [] answ;
    
    if(confFp!=NULL)
	fclose(confFp);

    if(numMonomersFp!=NULL)
	fclose(numMonomersFp);

    if(scalingParamFp!=NULL)
	fclose(scalingParamFp);

    for(i=0;i<statistics;i++)
	delete polymer[i];
    
    delete [] reader;
    delete [] polymer;
}

}//end of namespace PCA
