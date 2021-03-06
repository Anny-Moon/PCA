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
*   @file File.cpp
*
*   @autor Anna Sinelnikova
*   @data 2016
*/

#include "../include/File.h"
#include "../include/Utilities.h"
#include "../include/PCAmacros.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

namespace PCA{

bool File::verbose = true;

void File::setVerbose(bool verbose)
{
    File::verbose = verbose;
}

bool File::getVerbose()
{
    return File::verbose;
}

int File::countLinesInBlock(char* fileName, int blockNumber)
{
    int linesInBlock = 0;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    char line[100];
    FILE *fp;
    
    
    fp = fopen(fileName, "r");
    
    _PCA_CATCH_FILE_ERROR(fp, "open", fileName, "File::coutLinesInBlock(.)")
    
    if(blockNumber == 0){
	printf("Error in countLinesInBlockInFile:\nIn files number of the first block is 1. You pussed me 0!\n");
	exit(1);
    }
    
    while(fgets(line, sizeof line, fp)!=NULL){
	
	if(line[0]=='\n'||line[0]=='\t'||line[0]==' '){
	    
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	
	    if(blockCounter == blockNumber)
		break;
	    
	    linesInBlock = 0;
	}
	
	else{
	    linesInBlock++;
	    prevLineEmpty = false;
	}
    }
    
    if(!prevLineEmpty)
	blockCounter++;

    fclose(fp);
    
    if(blockNumber > blockCounter){
	printf("Error in File::countLinesInBlockInFile:\nYou have only %i blocks in your file. But you passed me number %i\nNote: in files number of the first block is 1.\n",blockCounter, blockNumber);
	exit(1);
    }
    
    if(File::getVerbose() && globalVerbose)
	printf("Number of lines in block #%i in file '%s': %i.\n", blockNumber, fileName, linesInBlock);
    
    return linesInBlock;
}

int File::countBlocks(char* fileName)
{
    int linesInBlock = 0;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    char line[100];
    FILE *fp;

    fp = fopen(fileName, "r");

    _PCA_CATCH_FILE_ERROR(fp, "open", fileName, "File::countBlocksInFile(.)")

    while(fgets(line, sizeof line, fp)!=NULL){
	
	if(line[0]=='\n'||line[0]=='\t'||line[0]==' '){
	    
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	    linesInBlock = 0;
	}
	
	else{
	    linesInBlock++;
	    prevLineEmpty = false;
	}
    }
    
    if(!prevLineEmpty)
	blockCounter++;

    fclose(fp);
    
    if(File::getVerbose() && globalVerbose)
	printf("Number of blocks in file '%s': %i.\n", fileName, blockCounter);
    return blockCounter;
}

bool File::checkAllBlocksHaveTheSameSize(char* fileName)
{
    int i;
    bool answ = true;
    int numBlocks, numLinesInFirstBlock, tmp;
    bool currentVerbose;
    
    currentVerbose = verbose;
    verbose = false;
    
    numBlocks = File::countBlocks(fileName);
    numLinesInFirstBlock = File::countLinesInBlock(fileName, 1);
    
    for(i=1; i<numBlocks; i++){
	tmp = File::countLinesInBlock(fileName, i+1);
	    if(tmp != numLinesInFirstBlock){
		answ = false;
		break;
	    }
    }
    
    verbose = currentVerbose;
    return answ;
}
void File::showNumberOfLinesInBlocks(char* fileName)
{
    int linesInBlock = 0;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    char line[100];
    FILE *fp;

    fp = fopen(fileName, "r");

    _PCA_CATCH_FILE_ERROR(fp, "open", fileName, "File::showNumberOfLinesInBlocks(.)")
    
    printf("In file '%s':\n", fileName);
    while(fgets(line, sizeof line, fp)!=NULL){
	
	if(line[0]=='\n'||line[0]=='\t'||line[0]==' '){
	    
	    if(!prevLineEmpty){
		blockCounter++;
		printf("block #%i:\t%i lines\n", blockCounter, linesInBlock);
	    }
	    
	    prevLineEmpty = true;
	    linesInBlock = 0;
	}
	
	else{
	    linesInBlock++;
	    prevLineEmpty = false;
	}
    }
    
    if(!prevLineEmpty){
	blockCounter++;
	printf("block #%i:\t%i lines\n", blockCounter, linesInBlock);
    }
    
    fclose(fp);
}


}//end of namespace