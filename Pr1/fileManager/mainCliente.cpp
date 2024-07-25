//Joan Benlloch   Pedro Morales
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "filemanager_stub.h"
using namespace std;

enum Opciones{
	ls,
	upload,
	download,
	salir,
	invalid	
};

Opciones resolverOpciones(string input);

int main()
{
    bool salir_b = false;
	 
    string data;
	string dirPath = "/home/ubuntu/dirFicheros/";
	string path;
	FILE* f;
	char* data_c;
    unsigned long int fileLen=0;
	unsigned long int dataLength;
    string file;
	string file2;
	char* file_c;
	char* file_c2;
    char* rutaRemoto;
    string comando;
	fileManager_stub *fm=new fileManager_stub();
	vector<string*>* vfiles = nullptr;

        do {
            system("cls");
            std::cout << "\n\nMenu de Opciones \n";
            std::cout << "ls - listar archivos remotos\n";
            std::cout << "upload - almacenar un archivo en remoto\n";
            std::cout << "download - almacenar archivo remoto en local\n";
            std::cout << "exit - salir\n";

            std::cout << "\nIngrese un comando: ";
            std::cin >> comando;

            switch (resolverOpciones(comando)) {
                case ls:
                    vfiles=fm->listFiles();
                    cout<<"\n\nLista de ficheros en el directorio remoto:\n";
                    for(unsigned int i=0;i<vfiles->size();++i)
                    {
                        cout<<"Fichero "<<i+1<<": "<<vfiles->at(i)->c_str()<<endl;
                    }
                    break;

                case upload:
					
                    
                    std::cout << "\nEscribe que nombre del archivo a guardar en remoto: \n";
					std::cin >> file;
					file_c = &file[0];
					path=dirPath+"/"+string(file_c);
					f=fopen(path.c_str(),"r");
					fseek(f, 0L, SEEK_END);
					dataLength= ftell(f);
					fseek(f, 0L, SEEK_SET);
					data_c=new char[dataLength];

					fread(data_c,dataLength,1,f);
					fclose(f);
                    fm->writeFile(file_c,data_c,dataLength); 
                    std::cout<<"El archivo ha sido guardado en el directorio remoto\n";
                    break;

                case download:
                    std::cout << "\nEscriba el nombre del archivo que quiere descargar: ";
					cin.ignore();
                    std::cin >> file;
					file_c = &file[0];
					fileLen = std::strlen(file_c) -1;
                    fm->readFile(file_c,data_c,dataLength);
					path=dirPath+"/"+string(file_c);
					//dataLength = std::strlen(data_c);
					std::cout << "Tamaño del contenido: " << dataLength << std::endl;
					f=fopen(path.c_str(),"w");
					fwrite(data_c,dataLength,1,f);
					fclose(f);
                    std::cout<<"El archivo ha sido guardado en local\n";
					std::cout<<"Contenido:\n"<<data_c<<std::endl;
					
                    break;

                case salir:
                    salir_b = true;
					std::cout<<"FIN COMUNICACIONES"<<std::endl;
                    fm->freeListedFiles(vfiles); //liberamos antes de salir
					delete fm;
                    break;

                case invalid:
                    std::cout<<"\nEl comando no existe, intentelo de nuevo" << std::endl;
                    break;
            }
        } while(!salir_b);

    return 0;
}

Opciones resolverOpciones(string input){
	if(input == "ls"){
		std::cout<<"Ls"<<std::endl;
		return ls;
	}else if(input == "download"){
		return download;
	}else if(input == "upload"){
		return upload;
	}else if(input == "exit"){
		return salir;
	}else{
		return invalid;
	}
}