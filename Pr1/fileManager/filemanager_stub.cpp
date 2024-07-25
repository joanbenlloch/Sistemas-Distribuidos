//Joan Benlloch   Pedro Morales
#include "filemanager_stub.h"
#include "filemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define PORT        30001
#define SERVER_IP   "34.229.25.7"
using namespace std;


fileManager_stub::fileManager_stub(){
	this->serverId = initClient((char*)SERVER_IP,PORT);
	if(serverId<0)std::cout<<"ERROR:"<<__FILE__<<":"<<__LINE__<<"\n";
}




void fileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){
	int typeOp = OP_LEEFICHERO;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	//ahora tengo que recibir la data y la longitud de la data y guardarlo. 
	//por eso envío sus direcciones de memória
	//envio nombre del fichero
	
	
    sendMSG(serverId,(const void*)fileName,std::strlen(fileName));
	
	//recibo la data
    void* buffContent = nullptr;
    int buffContentSize = 0;

    recvMSG(serverId,(void**)&buffContent,&buffContentSize);

    data = (char*)buffContent;
	dataLength = buffContentSize;
}


void fileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){//La función escribe la data en el documento fileName si existe,
																						   // si no existe lo crea y añade a la lista de ficheros
	int typeOp = OP_ESCRIBEFICHERO;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	//tal vez se pueda usar el .c_str()
	//Envio el nombre del fichero
	sendMSG(serverId,(const void*)fileName,std::strlen(fileName));
	//Envio los datos a escribir en el fichero
	sendMSG(serverId,(const void*)data,dataLength);
	
	
}

vector<string*>* fileManager_stub::listFiles(){
	
	// tipo operacion
    int typeOp = OP_LISTAFICHERO;
    sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	
	char* buffContent = nullptr;
	int buffContentSize = 0;
    recvMSG(serverId,(void**)&buffContent,&buffContentSize);
	int numFicheros = ((int*)buffContent)[0];delete[] buffContent;
	vector<string*>* flist = new vector<string*>();
    char* recvBuff = nullptr;
    int recvBuffSize = 0;
	
    for(int i=0;i<numFicheros; i++){
		recvMSG(serverId,(void**)&recvBuff,&recvBuffSize);		
		char* fichero = recvBuff;		
		std::string* s = new string(fichero);		
		flist->push_back(s);
		
		delete recvBuff;
	}
	return flist;
}


void fileManager_stub::freeListedFiles(vector<string*>* fileList){//yo
	//int typeOp = OP_LIBERAFICHERO;
	//sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	if (fileList == nullptr){
		std::cout<<"Lista de ficheros vacía"<<std::endl;
	}else{
		for(vector<string*>::iterator i=fileList->begin();i!= fileList->end();++i)
		{
			delete *i;
		}
		delete fileList;
	}
}

fileManager_stub::~fileManager_stub(){
	int typeOp = OP_END;
	sendMSG(serverId,(const void*)&typeOp,sizeof(int));
	closeConnection(serverId);	
}