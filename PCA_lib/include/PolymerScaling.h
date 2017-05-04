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
*   @file PolymerScaling.h
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#ifndef PCA_POLYMER_SCALING
#define PCA_POLYMER_SCALING

#include "Polymer.h"
#include "PolymerObservable.h"
#include "Vector.h"
#include "Utilities.h"
#include <stdlib.h>
#include <stdio.h>

namespace PCA{

class PolymerScaling
{
private:

    static bool verbose;///< If false then this class is not allowed to print anything on screen

public:
    class ScalingParam
    {private:
	static double ACCURACY;
	void findEverythingFromS();
	
    public:
	double s;
	int intPart;
	double fracPart;
	int numerator;
	int denominator;
    
	ScalingParam(double s_in);
	ScalingParam(int nemerator_in, int denominator_in, int intPart_in=1);
	ScalingParam(const ScalingParam& sp);
	~ScalingParam();
	void format(double s_in);
	
	static void setAccuracy(double accuracy);
	static double getAccuracy();
    };
    
    enum class Observable {
	scalingParameter,
	totalAngle,
	radiusOfGyration,
	averageMonomersLength
    };
    

    static double findCriticalScalingParam(int numMonomers);
    
    /** Returns new numMonomers! */
    static int findNewScalingParam(
	int oldNumMonomers,
	const ScalingParam& etalonS,
	ScalingParam* newS
    );

    static void scaling(
	Polymer** polymer,
	const ScalingParam& etalonS,
	ScalingParam* newS
    );
    
    static void scalingLoop(
	Polymer** polymer,
	const ScalingParam& etalonS,
	FILE* confFile=NULL,
	FILE* numMonomersFile=NULL,
	FILE* scalingParamFile=NULL,
	int loopSteps = 100000
    );
    
    static void observableVSscalingSteps(
	Observable observable,
	const Polymer& polymer,
	const ScalingParam& etalonS,
	char* resultFile,
	char* confFile=NULL,
	char* numMonomersFile=NULL,
	char* scalingParamFile=NULL
    );
    
    /** .. All blocks in statistics should be of the SAME SIZE.
    DataFileName - name of the file with coordinates x, y, z.*/
    static void observableVSscalingStepsWithStatistics(
	Observable observable,
	char* dataFileName,
	int statistics,
	const ScalingParam& etalonS,
	char* resultFile,
	char* confFile=NULL,
	char* numMonomersFile=NULL,
	char* scalingParamFile=NULL,
	int shiftForObservable = 1
    );
    
    void totalAngleVSaverageMonomersLength(
	const ScalingParam& etalonS,
	FILE* resultFile,
	FILE* confFile=NULL,
	FILE* numMonomersFile=NULL,
	FILE* scalingParamFile=NULL,
	int loopSteps = 100000
    );
    void totalAngleVSintegralMonomersLength(
	const ScalingParam& etalonS,
	FILE* resultFile,
	FILE* confFile=NULL,
	FILE* numMonomersFile=NULL,
	FILE* scalingParamFile=NULL,
	int loopSteps = 100000
    );
    
    void averageMonomersLengthVSscalingSteps(
	const ScalingParam& etalonS,
	FILE* resultFile,
	FILE* confFile=NULL,
	FILE* numMonomersFile=NULL,
	FILE* scalingParamFile=NULL,
	int loopSteps = 100000
    );


    /** @name Triangular maps: */
    //@{
    void writeMapEndToEndVideo(char* fileName, const ScalingParam& etalonS, FILE* confFile=NULL, FILE* numMonomersFile=NULL, FILE* scalingParamFile=NULL, int eachStep = 1);
    void writeMapDotProductVideo(char* fileName, const ScalingParam& etalonS, FILE* confFile=NULL, FILE* numMonomersFile=NULL, FILE* scalingParamFile=NULL, int eachStep = 1);
    //@}
    
    /** @name Verbose functions: */
    //@{
    static void setVerbose(double verbose);
    static bool getVerbose();
    //@}
};
}//end of namespace
#endif