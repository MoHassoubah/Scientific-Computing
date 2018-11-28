#include "gausselimination.h"

GaussElimination::GaussElimination()
{

}

char GaussElimination::SolveEQs(double **eqsCoeff, double * eqsForcingCoeff, int size, double * eqsRoot)
{
    char error = 0;
    int row_index_arr[size];
    double array_of_row_biggest[size];

    /* generate row index arr*/
    for (int i =0; i<size; i++)
    {
        row_index_arr[i] = i; /* will be used in ordering the rows if there is a change */
    }
    /* get the max element in each row in an array of biggest element in a row */
    for (int row_i =0; row_i<size; row_i++)
    {
        array_of_row_biggest[row_i] = fabs(eqsCoeff[row_i][0]);
        for (int col_i=1; col_i<size; col_i++)
        {
            if (array_of_row_biggest[row_i]<eqsCoeff[row_i][col_i])
                array_of_row_biggest[row_i] = fabs(eqsCoeff[row_i][col_i])       ;
        }
    }

    /* elimination step */
    error = elimainate(eqsCoeff, eqsForcingCoeff, size, row_index_arr, array_of_row_biggest);

    /* subistitute back only if no errors in the eliminate step */
    if (error == 0)
        substituteBack(eqsCoeff, eqsForcingCoeff, size, eqsRoot);

    return  error;
}

char GaussElimination::elimainate(double **eqsCoeff, double * eqForcingCoeff, int size, int *rows_index_arr, double *array_of_row_biggest){
    char error =0;

    /* elimination for loop*/
    for (int pivot_row_i =0; pivot_row_i < size-1; pivot_row_i++)
    {
        /* get pivot element and pivot equation and rearrange the array of elements */
        pivot(eqsCoeff, eqForcingCoeff, size, pivot_row_i, array_of_row_biggest, rows_index_arr);
        /* elimination step from the rest of the equations */
        for (int rows_i= pivot_row_i+1; rows_i<size; rows_i++)
        {
            double factor = eqsCoeff[rows_index_arr[rows_i]][rows_index_arr[pivot_row_i]]/eqsCoeff[rows_index_arr[pivot_row_i]][rows_index_arr[pivot_row_i]];

        }
    }
    /* end of elimination for loop */

    return  error;
}

void GaussElimination::pivot(double **eqsCoeff, double * eqForcingCoeff, int size, int currentIndex, double *array_of_row_biggest, int *rows_ptr_arr)
{

}

void GaussElimination::substituteBack(double **upperTriMatrix, double * eqForcingCoeff, int size, double * roots)
{

}


GaussElimination::~GaussElimination()
{

}
