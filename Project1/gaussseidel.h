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
    bool checkZerosDiagonalCoefficients(double **coeffiecients, int size);

    double m_tolerance = 10;   /* default tolerance value */
};

#endif // GAUSSSEIDEL_H
