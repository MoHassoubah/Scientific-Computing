#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H

#include "iequationssolver.h"

class GaussSeidel : public IEquationSolver
{
public:
    GaussSeidel();

public:
    char solveEquations(double **coefficients, double *forcingFunctions, int size, double *roots);

    void setToleranceValue(double tolerance) {m_tolerance = tolerance;}

private:
    bool reorganizeZerosDiagonalCoefficients(double **coeffiecients, int *indices, int size);
    bool changeRowsOrder(double **matrix, int *indices, int size, int currentRow);

    double m_tolerance = 10;   /* default tolerance value */
};

#endif // GAUSSSEIDEL_H
