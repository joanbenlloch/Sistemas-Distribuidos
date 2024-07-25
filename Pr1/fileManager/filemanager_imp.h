//Joan Benlloch   Pedro Morales
#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "utils.h"
#include "filemanager.h"

class filemanager_imp{
	
	private:
		FileManager* fm = nullptr;
		int clientId = -1;
	public:
		
		filemanager_imp(int clientId);//done
		~filemanager_imp();//done
		
		void recvListaFichero();
		void recvLiberaFichero();
		void recvLeeFichero();
		void recvEscribeFichero();
		void recvOp();//done
		
};