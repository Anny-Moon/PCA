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
*   @file Polymer.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#include "../include/Polymer.h"
#include "../include/Utilities.h"
#include "../include/File.h"
#include <stdio.h>
#include <math.h>

#include "PCAmacros.h"

namespace PCA{
Polymer::Polymer(const FileCoordinates& reader)
{
    int size;
    double *x, *y, *z;
    size = reader.getNumLines();

    this->numMonomers = size-1;
    
    monomerLength = NULL;
    r = NULL;
    t = NULL;
    
    r = new Vector [size];
    x = new double [size];
    y = new double [size];
    z = new double [size];
    reader.fillCoordinates(x,y,z);
    Vector::makeArray(size, r, x, y, z);
    delete [] x;
    delete [] y;
    delete [] z;
    
    monomerLength = new double [numMonomers];
    setMonomerLengthsFromRadiusVectors();
    
    t = new Vector[numMonomers];
    setVectorsTfromRadiusVectors();
    
}

Polymer::Polymer(int numMonomers_in, const Vector* r_in, const Vector* t_in)
{
    this->numMonomers = numMonomers_in;
    
    monomerLength = NULL;
    r = NULL;
    t = NULL;

    if(r_in != NULL){
	r = new Vector[numMonomers+1];
	Vector::copyArray(numMonomers+1, r, r_in);
    }
    
    if(t_in != NULL){
	t = new Vector[numMonomers];
	Vector::copyArray(numMonomers, t, t_in);
    }

}

Polymer::Polymer(const Polymer& polymer)
{
    numMonomers = polymer.numMonomers;
    
    monomerLength = NULL;
    r = NULL;
    t = NULL;
    
    if(polymer.monomerLength != NULL){
	monomerLength = new double[numMonomers];
	PCA::copyArray(numMonomers, monomerLength, polymer.monomerLength);
    }
    
    if(polymer.r != NULL){
	r = new Vector[numMonomers+1];
	Vector::copyArray(numMonomers+1, r, polymer.r);
    }
    
    if(polymer.t != NULL){
	t = new Vector[numMonomers];
	Vector::copyArray(numMonomers, t, polymer.t);
    }
    
}

Polymer::~Polymer()
{
    formatAll();
}

void Polymer::formatAll()
{
    if(monomerLength != NULL){
	delete [] monomerLength;
	monomerLength = NULL;
    }

    if(t != NULL){
	delete [] t;
	t = NULL;
    }

    if(r != NULL){
	delete [] r;
	r = NULL;
    }
}

void Polymer::setRadiusVectorsFromVectorsT()
{
    int i;

    _PCA_CATCH_VOID_POINTER(t, "Polymer::setRadiusVectorsFromVectorsT()");
    
    if(r == NULL ){
	r = new Vector [numMonomers+1];
    }

    r[0]=Vector::zero;

    for(i=1;i<numMonomers+1;i++)
        r[i] = r[i-1] + t[i-1];

}

void Polymer::setVectorsTfromRadiusVectors()
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Polymer::setVectorsTfromRadiusVectors()");
    
    if(t == NULL ){
	t = new Vector [numMonomers];
    }
    
    for(i=0;i<numMonomers;i++)
	t[i] = r[i+1] - r[i];

}

void Polymer::rotateAboutX(double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "Polymer::RotateAboutX()");
    int i;
    double yNew, zNew;
    for (i=0;i<numMonomers+1;i++){
        //x[i] = x[i]
        yNew = r[i].y * cos(alpha) - r[i].z * sin(alpha);
        zNew = r[i].y * sin(alpha) + r[i].z * cos(alpha);
        r[i].y = yNew;
        r[i].z = zNew;
    }
    
    if(t != NULL ){
        setVectorsTfromRadiusVectors();
    }
}

void Polymer::rotateAboutY(double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "Polymer::RotateAboutX()");
    int i;
    double xNew, zNew;
    for (i=0;i<numMonomers+1;i++){
        xNew = r[i].x * cos(alpha) + r[i].z * sin(alpha);
        //y[i] = y[i]
        zNew = - r[i].x * sin(alpha) + r[i].z * cos(alpha);
        r[i].x = xNew;
        r[i].z = zNew;
    }
    
    if(t != NULL ){
        setVectorsTfromRadiusVectors();
    }
}

void Polymer::rotateAboutZ(double alpha)
{
    _PCA_CATCH_VOID_POINTER(r, "Polymer::RotateAboutX()");
    int i;
    double xNew, yNew;
    for (i=0;i<numMonomers+1;i++){
        xNew = r[i].x * cos(alpha) - r[i].y * sin(alpha);
        yNew = r[i].x * sin(alpha) + r[i].y * cos(alpha);
        //z[i] = z[i]
        r[i].x = xNew;
        r[i].y = yNew;
    }
    
    if(t != NULL ){
        setVectorsTfromRadiusVectors();
    }
}

void Polymer::setMonomerLengthsFromRadiusVectors()
{
    int i;

    _PCA_CATCH_VOID_POINTER(r, "Polymer::setMonomerLengthsFromRadiusVectors()");
    
    if(monomerLength == NULL){
	monomerLength = new double [numMonomers];
    }
    
    for(i=0;i<numMonomers;i++){
	monomerLength[i] = (r[i+1] - r[i]).norm();
    }

}

void Polymer::setMonomerLengthsFromVectorsT()
{
    int i;

    _PCA_CATCH_VOID_POINTER(t, "Polymer::setMonomerLengthsFromVectorsT()");

    if(monomerLength == NULL){
	monomerLength = new double [numMonomers];
    }
    
    for(i=0;i<numMonomers;i++)
	monomerLength[i] = t[i].norm();

}

const double* Polymer::getMonomerLength() const
{
    _PCA_CATCH_VOID_POINTER(monomerLength, "Polymer::getMonomerLength()");
    return monomerLength;
}

const Vector* Polymer::getRadiusVectors() const
{
    _PCA_CATCH_VOID_POINTER(r, "Polymer::getRadiusVectors()");
    return r;
}

const Vector* Polymer::getVectorsT() const
{
    _PCA_CATCH_VOID_POINTER(t, "Polymer::getVectorsT()");
    return t;
}

void Polymer::getXarray(int N, double* array) const
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Polymer::getXarra()");
    _PCA_CATCH_VOID_POINTER(array, "Polymer::getXarra()");
    
    if (numMonomers+1 != N){
        printf("Error in Polymer::getXarray(): wrong array size\n");
        exit(1);
    }
    
    for(i=0; i<N; i++)
        array[i] = r[i].x;
}

void Polymer::getYarray(int N, double* array) const
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Polymer::getYarra()");
    _PCA_CATCH_VOID_POINTER(array, "Polymer::getYarra()");
    
    if (numMonomers+1 != N){
        printf("Error in Polymer::getYarray(): wrong array size\n");
        exit(1);
    }
    
    for(i=0; i<N; i++)
        array[i] = r[i].y;
}

void Polymer::getZarray(int N, double* array) const
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(r, "Polymer::getZarra()");
    _PCA_CATCH_VOID_POINTER(array, "Polymer::getZarra()");
    
    if (numMonomers+1 != N){
        printf("Error in Polymer::getZarray(): wrong array size\n");
        exit(1);
    }
    
    for(i=0; i<N; i++)
        array[i] = r[i].z;
}

void Polymer::writeRadiusVectorsInFile(FILE* fp) const
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(fp, "Polymer::writeRadiusVectorsInFile(.):\n\tGive me valid pointer to the file.");
    _PCA_CATCH_VOID_POINTER(r, "Polymer::writeRadiusVectorsInFile(.)");

    for(i=0;i<numMonomers+1;i++)
	r[i].writeInFile(fp);
	
    fprintf(fp,"\n\n");
}

void Polymer::writeMonomerLengthsInFile(FILE* fp) const
{
    int i;
    
    _PCA_CATCH_VOID_POINTER(fp, "Polymer::writeMonomerLengthsInFile(.):\n\tGive me valid pointer to the file.");
    _PCA_CATCH_VOID_POINTER(monomerLength, "Polymer::writeMonomerLengthsInFile(.)");
    
    for(i=0;i<numMonomers;i++)
	fprintf(fp, "%g\n", monomerLength[i]);
	
    fprintf(fp,"\n\n");
}


}// end of namespace
