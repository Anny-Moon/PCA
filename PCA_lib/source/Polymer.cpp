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

void Polymer::readFileWithCoordinates(char* fileName, int linesInBlock, int blockNumber)
{
    int i=0;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    char line[100];
    FILE *fp;
    double x_in, y_in, z_in;
    
    fp = fopen(fileName, "r");
    _PCA_CATCH_FILE_ERROR(fp, "open", fileName, "Polymer::readFileWithCoordinates");

    if(blockNumber == 0){
	printf("Error in Polymer::readFileWithCoordinates:\nnumber of the first block is 1 in data files. You passed me 0!\n");
	exit(1);
    }
    
    
    
    while(fgets(line, sizeof line, fp)!=NULL){
	
	if(blockCounter == blockNumber-1)
	    break;
	    
	else if(line[0]=='\n'||line[0]=='\t'||line[0]==' '){
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	    }
	
	else
	    prevLineEmpty = false;
    }

    if(!prevLineEmpty)
	blockCounter++;

    if(blockNumber > blockCounter+1){
	printf("Error in readFileWithCoordinates:\nYou have only %i blocks in your file. But you passed me number %i\nNote: in files number of the first block is 1.\n",blockCounter, blockNumber);
	exit(1);
    }

    int firstElement=0;
    
    if(line[0]!='\n'&&line[0]!='\t'&&line[0]!=' '){
	    sscanf(line,"%le %le %le",&x_in, &y_in, &z_in);
	    setRadiusVector(0, x_in, y_in, z_in);
	    firstElement = 1;
	}

    for(i=firstElement;i<linesInBlock;i++){
	fscanf(fp,"%le",&x_in);
	fscanf(fp,"%le",&y_in);
	fscanf(fp,"%le",&z_in);
	setRadiusVector(i, x_in, y_in, z_in);
    }
    
    fclose(fp);
}

Polymer::Polymer(char* fileWithCoordinates, int numberOfSites, int polymerNumber)
{
    int size;
    
    if(numberOfSites == 0)
	size = File::countLinesInBlock(fileWithCoordinates, polymerNumber);
	
    else
	size = numberOfSites;

    this->numMonomers = size-1;
    
    monomerLength = NULL;
    r = NULL;
    t = NULL;
    
    r = new Vector[numMonomers+1];
    readFileWithCoordinates(fileWithCoordinates, size, polymerNumber);
    
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
