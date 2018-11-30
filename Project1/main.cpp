#include <QCoreApplication>
#include "gausselimination.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   /* gauss elimination testing */
    GaussElimination test_obj;
    double equroots[2];

    double equ1[2]= {1,2};
    double equ2[2]= {1.1,2};
    double forcingF[2] = {10,10.4};
    double **equations = new double *[2];

    equations[0] = equ1;
    equations[1] = equ2;

    test_obj.SolveEQs(equations,forcingF,2,equroots);



    return 0;//a.exec();
}
