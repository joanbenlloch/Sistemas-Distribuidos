//Joan Benlloch   Pedro Morales

#include "filemanager_imp.h"
#include "filemanager_stub.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>


filemanager_imp::filemanager_imp(int clientId){
	this->clientId = clientId;
	this->fm = new FileManager("/home/ubuntu/dirPrueba/");
}

void filemanager_imp::recvLeeFichero(){
	//recibo el nombre del fichero a leer y lo guardo
    char* buffFileName = nullptr;
    int buffFileNameSize;

    recvMSG(clientId,(void**)&buffFileName,&buffFileNameSize);
    char* fileName = buffFileName;
	char* fileName_c = new char[buffFileNameSize+1];
	strcpy(fileName_c, fileName);
	fileName_c[buffFileNameSize]='\0';
	std::cout<<"Nombre del fichero en el filemanager_imp: "<< fileName_c << std::endl;

    //leo la data
    char* data;
    unsigned long int dataLength;
    fm->readFile(fileName_c,data,dataLength);

	//std::cout<<"Tamaño del contenido: "<< dataLength << std::endl;
    //envio la data
    sendMSG(clientId,(const void*)data,std::strlen(data));

    //envio la longitud
	//std::cout<<"Tamaño del contenido: "<< dataLength
    //sendMSG(clientId,(const void*)&dataLength,sizeof(unsigned long int));

    //libero
    delete fileName;
	delete fileName_c;
	
}

void filemanager_imp::recvEscribeFichero(){//yo
	
	char* buffFileName1 = nullptr;
	int buffFileNameSize1 = 0;
	recvMSG(clientId,(void**)&buffFileName1,&buffFileNameSize1);
	char* fileName = buffFileName1;
	char* fileName_c = new char[buffFileNameSize1+1];
	strcpy(fileName_c, fileName);
	fileName_c[buffFileNameSize1]='\0';
	std::cout<<"Nombre del fichero en el filemanager_imp: "<< fileName_c << std::endl;
	char* buffFileName2 = nullptr;
	int buffFileNameSize2 = 0;
	recvMSG(clientId,(void**)&buffFileName2,&buffFileNameSize2);
	char* data = buffFileName2;
	
	fm->writeFile(fileName_c,data, buffFileNameSize2);
	
	delete buffFileName1;
	delete buffFileName2;
	
}

void filemanager_imp::recvListaFichero(){//revisar el tamaño del string que se envia, funcion length
	
	 //listo los ficheros
    vector<string*>* flist=new vector<string*>();
    flist = fm->listFiles();
	//envio primero número de ficheros que tengo
	int tam = (int)flist->size();
	sendMSG(clientId,(const char*)&tam,sizeof(int));
	//envio la lista de ficheros
    for(int i=0;i<flist->size(); i++){
		sendMSG(clientId,(const char*)flist->at(i)->c_str(),flist->at(i)->length()+1);
	}
	
	delete flist;
}

void filemanager_imp::recvLiberaFichero(){//yo
	
	
}

void filemanager_imp::recvOp(){
	int* typeOp = nullptr;
	int typeOpSize = 0;
	do{
		if(!typeOp)delete[] typeOp;
		recvMSG(clientId,(void**)&typeOp,&typeOpSize);
		switch(typeOp[0]){
			case OP_LIBERAFICHERO:
				recvLiberaFichero();
				break;				
			case OP_LISTAFICHERO:
				recvListaFichero();
				break;
			case OP_ESCRIBEFICHERO:
				recvEscribeFichero();
				break;
			case OP_END:
				std::cout<<"FIN COMUNICACIONES\n";
				break;
			case OP_LEEFICHERO:
				recvLeeFichero();
				break;
			default:
				std::cout<<"ERROR Operacion "<< typeOp[0]<<" no existe\n";
		}
	}while(typeOp[0]!=OP_END);
	if(!typeOp)delete[] typeOp;
	
}

filemanager_imp::~filemanager_imp(){
	closeConnection(clientId);
	delete fm;	
	
}