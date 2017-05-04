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
*   @file DataHandler.h
*
*   @autor Anna Sinelnikova
*   @data 2017
*/

#ifndef PCA_DATA_HANDLER
#define PCA_DATA_HANDLER

#include <string>
#include <iostream>
namespace PCA{

class DataHandler{
public:
    static std::string path;//< path to the data folder
    
    inline void setPath (const std::string& path_in="");
    inline static std::string fullName (const std::string& name);
};

inline void DataHandler::setPath (const std::string& path_in){
    if(path_in.compare("") == 0)
	path = "../../data/";

    else
	path = path_in;
}

inline std::string DataHandler::fullName(const std::string& name){
    return path+name;
}

}// end of namespace
#endif