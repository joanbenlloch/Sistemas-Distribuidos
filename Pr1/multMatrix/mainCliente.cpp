//Joan Benlloch   Pedro Morales

#include "multMatrix_stub.h"
void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;

}

//REVISAR EL CMAKELISTS.TXT SI ES EJ0 O EJ0_2
int main(int argc, char** argv)
{
	multMatrix_stub* mmatrix=new multMatrix_stub();


    //matrix_t* m1= mmatrix->createRandMatrix(5,5);
	matrix_t* m1= mmatrix->createIdentity(5,5);
	//matrix_t* m2= mmatrix->createRandMatrix(5,5);
    matrix_t* m2= mmatrix->createIdentity(5,5);
    matrix_t* mres=mmatrix->multMatrices(m1,m2);
	mmatrix->writeMatrix(mres,"resultado.txt");
    matrix_t* m3=mmatrix->readMatrix("resultado.txt");
    matrix_t* mres2=mmatrix->multMatrices(m1,m3);
    mmatrix->writeMatrix(mres2,"resultado2.txt");
	std::cout<<"Datos de m1:"<<std::endl;
	for (int i = 0; i < 25; i++)
        std::cout << m1->data[i] << " ";
	std::cout << std::endl;
	
	std::cout<<"Datos de m2:"<<std::endl;
	for (int i = 0; i < 25; i++)
        std::cout << m2->data[i] << " ";
	std::cout << std::endl;
	
	std::cout<<"Datos de mres:"<<std::endl;
	for (int i = 0; i < 25; i++)
        std::cout << mres->data[i] << " ";
	std::cout << std::endl;
	
	freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
	delete mmatrix;
	
	return 0;
	
	
	
}