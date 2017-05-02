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