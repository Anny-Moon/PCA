/** PCAmacros.h
*
*   Anna Sinelnikova
*   Uppsala, Sweden 2016
*/

#ifndef PCA_MACROS
#define PCA_MACROS


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PCA_PI 3.141592653589793

#define _PCA_CATCH_VOID_POINTER(pointer, functionName)\
    if(pointer==NULL){\
	printf("Error: void pointer\n\tin ");\
	printf(functionName);\
	printf("\n");\
	exit(1);\
    }

#define _PCA_CATCH_FILE_ERROR(fp, action, fileName, functionName)\
    if(fp==NULL){\
	printf("Error: cannot \%s file '%s'\n\tin ", action, fileName);\
	printf(functionName);\
	printf("\n");\
	exit(1);\
    }
#define PCA_NUMERICAL_ERROR 3.0*fabs(atan(1.0)-PCA_PI/4.0)

#define _PCA_IS_EQUAL(a,b)\
     fabs(a-b)<PCA_NUMERICAL_ERROR

#define _PCA_CHECK_BLOCKS_SIZE_IN_FILE(str)\
    if(!File::checkAllBlocksHaveTheSameSize(str)){\
	printf("Error in data file:\n");\
	printf("All the chains in your file should be of the same size. ");\
	printf("But it is not the case.\nLook:\n");\
	File::showNumberOfLinesInBlocks(str);\
	exit(1);\
    }

#endif