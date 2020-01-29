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
*   @file Polymer.h
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#ifndef PCA_POLYMER
#define PCA_POLYMER

#include "FileHandler/FileCoordinates.h"
#include "Vector.h"
#include "Utilities.h"
#include <stdlib.h>
#include <stdio.h>

namespace PCA{

class Polymer
{private:

    int numMonomers;/**< Number of monomers in polymer chain */
    double* monomerLength;/**< monomer length */
    
    Vector* t; /**< tangent not-unit vectors*/
    Vector* r;/**< radius vectors */
    
    /** The same as destructor */
    void formatAll();
public:

    /** Constructor. Read coordinates of sites from file. If you have more than one
    * blocks in file then pass the number of the block. You can pass number of sites in
    * the block, but it is not necessarily.*/
    Polymer(const FileCoordinates& reader);
    
    /** Constructor. */
    Polymer(int numMonomers_in, const Vector* r_in, const Vector* t_in);

    /** Copy constructor */
    Polymer(const Polymer& polymer);

    /** Destructor*/
    ~Polymer();

    /** Set one radius vector r[i] from x,y,z coordinates */
    void setRadiusVector(int i, double x_in, double y_in, double z_in);
    
    /** @name Set ones vectors from another vectors:*/
    ///@{
    void setVectorsTfromRadiusVectors();
    void setRadiusVectorsFromVectorsT();
    ///@}
    
    /** @name Rotation about X, Y and Z axes:*/
    ///@{
    void rotateAboutX(double alpha);
    void rotateAboutY(double alpha);
    void rotateAboutZ(double alpha);
    ///@}
    
    /** @name Set lengths of all monomers from vectors:*/
    ///@{
    void setMonomerLengthsFromRadiusVectors();
    void setMonomerLengthsFromVectorsT();
    ///@}
    
    /** @name Functions which return members:*/
    ///@{
    int getNumMonomers () const;
    const double* getMonomerLength () const;
    const Vector* getRadiusVectors() const;
    const Vector* getVectorsT() const;
    ///@}
    
    ///@{@name return arrays of Xs, Ys or Zs:
    void getXarray(int N, double* array) const;
    void getYarray(int N, double* array) const;
    void getZarray(int N, double* array) const;
    ///@}
    
    /** @name Write in file or write file itself:*/
    /** Writes x y z coordinates in file. One line - one atom */
    void writeRadiusVectorsInFile(FILE* fp) const;
    
    /** Writes lengthes of all monomers in the chain in file. */
    void writeMonomerLengthsInFile(FILE* fp) const;

};

inline void Polymer::setRadiusVector(int i, double x_in, double y_in, double z_in)
{
    if(r == NULL){
	printf("Error in inline Polymer::setRadiusVector\n");
	exit(1);
    }

    r[i].x = x_in;
    r[i].y = y_in;
    r[i].z = z_in;

}
inline int Polymer::getNumMonomers() const
{
    return numMonomers;
}

}// end of namespace
#endif