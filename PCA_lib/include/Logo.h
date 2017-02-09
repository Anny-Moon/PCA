/** @package PCA
*   @file Logo.h
*
*   @autor Anna Sinelnikova
*   @data 2017
*/

#ifndef PCA_LOGO
#define PCA_LOGO

#include <stdlib.h>
#include <stdio.h>

namespace PCA{

class Logo
{
public:

    inline static void print();
    inline static void printInFile(FILE* fp);
};

inline void Logo::print(){
    printf("=====================================\n");
    printf("-------------------------------------\n");
    printf("+   ______        __       ___      +\n");
    printf("+  |   __  \\    /  __\\   / __  \\    +\n");
    printf("+  |  |   | |  / /      | |  \\  \\   +\n");
    printf("+  |  | _/ /  | |       | |___|  |  +\n");
    printf("+  |   __ /   |  \\ __   |  ___   |  +\n");
    printf("+  |__|        \\ ___ /  |_|   |__|  +\n");
    printf("-------------------------------------\n");
    printf("============================Anna=====\n");
}

inline void Logo::printInFile(FILE* fp){
    if(fp==NULL){
	printf("Error in Logo::printInFile\n");
	exit(1);
    }

    fprintf(fp,"=====================================\n");
    fprintf(fp,"-------------------------------------\n");
    fprintf(fp,"+   ______        __       ___      +\n");
    fprintf(fp,"+  |   __  \\    /  __\\   / __  \\    +\n");
    fprintf(fp,"+  |  |   | |  / /      | |  \\  \\   +\n");
    fprintf(fp,"+  |  | _/ /  | |       | |___|  |  +\n");
    fprintf(fp,"+  |   __ /   |  \\ __   |  ___   |  +\n");
    fprintf(fp,"+  |__|        \\ ___ /  |_|   |__|  +\n");
    fprintf(fp,"-------------------------------------\n");
    fprintf(fp,"============================Anna=====\n");
}
}// end of namespace
#endif