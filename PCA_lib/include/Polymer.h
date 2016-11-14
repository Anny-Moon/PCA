/** @file	Polymer.h
*
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#ifndef PCA_POLYMER
#define PCA_POLYMER

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
    
    /** Read file with x y z coordinates and fill . One line - one atom. One block - one chain.
    * Block is separated from another one with one or more empty lines. The first has number 1 (not 0).
    *
    * NB1: in this version empty line is every line which starts with
    * unprintable characters: \\n, \\t or space. That's why any line with data can't 
    * have unprintable character at the beginning.
    *
    * NB2: You can't have emty line before the first block.
    * You don't need to have empty line at the end of file.*/
    void readFileWithCoordinates(char* fileName, int linesInBlock, int blockNumber = 1);
    
    /** The same as destructor */
    void formatAll();
public:

    /** Constructor. Read coordinates of sites from file. If you have more than one
    * blocks in file then pass the number of the block. You can pass number of sites in
    * the block, but it is not necessarily.*/
    Polymer(char* fileWithCoordinates, int numberOfSites = 0, int polymerNumber = 1);
    
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
    
    /** @name Set lengths of all monomers from vectors:*/
    ///@{
    void setMonomerLengthsFromRadiusVectors();
    void setMonomerLengthsFromVectorsT();
    ///@}
    
    /** @name Functions which returns members:*/
    ///@{
    int getNumMonomers () const;
    const double* getMonomerLength () const;
    const Vector* getRadiusVectors() const;
    const Vector* getVectorsT() const;
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