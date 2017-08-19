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
*   @file FilePCA.cpp
*
*   @autor Anna Sinelnikova
*   @data 2017
*/

#include "../include/FilePCA.h"
#include "../include/File1.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace PCA;
using namespace std;

FilePCA::FilePCA(string fileName, int blockNumber) : File1(fileName){

    extention = "pca";
    
    int blockCounter = 0;
    bool prevLineEmpty = false;
    double value;;
    
    string line;
    ifstream fin(fileName);
    
    if(!fin){
	cout<<"Error while reading file:\nCannot find "<<fileName<<".\n";
	exit(1);
    }
    
    if(blockNumber < 0){
	cout<<"Error in while teading file:\ninvalid number of block.\n";
	exit(1);
    }
    
    while(getline(fin, line)){
	stringstream sin(line);
	
	if(blockCounter == blockNumber+1)
	    break;
	    
	else if(line[0]=='\n'||line[0]=='\t'||line[0]==' '){
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	    }
	
	else
	    prevLineEmpty = false;
	    if(blockCounter==blockNumber){
		sin>>value;
		x.push_back(value);
		sin>>value;
		y.push_back(value);
		sin>>value;
		z.push_back(value);
	    }
    }

//    if(!prevLineEmpty) //if file ends without new line
//	blockCounter++;

    if(blockNumber > blockCounter){
	printf("Error while reading file:\nYou have only %i blocks in your file. But you passed me number %i\nNote: in files number of the first block is 1.\n",blockCounter, blockNumber);
	exit(1);
    }
    
    fin.close();
    
    numLines = x.size();
}

FilePCA::~FilePCA(){};

void FilePCA::fillCoordinates(double* x_out, double* y_out, double* z_out) const{

    for(int i=0;i<numLines;i++){
	x_out[i] = x[i];
	y_out[i] = y[i];
	z_out[i] = z[i];
    }

}
