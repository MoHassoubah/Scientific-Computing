#include "gausselimination.h"

GaussElimination::GaussElimination()
{

}

char GaussElimination::SolveEQs(double **eqsCoeff, double * eqsForcingCoeff, int size, double * eqsRoot)
{
    char error = 0;
    int *row_index_arr = new int [size];
    double *array_of_row_biggest = new double [size];

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
                array_of_row_biggest[row_i] = fabs(eqsCoeff[row_i][col_i]);
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
            for (int col_i=pivot_row_i+1; col_i<size; col_i++)
            {
                eqsCoeff[rows_index_arr[rows_i]][rows_index_arr[col_i]] = eqsCoeff[rows_index_arr[rows_i]][rows_index_arr[col_i]] - factor* eqsCoeff[rows_index_arr[pivot_row_i]][rows_index_arr[col_i]];
            }
            eqForcingCoeff[rows_index_arr[rows_i]] = eqForcingCoeff[rows_index_arr[rows_i]] - factor*eqForcingCoeff[rows_index_arr[pivot_row_i]];
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
    /* solution of the last element X[n][n] = b[n]/a[n][n] */
    roots[size-1] = eqForcingCoeff[size-1]/upperTriMatrix[size-1][size-1];

    /* equation for row n-1 -> a[n-1][n-1]*x[n-1]+a[n-1][n]*x[n] = b[n-1]
     * we know x[n] and w need to get x[n-1]
     * x[n-1]= (b[n-1] - a[n-1][n]*x[n])/a[n-1][n-1]
     * */
    for(int row_i=size-2; row_i>=0; row_i--)
    {
        double sum =0;
        for (int col_i=row_i+1; col_i<size; col_i++)
        {
            sum = sum + upperTriMatrix[row_i][col_i] * roots[col_i];
        }
        roots[row_i] = (eqForcingCoeff[row_i] - sum)/upperTriMatrix[row_i][row_i];
    }

}


GaussElimination::~GaussElimination()
{

}
