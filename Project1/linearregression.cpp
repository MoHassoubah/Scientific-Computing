#include "linearregression.h"

LinearRegression::LinearRegression(IEquationSolver *s)
{
    m_eqsSolver = s;
}

char LinearRegression::calculateCoeffs(double **x, double *y, int no_of_points, int order, double *coeffs){
    char error = 0;
    int size = order + 1;
    double **equations_coeffs = new double *[size];
    double equations_Forcing_coeff[size];

    /* define a space for the equations_coeffs (2 dimensional array)*/
    for (int i =0; i<size; i++)
    {
        double *eq = new double [size];
        equations_coeffs[i] = eq;
    }

    /* calculate the equations coeffeicents for system of linear equations */
    for (int x_idx1=1; x_idx1 <= size; x_idx1++)
    {
        for (int x_idx2 =1; x_idx2 <= x_idx1; x_idx2++)
        {
            double sum=0;
            for (int point_idx=0; point_idx<no_of_points; point_idx++)
            {
                if (((x_idx1-2) != -1) && ((x_idx2-2) != -1))
                    sum = sum + x[point_idx][x_idx1-2] * x[point_idx][x_idx2-2];
                 else if ((x_idx1-2) != -1)
                    sum = sum + x[point_idx][x_idx1-2];
                else if ((x_idx2-2) != -1)
                    sum = sum + x[point_idx][x_idx2-2];
                else
                    sum = sum + 1;
            }
            equations_coeffs[x_idx1-1][x_idx2-1] = sum;
            equations_coeffs[x_idx2-1][x_idx1-1] = sum;
        }

        double sum =0;
        for (int point_idx=0; point_idx<no_of_points; point_idx++)
        {
            if ((x_idx1-2) != -1)
                sum = sum + y[point_idx] * x[point_idx][x_idx1-2];
            else
                sum = sum + y[point_idx];
        }
        equations_Forcing_coeff[x_idx1-1] = sum;
    }

    /*solve the system of linear equations */
    m_eqsSolver->solveEquations(equations_coeffs, equations_Forcing_coeff, size, coeffs);


    return error;
}
