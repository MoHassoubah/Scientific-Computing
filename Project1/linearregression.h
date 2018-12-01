#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "ieqssolver.h"

class LinearRegression
{
public:
    LinearRegression();

    /* given points values for
     * double dim array of independent variables [(x10,x20,...,xk0,y0),(x11,x21,...,xk1,y1),...., (x1n,x2n,...,xkn,yn)]
     * number of points -> n &
     * order -> k (no of independent variables)
     * calculate coefficents a0,a1,a2,....ak
     *  */
    char calculateCoeffs(double **x, double *y,int no_of_points, int order, double *coeffs);

    /* must be called before calling calculateCoeffs in order to
     * define the strategy to solve system the system of linear equations
     *   */
    void setEqSolverStrategy (IEQsSolver * s){m_eqsSolver = s;}

private:

    IEQsSolver * m_eqsSolver;
};

#endif // LINEARREGRESSION_H
