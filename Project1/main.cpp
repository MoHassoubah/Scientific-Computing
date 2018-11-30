#include <QCoreApplication>
#include "iostream"
#include "gausselimination.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   /* gauss elimination testing */
    GaussElimination test_obj;
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

    test_obj.SolveEQs(equations,forcingF,size,equroots);
    std::cout<<"x0="<<equroots[0]<<", x1="<<equroots[1]<<", x2="<<equroots[2]<<"\n";
    /* expected output values x0=8.59412, x1=34.4118, x2=36.7647 */
    delete [] equations;
    /* gauss elimination testing end */


    return a.exec();
}
