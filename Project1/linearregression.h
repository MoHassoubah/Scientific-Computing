#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "iequationssolver.h"

class LinearRegression
{
public:
    LinearRegression();

    /* given points values for independent variables x1,x2,...,xn & y & order n
     * calculate coefficents a0,a1,a2,....an-1
     *  */
    char calculateCoeffs(double **x, double *y, int order, double *coeffs);

    /* must be called before calling calculateCoeffs in order to
     * define the strategy to solve system the system of linear equations
     *   */
    void setEqSolverStrategy (IEquationSolver * s){m_eqsSolver = s;}

private:

    IEquationSolver * m_eqsSolver;
};

#endif // LINEARREGRESSION_H
