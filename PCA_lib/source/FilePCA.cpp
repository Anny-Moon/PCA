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

FilePCA::FilePCA(string fullFileName, int blockNumber) : File1(fullFileName){

    extention = ".pca";
    
    ifstream fin(fullFileName);
    
    if(!fin){
	cout<<"Error while reading file:\nCannot find "<<fullFileName<<".\n";
	exit(1);
    }
    
    if(blockNumber < 0){
	cout<<"Error in while teading file:\ninvalid number of block.\n";
	exit(1);
    }
    
    string line;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    double value;
    
    while(getline(fin, line)){
	stringstream sin(line);
	
	if(blockCounter == blockNumber+1)
	    break;
	    
	else if(line.find_first_not_of(" \t\n\v\f\r") == std::string::npos){
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	}
	
	else{
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
    }

    if(prevLineEmpty) //if file ends with new line
	blockCounter--;

    if(blockNumber > blockCounter){
	printf("Error while reading file:\nYou have only %i blocks in your file. But you passed me number %i.\n",blockCounter+1, blockNumber);
	printf("Hint: block counting starts with 0, i.e the last block has number %i!\n", blockCounter);
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

int FilePCA::countBlocks() const{

    ifstream fin(fullFileName);
    
    if(!fin){
	cout<<"Error while reading file:\nCannot find "<<fullFileName<<"\n";
	exit(1);
    }
    
    string line;
    int blockCounter = 0;
    bool prevLineEmpty = false;
    
    while(getline(fin, line)){
	stringstream sin(line);
	
	if(line.find_first_not_of(" \t\n\v\f\r") == std::string::npos){
	    if(!prevLineEmpty)
		blockCounter++;
	    prevLineEmpty = true;
	}
	
	else{
	    prevLineEmpty = false;
	}
    }

    if(prevLineEmpty) //if file ends with new line
	blockCounter--;

    fin.close();
    return blockCounter+1;
}

void FilePCA::check() const{
    for(int i=0;i<x.size();i++)
	cout<<x[i]<<"\t"<<y[i]<<"\t"<<z[i]<<"\n";

}