#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include "iequationssolver.h"

class Interpolation
{
public:
    Interpolation();

    /* given points values for independent variables x1,x2,...,xn & y & num_points
     * calculate coefficents ai,bi,ci,di, where i is from 0 to num_points - 1
     *  */
    char CSplineCalculateCoeffs(double *x, double *y, int num_points, double *coeffs);

    /* given points values for independent variables x1,x2,...,xn & y & num_points
     * calculate coefficents ai,bi,ci,di, where i is from 0 to num_points - 1
     *  */
    char NewtonsCalcInterpolatingPoly(double *x, double *y, int num_points, int order, double xi, double *yint, double *e);

    /* must be called before calling calculateCoeffs in order to
     * define the strategy to solve system the system of linear equations
     *   */
    void setEqSolverStrategy (IEquationSolver * s){m_eqsSolver = s;}

private:

    IEquationSolver * m_eqsSolver;
};

#endif // INTERPOLATION_H
