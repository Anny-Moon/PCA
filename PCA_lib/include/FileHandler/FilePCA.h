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
*   @file FilePCA.h
*
*   @autor Anna Sinelnikova
*   @data 2017
*/

#pragma once

#include "FileCoordinates.h"
#include <iostream>
#include <string>

#define _PCA_CHECK_BLOCKS_SIZE_IN_FILE(str)\
    if(!FilePCA::checkAllBlocksHaveTheSameSize(str)){\
	printf("Error in data file:\n");\
	printf("All the chains in your file should be of the same size. ");\
	printf("But it is not the case.\nLook:\n");\
	FilePCA::showNumberOfLinesInBlocks(str);\
	exit(1);\
    }

namespace PCA{

class FilePCA : public FileCoordinates
{
public:
    /**
    * Block are separated from another one with one or more empty lines. The first has number 0.
    
    * NB1: in this version empty line is every line which starts with
    * unprintable characters: \\n, \\t or space. That's why any line with data can't 
    * have unprintable character at the beginning.
    
    * NB2: You can't have emty line before the first block.
    * You don't need to have empty line at the end of file.*/
    
    inline FilePCA();
    FilePCA(std::string fullFileName, int blockNumber = 0);
    inline ~FilePCA();
    
    void fillCoordinates(double* x, double* y, double* z) const;
    
    /** Returns number of lines in one particular data block.*/
    static int countLinesInBlock(std::string fileName, int blockNumber = 0);
    
    /** Return number of blocs in file */
    static int countBlocks(std::string fileName);
    
    /** Check that all data blocks have the same number of lines */
    static bool checkAllBlocksHaveTheSameSize(std::string fileName);
    
    /** Print on screen list of blocks and number of lines in each.
    * Thus function will print on screen even if all
    * verbose are false */
    static void showNumberOfLinesInBlocks(std::string fileName);
    
    /** For debugging */
    void check() const;
};
inline FilePCA::FilePCA() : FileCoordinates() {};
FilePCA::~FilePCA(){};
}// end of namespace
