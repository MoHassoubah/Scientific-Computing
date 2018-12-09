#include "gaussseidel.h"
#include <iostream>
#include <cmath>

#define MAX_ITERATIONS 100

GaussSeidel::GaussSeidel()
{
}

char GaussSeidel::solveEquations(double **coefficients, double *forcingFunctions, int size, double *roots)
{
    int *rowIndexArr = new int [size];

    if(!avoidZeroDiagonalAndMatchConvergenceCriterion(coefficients, rowIndexArr, size))
    {
        std::cout << "Error!: Gauss Seidel: Gauss Seidel will not converge.\n";
        return -1;
    }

    for (int i = 0; i < size; ++i)
    {
        roots[i] = 0.0;
    }

    int i = 0;
    bool toleranceLimitReached = false;
    do
    {
        std::cout << "iteration #" << i << " --> ";
        toleranceLimitReached = iteration(coefficients, forcingFunctions, rowIndexArr, roots, size);
        std::cout << std::endl;
        ++i;
    } while(i < MAX_ITERATIONS && !toleranceLimitReached);

    return 0;
}

bool GaussSeidel::avoidZeroDiagonalAndMatchConvergenceCriterion(double **coeffiecients, int *indices, int size)
{
    for (int i = 0; i < size; ++i)
    {
        indices[i] = -1;
    }

    int rowIndex;
    for(int i = 0; i < size; ++i)
    {
        rowIndex = getTheOrderToConverge(coeffiecients, size, i);

        if(rowIndex == -1 || indices[rowIndex] != -1)
        {
            return false;
        }

        indices[rowIndex] = i;
    }

    return true;
}

int GaussSeidel::getTheOrderToConverge(double **matrix, int size, int rowIndex)
{
    for (int targetRowIndex = 0; targetRowIndex < size; ++targetRowIndex)
    {
        if(convergenceCriterion(matrix, rowIndex, targetRowIndex, size))
        {
            return targetRowIndex;
        }
    }
    return -1;
}

bool GaussSeidel::convergenceCriterion(double **matrix, int i, int diagonalCoeffienientToCheck, int size)
{
    double sum = 0.0;
    for (int j = 0; j < size; ++j)
    {
        if(j != diagonalCoeffienientToCheck)
        {
            sum += fabs(matrix[i][j]);
        }
    }

    return fabs(matrix[i][diagonalCoeffienientToCheck]) > sum;
}

bool GaussSeidel::iteration(double **coefficients, double *forcingFunctions, int *rowIndexArr, double *roots, int size)
{
    double errorPercentages[size];
    for (int i = 0; i < size; ++i)
    {
        errorPercentages[i] = 0;
    }

    for (int i = 0; i < size; ++i)
    {
        calculateXi(coefficients, forcingFunctions, rowIndexArr, roots, errorPercentages, size, i);
    }

    for (int i = 0; i < size; ++i)
    {
        std::cout << "E" << i << " = " << errorPercentages[i] << " | ";
    }

    return isToleranceValueReached(errorPercentages, size);
}

void GaussSeidel::calculateXi(double **coefficients, double *forcingFunctions, int *rowIndexArr, double *roots, double *errorPercentages, int size, int i)
{
    double sum = 0.0, xiOld;
    for (int j = 0; j < size; ++j)
    {
        if(j != i)
        {
            sum += coefficients[rowIndexArr[i]][j] * roots[j];
        }
    }
    xiOld = roots[i];
    roots[i] = (forcingFunctions[rowIndexArr[i]] - sum) / coefficients[rowIndexArr[i]][i];
    errorPercentages[i] = calculateXiErrorPercentage(roots[i], xiOld);
}

double GaussSeidel::calculateXiErrorPercentage(double xi, double xiOld)
{
    return fabs((xi - xiOld) / xi) * 100;
}

bool GaussSeidel::isToleranceValueReached(double *errorPercentages, int size)
{
    bool isReached = true;

    for(int i = 0; i < size; ++i)
    {
        isReached &= (errorPercentages[i] <= m_tolerance);
    }

    return isReached;
}
