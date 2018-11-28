#include <QCoreApplication>
#include "gausselimination.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   /* gauss elimination testing */
    GaussElimination test_obj;



    return a.exec();
}
