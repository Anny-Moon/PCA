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

void Vector::KadanoffTransformation(int size, Vector* vector_out, const Vector* vector_in)
{
    int i;

    _PCA_CATCH_VOID_POINTER(vector_in, "Vector::KadanoffTransformation(.)")
    
    *vector_out = Vector::zero;

    for(i=0;i<size;i++){
	*vector_out = *vector_out + vector_in[i];
    }
    
    *vector_out = *vector_out/vector_out->norm();
}

void Vector::copyArray(int size, Vector* vector_to, const Vector* vector_from)
{
    int i;

    _PCA_CATCH_VOID_POINTER(vector_to, "Vector::copyArray(.)\n\tTo where I should copy?")
    _PCA_CATCH_VOID_POINTER(vector_from, "Vector::copyArray(.)\n\tFrom where I should copy?")

    for (i=0;i<size;i++)
	vector_to[i] = vector_from[i];

}
}//end of namespace