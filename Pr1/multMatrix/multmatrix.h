//Joan Benlloch   Pedro Morales
#ifndef MULTMATRIX_H
#define MULTMATRIX_H
#include "utils.h"

class multMatrix
{
public:
    multMatrix();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    ~multMatrix();
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};

#endif // MULTMATRIX_H
