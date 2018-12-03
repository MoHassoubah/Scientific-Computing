#include "gaussseidel.h"
#include <iostream>

GaussSeidel::GaussSeidel()
{

}

char GaussSeidel::solveEquations(double **coefficients, double *forcingFunctions, int size, double *roots)
{
    if(checkZerosDiagonalCoefficients(coefficients, size))
    {
        std::cout<<"Error!: Gauss Seidel: one or more diagonal coefficient equal zero.\n";
        return -1;
    }
}

bool GaussSeidel::checkZerosDiagonalCoefficients(double **coeffiecients, int size)
{
    for(int i = 0; i < size; ++i)
    {
        if(coeffiecients[i][i] == 0.0)
        {
            return true;
        }
    }

    return false;
}
