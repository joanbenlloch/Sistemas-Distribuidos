//Joan Benlloch   Pedro Morales
#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"

#define OP_END 		   	  0
#define OP_LEEFICHERO     1
#define OP_ESCRIBEFICHERO 2
#define OP_LIBERAFICHERO  3
#define OP_LISTAFICHERO	  4

using namespace std;

class fileManager_stub
{
private:
	int serverId = -1;
public:
    fileManager_stub();
	~fileManager_stub();
	
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};