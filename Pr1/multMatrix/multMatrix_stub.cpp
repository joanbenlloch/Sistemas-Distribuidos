//Joan Benlloch   Pedro Morales
#include "multMatrix_stub.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

#define PORT        30001
#define SERVER_IP   "34.229.25.7"


multMatrix_stub::multMatrix_stub()
{
    this->serverId = initClient((char*)SERVER_IP,PORT);
	if(serverId<0)std::cout<<"ERROR:"<<__FILE__<<":"<<__LINE__<<"\n";
}

matrix_t *multMatrix_stub::readMatrix(const char *fileName)
{
    int typeOp = OP_LEEFICHERO;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	std::string fName = fileName;//tal vez se pueda usar el .c_str()
	sendMSG(serverId,(const void*)fileName,fName.length());
	char* buffContent = nullptr;
	int buffContentSize = 0;
	
	int rows = 0;
	int cols = 0;
	int* data = NULL;
	
	recvMSG(serverId,(void**)&buffContent,&buffContentSize);	
	rows = ((int*)buffContent)[0];delete[] buffContent;
	
	recvMSG(serverId,(void**)&buffContent,&buffContentSize);
	cols = ((int*)buffContent)[0];delete[] buffContent;
	recvMSG(serverId,(void**)&buffContent,&buffContentSize);
	data = (int*)buffContent;	
	
	matrix_t* fileContent = new matrix_t[1];
	fileContent->rows = rows;
	fileContent->cols = cols;
	fileContent->data = data;
	
	return fileContent;
    
}

void multMatrix_stub::writeMatrix(matrix_t *m,const char* fileName)
{
	int typeOp = OP_ESCRIBEFICHERO;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
    std::string fName = fileName;
    sendMSG(serverId,(const void*)fileName,fName.length());
    
	void* buffContent = nullptr;
	int buffContentSize = 0;
	
	sendMSG(serverId,(const void*)&m->rows,sizeof(int));
	sendMSG(serverId,(const void*)&m->cols,sizeof(int));
    
	int dataLen = m->rows*m->cols;
	sendMSG(serverId,(const void*)m->data,dataLen*sizeof(int));
}

matrix_t *multMatrix_stub::multMatrices(matrix_t *m1, matrix_t* m2)
{

	int typeOp = OP_MULTMATRIX;
	
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	//Envio la matriz 1
	int sizeM1 = m1->rows * m1->cols;
	sendMSG(serverId,(const void*)&m1->rows,sizeof(int));
	sendMSG(serverId,(const void*)&m1->cols,sizeof(int));
	sendMSG(serverId,(const void*)m1->data,sizeM1*sizeof(int));
	//Envio la matriz 2
	int sizeM2 = m2->rows * m2->cols;
	sendMSG(serverId,(const void*)&m2->cols,sizeof(int));
	sendMSG(serverId,(const void*)&m2->rows,sizeof(int));
	sendMSG(serverId,(const void*)m2->data,sizeM2*sizeof(int));
	
	void* recvBuff= NULL;
	int recvBuffSize = 0;

	//Recibo la data de la solución 
    recvMSG(serverId,(void**)&recvBuff,&recvBuffSize);//si da problemas quitar el cast pq ya es un void **
	//solo necesito la data, las filas y columas del resultado ya los sé
	//con lo que me ahorro dos mensajes
	matrix_t* resMatrix = new matrix_t[1];
	resMatrix->rows = m1->rows;
    resMatrix->cols = m2->cols;
	resMatrix->data = (int*)recvBuff;
	
	
	return resMatrix;
}

matrix_t* multMatrix_stub::createRandMatrix(int rows, int cols)
{
	int typeOp = OP_RANDOM;
	
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	sendMSG(serverId,(const void*)&rows,sizeof(int));
	sendMSG(serverId,(const void*)&cols,sizeof(int));
	
	//El recvBuff va a coger el array de ints que es el data de la matriz random
	int*  recvBuff = nullptr;
	int recvBuffSize = 0;
	
	//Recibo la data de la random ya creada
    recvMSG(serverId,(void**)&recvBuff,&recvBuffSize);
	
	matrix_t* matrix_Random = new matrix_t[1];
	//el tamaño de filas y columnas ya lo se.
	matrix_Random->rows = rows;
	matrix_Random->cols = cols;
	//cast de la data recibida a la data a retornar
	matrix_Random->data = (int*)recvBuff;	

    return matrix_Random;
}

matrix_t* multMatrix_stub::createIdentity(int rows, int cols)
{
    int typeOp=OP_IDENTITY;
    sendMSG(serverId,(const void*)&typeOp, sizeof(int));

    sendMSG(serverId,(const void*)&rows, sizeof(int));
    sendMSG(serverId,(const void*)&cols, sizeof(int));

    int* recvBuff=nullptr;
    int recvBuffSize=0;

    recvMSG(serverId,(void**)&recvBuff,&recvBuffSize);

    matrix_t* matrix_identity = new matrix_t[1];
    matrix_identity->rows  = rows;
    matrix_identity->cols  = cols;
    matrix_identity->data = (int*)recvBuff;

    return matrix_identity;
}


multMatrix_stub::~multMatrix_stub()
{
    int typeOp = OP_END;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	closeConnection(serverId);
}