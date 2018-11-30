#ifndef GAUSSELIMINATION_H
#define GAUSSELIMINATION_H
#include <cmath>

class GaussElimination
{
public:
    GaussElimination();
    ~GaussElimination();
    /*
     *
     *  This will be the main interface to caluclating roots of a system of linear Equations using Gauss Elimination
     *  a00 x1 + a01 x2 = b0
     *  a10 x1 + a11 x2 = b1
     *  i/p: eqsCoeff       -> 2 dimensional array[row][col] that carry matrix of the equations coeffcients
     *                          ex. [ a00, a01, a10, a11]
     *       size           -> size of rows & col & eqForcingCoeff array & eqsRoot array
     *                          ex. 2
     *       eqForcingCoeff -> pointer of array of forcing coeffiecents
     *                          ex. [b0, b1]
     *  o/p: eqsRoot        -> pointer of array of output roots of system of equations
     *                          ex. [x1, x2]
     * */
    char SolveEQs(double **eqsCoeff, double * eqsForcingCoeff, int size, double * eqsRoot);

private:
    char elimainate(double **eqsCoeff, double * eqForcingCoeff, int size, int *row_index, double *array_of_row_biggest);
    void pivot(double **eqsCoeff, int size, int currentIndex, double *array_of_row_biggest, int *rows_ptr_arr);
    void substituteBack(double **upperTriMatrix, double * eqForcingCoeff, int size, double * roots, int *rows_index_arr);


};

#endif // GAUSSELIMINATION_H
