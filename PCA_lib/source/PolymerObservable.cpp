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

}//end of namespace
