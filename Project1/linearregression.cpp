#include "linearregression.h"

LinearRegression::LinearRegression()
{

}

char LinearRegression::calculateCoeffs(double **x, double *y, int order, double *coeffs){
    char error = 0;
    int size = order + 1;
    double **equations_coeffs = new double *[size];
    double equations_Forcing_coeff[size];
    /* calculate the equations coeffeicents for system of linear equations */


    /*solve the system of linear equations */
    m_eqsSolver->solveEquations(equations_coeffs, equations_Forcing_coeff, size, coeffs);


    return error;
}
