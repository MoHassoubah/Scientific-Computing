#include "iostream"
#include "gausselimination.h"
#include "gaussseidel.h"
#include "linearregression.h"
#include "interpolation.h"
#include "csvreader.h"


int main(int argc, char *argv[])
{
    /* gauss elimination testing */
    IEquationSolver *Gauss_test_obj = new GaussElimination();
    int size = 4;
    double equ1[4]= {1,-1,2,1};
    double equ2[4]= {3,2,1,4};
    double equ3[4]= {5,8,6,3};
    double equ4[4]= {4,2,5,3};
    double forcingF[4] = {1,1,1,-1};
    double equroots[4];

    double **equations = new double *[size];
    equations[0] = equ1;
    equations[1] = equ2;
    equations[2] = equ3;
    equations[3] = equ4;

    Gauss_test_obj->solveEquations(equations,forcingF,size,equroots);
    std::cout<<"x0="<<equroots[0]<<", x1="<<equroots[1]<<", x2="<<equroots[2]<<", x3="<<equroots[3]<<"\n";
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
    test_obj_1.setEqSolverStrategy(Gauss_test_obj);
    test_obj_1.calculateCoeffs(x,y,no_of_points,order,output_coeffs);
    std::cout<<"a0="<<output_coeffs[0]<<", a1="<<output_coeffs[1]<<", a2="<<output_coeffs[2]<<"\n";
    /* expected output values a0=5, a1=4, a2=-3 */
    /* linear regression testing End */

    {
    /* Test the newton interpolation */
        double x[4];
        x[0] = 1;
        x[1] = 4;
        x[2] = 6;
        x[3] = 5;

        double y[4];
        y[0] = 0;
        y[1] = 1.386294;
        y[2] = 1.791759;
        y[3] = 1.609438;

        double y_of_x, error ;

        int order = 3;
        Interpolation test_obj_1;
        test_obj_1.setEqSolverStrategy(Gauss_test_obj);
        test_obj_1.NewtonsCalcInterpolatingPoly(x,
                                                y,
                                                4,
                                                order, 2, &y_of_x, &error);
        std::cout<<"f"<<order<<"(2)="<<y_of_x<<", R"<<order-1<<"="<<error<<"\n";
    }

    {
        IEquationSolver *Gauss_test_obj = new GaussSeidel();
        /* test cubic spline */
        double x[4];
        x[0] = 3;
        x[1] = 4.5;
        x[2] = 7;
        x[3] = 9;

        double y[4],coeffs[12];
        y[0] = 2.5;
        y[1] = 1;
        y[2] = 2.5;
        y[3] = 0.5;

        Interpolation test_obj_1;
        test_obj_1.setEqSolverStrategy(Gauss_test_obj);
        test_obj_1.CSplineCalculateCoeffs(x, y, 4, coeffs);
        for(int i =0; i < 12; i+=4)
        {
            std::cout<<"coeffs->>"<<i/4<< "  "<<"a = "<<coeffs[i]<< "  "<<"b="<<coeffs[i+1]<< "  "<<"c="<<coeffs[i+2]<< "  "<<"d="<<coeffs[i+3]<<"\n";
        }

        delete Gauss_test_obj;
        Gauss_test_obj = NULL;
    }

    {
        /* test csv reader */
        // Creating an object of CSVWriter
        CSVReader reader("C:/Users/mhassoub/Desktop/Nile masters stuff/3rd term/sceintific computing/assignements/assignement_1/coursework_1/part three datasets/sp1.csv");

        // Get the data from CSV File
        std::vector<std::vector<std::string> > dataList = reader.getData();

        // Print the content of row by row on screen
        for(std::vector<std::string> vec : dataList)
        {
            for(std::string data : vec)
            {
                std::cout<<data << " , ";
            }
            std::cout<<std::endl;
        }
    }

    delete Gauss_test_obj;
    Gauss_test_obj = NULL;

}
