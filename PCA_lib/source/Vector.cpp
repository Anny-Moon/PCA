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
*   @file Vector.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/


#include "../include/Vector.h"
#include "../include/PCAmacros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

namespace PCA{

bool Vector::verbose = true;

Vector::Vector()
    {	x = 0.0;
	y = 0.0;
	z = 0.0;
    }

Vector::Vector (double X, double Y, double Z)
    {
	x = X;
	y = Y;
	z = Z;
    }

Vector::~Vector(){}

const Vector Vector::zero(0.0, 0.0, 0.0);
const Vector Vector::eX(1.0 ,0.0, 0.0);
const Vector Vector::eY(0.0 ,1.0, 0.0);
const Vector Vector::eZ(0.0 ,0.0, 1.0);

void Vector::setVerbose(bool verbose)
{
    Vector::verbose = verbose;
}

bool Vector::getVerbose()
{
    return Vector::verbose;
}

void Vector::print() const
{
    if(Vector::getVerbose() && globalVerbose)
	printf("%.15le\t%.15le\t%.15le\n", x, y, z);
}

void Vector::makeArray(int size, Vector* r, double* x, double* y, double* z){
    int i;
    _PCA_CATCH_VOID_POINTER(r, "Vector::makeArray(.)\n\tGive me pointer to final array.");
    _PCA_CATCH_VOID_POINTER(x, "Vector::makeArray(.)\n\tGive me x.");
    _PCA_CATCH_VOID_POINTER(y, "Vector::makeArray(.)\n\tGive me y.");
    _PCA_CATCH_VOID_POINTER(z, "Vector::makeArray(.)\n\tGive me z.");
    
    for(i=0;i<size;i++){
	r[i].x = x[i];
	r[i].y = y[i];
	r[i].z = z[i];
    }
}

void Vector::copyArray(int size, Vector* vector_to, const Vector* vector_from)
{
    int i;

    _PCA_CATCH_VOID_POINTER(vector_to, "Vector::copyArray(.)\n\tTo where I should copy?")
    _PCA_CATCH_VOID_POINTER(vector_from, "Vector::copyArray(.)\n\tFrom where I should copy?")

    for (i=0;i<size;i++)
	vector_to[i] = vector_from[i];

}

void Vector::getXarray(int N, const Vector* r,  double* array)
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Vector::getXarray()");
    _PCA_CATCH_VOID_POINTER(array, "Vector::getXarray()");
    
    for(i=0; i<N; i++)
        array[i] = r[i].x;
}

void Vector::getYarray(int N, const Vector* r, double* array)
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Vector::getYarray()");
    _PCA_CATCH_VOID_POINTER(array, "Vector::getYarray()");
    
    for(i=0; i<N; i++)
        array[i] = r[i].y;
}

void Vector::getZarray(int N, const Vector* r, double* array)
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Vector::getZarray()");
    _PCA_CATCH_VOID_POINTER(array, "Vector::getZarray()");
    
    for(i=0; i<N; i++)
        array[i] = r[i].z;
}

}//end of namespace