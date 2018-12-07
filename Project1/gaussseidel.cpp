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
        rowIndexArr[i] = i; /* will be used in ordering the rows if there is a change */
    }
    if(!reorganizeZerosDiagonalCoefficients(coefficients, rowIndexArr, size))
    {
        std::cout<<"Error!: Gauss Seidel: one or more diagonal coefficient equal zero.\n";
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

bool GaussSeidel::changeRowsOrder(double **matrix, int *indices, int size, int current)
{
    for(int i = 0; i < size; ++i)
    {

    }

    return false;
}
