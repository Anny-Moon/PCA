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
*   @file PolymerObservable.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#include "../include/PolymerObservable.h"
#include "../include/Polymer.h"
#include "../include/Utilities.h"
#include <stdio.h>
#include <math.h>

#include "PCAmacros.h"

namespace PCA{

double PolymerObservable::radiusOfGyration(const Polymer& polymer)
{
    int i,j;
    double R;

    _PCA_CATCH_VOID_POINTER(polymer.getRadiusVectors(), "PolymerObservable::radiusGyration()");
    
    const Vector* r = polymer.getRadiusVectors();
    int numMonomers = polymer.getNumMonomers();
    
    R=0;
    for(i=0;i<numMonomers+1;i++)
	for(j=i+1;j<numMonomers+1;j++)
	    R+=Vector::dotProduct(r[i]-r[j], r[i]-r[j]);
    
    return sqrt(R)/((double)(numMonomers+1));

}


double PolymerObservable::totalAngle(const Polymer& polymer, int shift)
{
    int i,j;
    double answ=0.0;

    _PCA_CATCH_VOID_POINTER(polymer.getVectorsT(), "PolymerObservable::totalAngle()");
    
    const Vector* t = polymer.getVectorsT();
    int numMonomers = polymer.getNumMonomers();
    
    for(i=0;i<numMonomers;i++)
	for(j=i+shift;j<numMonomers;j++)
	    answ += Vector::dotProduct(t[i],t[j]) / (t[i].norm() * t[j].norm());
    
    return answ;
//    return answ/pow((double)numMonomers,1.5);
}


void PolymerObservable::rotateAboutX(int N, Vector* r, double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "PolymerObservable::rotateAboutX()");
    int i;
    double yNew, zNew;
    for (i=0;i<N;i++){
        //x[i] = x[i]
        yNew = r[i].y * cos(alpha) - r[i].z * sin(alpha);
        zNew = r[i].y * sin(alpha) + r[i].z * cos(alpha);
        r[i].y = yNew;
        r[i].z = zNew;
    }
    
}

void PolymerObservable::rotateAboutY(int N, Vector* r, double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "PolymerObservable::rotateAboutY()");
    int i;
    double xNew, zNew;
    for (i=0;i<N;i++){
        xNew = r[i].x * cos(alpha) + r[i].z * sin(alpha);
        //y[i] = y[i]
        zNew = - r[i].x * sin(alpha) + r[i].z * cos(alpha);
        r[i].x = xNew;
        r[i].z = zNew;
    }
    
}

void PolymerObservable::rotateAboutZ(int N, Vector* r, double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "Polymer::RotateAboutZ()");
    int i;
    double xNew, yNew;
    for (i=0;i<N;i++){
        xNew = r[i].x * cos(alpha) - r[i].y * sin(alpha);
        yNew = r[i].x * sin(alpha) + r[i].y * cos(alpha);
        //z[i] = z[i]
        r[i].x = xNew;
        r[i].y = yNew;
    }
    
}

}//end of namespace
