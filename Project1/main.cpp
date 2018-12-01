#include <QCoreApplication>
#include "iostream"
#include "gausselimination.h"
#include "linearregression.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   /* gauss elimination testing */
    GaussElimination GaussElimination_test_obj;
    int size = 3;
    double equ1[3]= {70,1,0};
    double equ2[3]= {60,-1,1};
    double equ3[3]= {40,0,-1};
    double forcingF[3] = {636,518,307};
    double equroots[3];

    double **equations = new double *[size];
    equations[0] = equ1;
    equations[1] = equ2;
    equations[2] = equ3;

    GaussElimination_test_obj.solveEquations(equations,forcingF,size,equroots);
    std::cout<<"x0="<<equroots[0]<<", x1="<<equroots[1]<<", x2="<<equroots[2]<<"\n";
    /* expected output values x0=8.59412, x1=34.4118, x2=36.7647 */
    delete [] equations;
    /* gauss elimination testing end */

    /* linear regression testing */
    int order = 2;
    double point1[2]={0,0};
    double point2[2]={2,1};
    double point3[2]={2.5,2};
    double point4[2]={1,3};
    double point5[2]={4,6};
    double point6[2]={7,2};
    double **x = new double *[6];
    x[0] = point1;
    x[1] = point2;
    x[2] = point3;
    x[3] = point4;
    x[4] = point5;
    x[5] = point6;
    int no_of_points = 6;

    double y[6];
    y[0] = 5;
    y[1] = 10;
    y[2] = 9;
    y[3] = 0;
    y[4] = 3;
    y[5] = 27;

    double output_coeffs[3];

    LinearRegression test_obj_1;
    test_obj_1.setEqSolverStrategy(&GaussElimination_test_obj);
    test_obj_1.calculateCoeffs(x,y,no_of_points,order,output_coeffs);
    std::cout<<"a0="<<output_coeffs[0]<<", a1="<<output_coeffs[1]<<", a2="<<output_coeffs[2]<<"\n";
    /* expected output values a0=5, a1=4, a2=-3 */
    /* linear regression testing End */

    return a.exec();
}
