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
*   @file PolymerObservable.h
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#ifndef PCA_POLYMER_OBSERVABLE
#define PCA_POLYMER_OBSERVABLE

#include "Polymer.h"
#include "Vector.h"
#include "Utilities.h"
#include <stdlib.h>
#include <stdio.h>

namespace PCA{

class PolymerObservable
{
public:
    
    /** ..
    * \f[
    * R_{gyr} = \sqrt{\frac{1}{(N+1)^2} \sum_{i<j}^{N+1}
    * \left( \vec{r}_i-\vec{r}_j \right)^2}
    * \f] where N is number of monomers.*/
    static double radiusOfGyration(const Polymer& polymer);
    
    /** ..
    * \f[
    * \theta = \sum_{i+k<j}^N
    * \frac{(\vec{t}_i\cdot \vec{t}_j)}{\vert\vec{t}_i\vert\vert\vec{t}_j\vert}
    * \f] where N is number of monomers, k is number of terms we exclude from the summation.*/
    static double totalAngle(const Polymer& polymer, int shift = 1);
    
};
}//end of namespace PCA
#endif