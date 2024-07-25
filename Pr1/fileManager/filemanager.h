//Joan Benlloch   Pedro Morales
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <dirent.h>

using namespace std;

class FileManager
{
    string dirPath;
    map<string, string* > files;//Como un diccionario con un string que es el nombre del fichero y un puntero a string con su contenido
public:
    FileManager(string path);
	~FileManager();
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};

#endif // FILEMANAGER_H
