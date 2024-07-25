//Joan Benlloch   Pedro Morales
#define MULTMATRIX_H
#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"
#include "multmatrix.h"

#define OP_END 		   	  0
#define OP_RANDOM 	   	  1
#define OP_MULTMATRIX     2
#define OP_LEEFICHERO     3
#define OP_IDENTITY	  	  4
#define OP_ESCRIBEFICHERO 5


class multMatrix_stub
{
	private:
		int serverId = -1;
	
	public:
		multMatrix_stub();
		matrix_t* readMatrix(const char* fileName);
		matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
		void writeMatrix(matrix_t* m,const char *fileName);
		
		~multMatrix_stub();
		
		matrix_t *createIdentity(int rows, int cols);
		matrix_t *createRandMatrix(int rows, int cols);
};