#include <string.h>
#include <limits>
#include "interpolation.h"

Interpolation::Interpolation()
{

}

char Interpolation::CSplineCalculateCoeffs(double *x, double *y, int num_points, double *coeffs){
    char error = 0;
    const int size = num_points - 1;
    double **equations_coeffs = new double *[4*size];
    double equations_Forcing_coeff[4*size];

    for (int i =0; i<4*size; i++)
    {
        double *eq = new double [4*size];
        (void)memset(eq, 0, sizeof(double)*4*size);
        equations_coeffs[i] = eq;
    }

    (void)memset(equations_Forcing_coeff, 0, sizeof(double)*4*size);

    /* calculate the equations coeffeicents for system of linear equations */
    /*The first and last functions must pass through endpoints (2 cond.) */
    equations_coeffs[0][0] = x[0] * x[0] * x[0];
    equations_coeffs[0][1] = x[0] * x[0];
    equations_coeffs[0][2] = x[0];
    equations_coeffs[0][3] = 1;
    equations_Forcing_coeff[0] = y[0];

    equations_coeffs[1][(4*size) - 4] = x[size] * x[size] * x[size];
    equations_coeffs[1][(4*size) - 3] = x[size] * x[size];
    equations_coeffs[1][(4*size) - 2] = x[size];
    equations_coeffs[1][(4*size) - 1] = 1;
    equations_Forcing_coeff[1] = y[size];

    /*The second derivatives at endpoints are zero (2 cond.) */
    equations_coeffs[2][0] = x[0] * 6;
    equations_coeffs[2][1] = 2;

    equations_coeffs[3][(4*size) - 4] = x[size] * 6;
    equations_coeffs[3][(4*size) - 3] = 2;

    int row_cnt = 3;
    /* Function values must be equal at interior knots (2n‐2 conditions) */
    for(int i = 1; i < num_points - 1; i++)
    {
        for(int j = i-1; j < i+1; j++)
        {
            int col_idx = 4 * j;
            equations_coeffs[row_cnt + j + 1][col_idx] = x[i] * x[i] * x[i];
            equations_coeffs[row_cnt + j + 1][col_idx + 1] = x[i] * x[i];
            equations_coeffs[row_cnt + j + 1][col_idx + 2] = x[i];
            equations_coeffs[row_cnt + j + 1][col_idx + 3] = 1;
            equations_Forcing_coeff[row_cnt + j + 1] = y[i];
        }

        row_cnt++;
    }

    row_cnt = row_cnt + num_points - 1;

    for(int i = 1; i < num_points - 1; i++)
    {
        int col_idx = 4 * (i-1);

        /* First derivatives at internal knots must be equal (n‐1 cond.) */
        equations_coeffs[row_cnt][col_idx] = 3 * x[i] * x[i];
        equations_coeffs[row_cnt][col_idx + 1] = 2 * x[i];
        equations_coeffs[row_cnt][col_idx + 2] = 1;

        equations_coeffs[row_cnt][col_idx + 4] = -3 * x[i] * x[i];
        equations_coeffs[row_cnt][col_idx + 5] = -2 * x[i];
        equations_coeffs[row_cnt][col_idx + 6] = -1;

        row_cnt++;

        /* Second derivatives at internal points must be equal (n‐1 cond.) */
        equations_coeffs[row_cnt][col_idx] = 6 * x[i];
        equations_coeffs[row_cnt][col_idx + 1] = 2 ;

        equations_coeffs[row_cnt][col_idx + 4] = -6 * x[i];
        equations_coeffs[row_cnt][col_idx + 5] = -2;

        row_cnt++;
    }

    /*solve the system of linear equations */
    m_eqsSolver->solveEquations(equations_coeffs, equations_Forcing_coeff, size, coeffs);


    return error;
}

char Interpolation::NewtonsCalcInterpolatingPoly(double *x,
                                                  double *y,
                                                  int num_points,
                                                  int order, double xi, double *yint, double *e)
{
    char error = 0;
    int order_plus_1 = order + 1;
    double **finite_diffs = new double *[order_plus_1];

    /* set to invalid values */
    *yint = std::numeric_limits<double>::max();
    *e = std::numeric_limits<double>::max();

    for (int i =0; i<order_plus_1; i++)
    {
        double *eq = new double [order_plus_1];
        (void)memset(eq, 0, sizeof(double)*order_plus_1);
        finite_diffs[i] = eq;
    }

    if(order < num_points)
    {
        for(int i = 0; i < order_plus_1; i++)
        {
            finite_diffs[i][0] = y[i];
        }

        for(int j = 1; j < order_plus_1; j++)
        {
            for(int i = 0; i < (order_plus_1 - j); i++)
            {
                finite_diffs[i][j] = (finite_diffs[i+1][j-1] - finite_diffs[i][j-1]) /
                        (x[i+j] -x[i]);
            }
        }

        double xterm = 1;
        double yint_loc[order_plus_1], ea_loc[order];

        yint_loc[0] = finite_diffs[0][0];

        for(int i = 1; i < order_plus_1; i++)
        {
            xterm = xterm * (xi - x[i-1]);
            yint_loc[i] = yint_loc[i-1] + (finite_diffs[0][i] * xterm);
            ea_loc[i-1] = yint_loc[i] - yint_loc[i-1];
        }

        *yint = yint_loc[order_plus_1 -1];
        *e = ea_loc[order -1];
    }
    else
    {
        error = 1;
    }

    return error;
}

