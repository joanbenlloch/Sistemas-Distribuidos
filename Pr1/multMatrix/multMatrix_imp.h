//Joan Benlloch   Pedro Morales
#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "utils.h"
#include "multmatrix.h"

class multMatrix_imp{
	
	private:
		multMatrix* mm = nullptr;
		int clientId = -1;
	public:
		
		multMatrix_imp(int clientId);
		~multMatrix_imp();
		
		void recvCreaRandom();
		void recvCreaIndentidad();
		void recvMultMatrix();
		void recvLeeMatrix();
		void recvEscribeMatrix();
		void recvOp();
		
};