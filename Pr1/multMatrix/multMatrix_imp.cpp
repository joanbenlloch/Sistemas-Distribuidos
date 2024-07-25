//Joan Benlloch   Pedro Morales

#include "multMatrix_imp.h"
#include "multMatrix_stub.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>



multMatrix_imp::multMatrix_imp(int clientId){
	this->clientId = clientId;
	this->mm = new multMatrix();
}

void multMatrix_imp::recvLeeMatrix()
{
    char* buffFileName = nullptr;
	int buffFileNameSize = 0;

	recvMSG(clientId,(void**)&buffFileName,&buffFileNameSize);

	char* fileName = buffFileName;
	matrix_t* fileContent = mm->readMatrix(fileName);
	//envio rows al cliente
	sendMSG(clientId,(const void*)&fileContent->rows,sizeof(int));
	//envío cols
	sendMSG(clientId,(const void*)&fileContent->cols,sizeof(int));
	
	//envío la data
	int dataLen = fileContent->rows*fileContent->cols;
	sendMSG(clientId,(const void*)fileContent->data,dataLen*sizeof(int));

	delete fileName;
	delete fileContent;
	
}

void multMatrix_imp::recvEscribeMatrix()
{
	char* buffFileName = nullptr;
	int buffFileNameSize = 0;

	recvMSG(clientId,(void**)&buffFileName,&buffFileNameSize);
	char* fileName = buffFileName;
	
	int rows;
	int cols;
	int* data;
	matrix_t* matriz_r = new matrix_t[1];
	
    char* recvBuff = nullptr;
	int recvBuffSize = 0;
	
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	rows = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	cols = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	data = (int*)recvBuff;
	matriz_r->rows = rows;
	matriz_r->cols = cols;
	matriz_r->data = data;
	
	mm->writeMatrix(matriz_r,fileName);

	delete fileName;
}

void multMatrix_imp::recvMultMatrix()
{
	
	char* recvBuff = nullptr;
	int recvBuffSize = 0;
	
	int rows;
	int cols;
	int* data;
	matrix_t* resMatrix = new matrix_t[1];
	matrix_t* m1 = new matrix_t[1];
	matrix_t* m2 = new matrix_t[1];
	
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	rows = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	cols = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	data = (int*)recvBuff;
	m1->rows = rows;
	m1->cols = cols;
	m1->data = data;
	
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	rows = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	cols = ((int*)recvBuff)[0];delete[] recvBuff;
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	data = (int*)recvBuff;
	m2->rows = rows;
	m2->cols = cols;
	m2->data = data;
	
	resMatrix = mm->multMatrices(m1, m2);
	
	sendMSG(clientId,(const void**)resMatrix->data,resMatrix->rows*resMatrix->cols*sizeof(int));

	delete m1;
	delete m2;
	delete resMatrix;   
}

void multMatrix_imp::recvCreaRandom()
{
	char* recvBuff = nullptr;
	int recvBuffSize = 0;
	
	int rows = 0;
	int cols = 0;
	int lenData = 0;
	
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	rows = ((int*)recvBuff)[0];delete[] recvBuff;
	
	recvMSG(clientId,(void**)&recvBuff,&recvBuffSize);
	cols = ((int*)recvBuff)[0];delete[] recvBuff;
	
	lenData = rows * cols;
	matrix_t* random_Matrix = mm->createRandMatrix(rows, cols);  
	
	sendMSG(clientId,(const void**)random_Matrix->data,lenData*sizeof(int));
	delete random_Matrix;
}

void multMatrix_imp::recvCreaIndentidad()
{
    char* recvBuff=nullptr;
    int recvBuffSize=0;

    int rows=0;
    int cols=0;

    recvMSG(clientId,( void**)&recvBuff, &recvBuffSize);
    rows=((int*)recvBuff)[0];delete[] recvBuff;

    recvMSG(clientId,(void**)&recvBuff, &recvBuffSize);
    cols=((int*)recvBuff)[0];delete[] recvBuff;

    int lenData = rows * cols;
    matrix_t* identidad = mm->createIdentity(rows, cols);


    sendMSG(clientId,(const void*)identidad->data,lenData*sizeof(int));
    delete identidad;

}

void multMatrix_imp::recvOp(){
	int* typeOp = nullptr;
	int typeOpSize = 0;
	
	do{
		if(!typeOp)delete[] typeOp;
		recvMSG(clientId,(void**)&typeOp,&typeOpSize);
		switch(typeOp[0]){
			case OP_END:
				std::cout<<"FIN COMUNICACIONES\n";
				break;
			case OP_RANDOM:
				recvCreaRandom();
				break;
			case OP_MULTMATRIX:
				recvMultMatrix();
				break;
			case OP_LEEFICHERO:
				recvLeeMatrix();
				break;
			case OP_IDENTITY:
				recvCreaIndentidad();
				break;
			case OP_ESCRIBEFICHERO:
				recvEscribeMatrix();
				break;
		}
	}while(typeOp[0]!=OP_END);
	if(!typeOp)delete[] typeOp;
}



multMatrix_imp::~multMatrix_imp()
{
    delete mm;
	closeConnection(clientId);
}