#include "gaussseidel.h"
#include <iostream>

GaussSeidel::GaussSeidel()
{
}

char GaussSeidel::solveEquations(double **coefficients, double *forcingFunctions, int size, double *roots)
{
    int *rowIndexArr = new int [size];

    /* generate row index arr*/
    for (int i =0; i<size; i++)
    {
        rowIndexArr[i] = i; /* will be used in ordering the rows if needed to avoid zero value in a diagonal coefficient */
    }
    if(!reorganizeZerosDiagonalCoefficients(coefficients, rowIndexArr, size))
    {
        std::cout << "Error!: Gauss Seidel: one or more diagonal coefficients equal zero, and matrix could not be order.\n";
        return -1;
    }

    return 0;
}

bool GaussSeidel::reorganizeZerosDiagonalCoefficients(double **coeffiecients, int *indices, int size)
{
    for(int i = 0; i < size; ++i)
    {
        if(coeffiecients[i][i] == 0.0)
        {
            if(!changeRowsOrder(coeffiecients, indices, size, i))
            {
                return false;
            }
        }
    }

    return true;
}

bool GaussSeidel::changeRowsOrder(double **matrix, int *indices, int size, int currentRow)
{
    int tempIndex = 0;
    for(int i = 1, targetRow = (currentRow + i) % size;
        targetRow != currentRow;
        ++i, targetRow = (currentRow + i) % size)
    {
        if(matrix[targetRow][currentRow] != 0.0 && matrix[currentRow][targetRow] != 0.0)
        {
            tempIndex = indices[targetRow];
            indices[targetRow] = indices[currentRow];
            indices[currentRow] = tempIndex;
            return true;
        }
    }

    return false;
}
