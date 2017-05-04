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
*   @file Utilities.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/


#include <math.h>
#include "../include/Utilities.h"
#include <stdlib.h>
#include <stdio.h>


namespace PCA{

bool globalVerbose = true;

double meanValue(int size, const double* values)
{   int i;
    double av = 0.0;

    for(i=0; i<size; i++)
	av += values[i];

    av = av / ((double)size);
    return av;
}

double standartDeviation(int size, const double* values)
{   int i;
    double av, sigma;
    sigma = 0.0;
    av = meanValue(size, values);
    for(i=0; i<size; i++)
	sigma += (values[i] - av) * (values[i] - av);

    sigma = sqrt(sigma / ((double)(size * size)));
    return sigma;
}

void copyArray(int N, double* array_to, const double* array_from)
{   int i;

//    _PCA_CATCH_VOID_POINTER(array_to, "Utilities.cpp PCA::copyArray(.)\n\tTo where I should copy?")
//    _PCA_CATCH_VOID_POINTER(array_from, "Utilities.cpp PCA::copyArray(.)\n\tFrom where I should copy?")
    
    for(i=0;i<N;i++)
	array_to[i] = array_from[i];
}

void fillArray(int N, double* array_to, double value)
{   int i;
    for(i=0;i<N;i++)
	array_to[i] = value;
}

int rounding(double number)
{
    double intpart;
    double fracpart;
    int answ;

    fracpart=modf (number , &intpart);

    if(fabs(fracpart)<0.499999)
	answ=(int)intpart;
    
    else
	answ=(int)intpart+1;
    
    return answ;
}

int commonDivisor(int int1, int int2, int upperLimit)
{
    int i;

    if(upperLimit==0){
	if(int1<int2)
	    upperLimit = int1;
    
	else
	    upperLimit = int2;
    }
    
    for(i=upperLimit;i>0;i--){
	if(int1%i==0){
	    if(int2%i==0)
	    return i;
	}
    }

return 1;
}


}// End namespace