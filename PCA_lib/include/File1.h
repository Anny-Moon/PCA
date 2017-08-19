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
*   @file File.h
*
*   @autor Anna Sinelnikova
*   @data 2017
*/

#pragma once

#include <vector>
#include <string>

namespace PCA{

/* Pure virtial class*/
class File1
{
private:
    
protected:
    std::string fileName;
    std::string extention;
    
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    
    int numLines;
    
    bool verbose;
    File1(std::string fileName);
public:
    
    virtual void fillCoordinates(double* x, double* y, double* z) const = 0;
    inline int getNumLines() const;
    
    std::string getFileName() const;
    std::string getExtention() const;
    
    ///@{@name Verbose functions:
    inline void setVerbose(bool verbose);
    inline bool getVerbose() const;
    ///@}
    inline ~File1();
};


inline int File1::getNumLines() const {
    return numLines;
}

inline std::string File1::getFileName() const {
    return fileName;
}

inline std::string File1::getExtention() const {
    return extention;
}

inline void File1::setVerbose(bool verbose){
    File1::verbose = verbose;
}

inline bool File1::getVerbose() const {
    return File1::verbose;
}

inline File1::~File1(){};

}// end of namespace
