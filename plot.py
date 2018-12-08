__author__ = 'asabry'

import sys
import csv
from os import  walk
from numpy import *
from matplotlib.pyplot import plot, show, figure, axes



# read CSV file and define column size & row size &
def read_points_from_csv(file_name):
    with open(file_name, 'r') as fileObj:
        reader = csv.reader(fileObj)
        csv_list = list(reader)

    csv_list.pop(0)  # remove the headder
    col_size = len(csv_list[0])
    row_size = len(csv_list)  # remove the header
    # reorder the list to be easier to access
    arr_of_elements = [[]]
    for idx in range(0, col_size):
        arr_of_elements.append([float(x[idx]) for x in csv_list])
    arr_of_elements.pop(0)  # remove the first element that is due to initialization & is empty

    return arr_of_elements


# read CSV file and define column size & row size &
def read_equation_coeff_from_csv(file_name):
    with open(file_name, 'r') as fileObj:
        reader = csv.reader(fileObj)
        csv_list = list(reader)

    csv_list.pop(0)  # remove the headder

    return csv_list


def plot_3d_points(arr_of_elements):
    ax = axes(projection='3d')

    # Data for three-dimensional scattered points
    ax.scatter3D(arr_of_elements[0], arr_of_elements[1], arr_of_elements[2], c=arr_of_elements[2], cmap='Greens');
    return


def plot_points(arr_of_elements, color='r'):
    if len(arr_of_elements) == 2:
        plot(arr_of_elements[0], arr_of_elements[1], color + 'o')
    elif len(arr_of_elements) == 3:
        plot_3d_points(arr_of_elements)  # give this a 3D option
    return


# equation_coeff : a0,a1,a2,a3 -> a3X**3+a2X**2+a1X**1+a0
# equation_type : order
# data_range: [start of interval, end of interval]
# step_size : give if data step size is very small
def plot_polynomial_equation(equation_coeff, data_range, step_size=0.01,color ='g'):
    x = arange(float(data_range[0]), float(data_range[1]),
               step_size)  # get values between -10 and 10 with 0.01 step and set to y
    i = 0
    y = float(equation_coeff[0]) * x ** i
    i = i + 1
    for idx in range(1, len(equation_coeff)):
        y = y + float(equation_coeff[idx]) * x ** i
        i = i + 1

    plot(x, y, color)
    return


def plot_3d_equation(arr_of_elements):
    ax = axes(projection='3d')

    # Data for a three-dimensional line
    ax.plot3D(arr_of_elements[0], arr_of_elements[1], arr_of_elements[2], 'gray')
    return


# equation_coeff : a0,a1,a2,a3 -> a2X2+a1X1+a0 or a1X1+a0
# equation_type : order 1,2
# data_range: [start of interval, end of interval]
# step_size : give if data step size is very small
def plot_linear_equation(equation_coeff, data_range=[-1000, 1000], data_range2=[-1000, 1000], step_size=0.01):
    if (len(equation_coeff) == 2):
        x = arange(float(data_range[0]), float(data_range[1]),
                   step_size)  # get values between -10 and 10 with 0.01 step and set to y
        y = float(equation_coeff[0]) + x * float(equation_coeff[1])

        plot(x, y)
    elif (len(equation_coeff) == 3):
        x1 = arange(float(data_range[0]), float(data_range[1]),
                    step_size)  # get values between -10 and 10 with 0.01 step and set to y
        # calculate the step size for the 2nd line to be equal the frist line
        step_size2 = (float(data_range2[1]) - float(data_range2[0])) / (
        (float(data_range[1]) - float(data_range[0])) / step_size)
        x2 = arange(float(data_range2[0]), float(data_range2[1]), step_size2)
        y = float(equation_coeff[0]) + x1 * float(equation_coeff[1]) + x2 * float(equation_coeff[1])

        plot_3d_equation([x1, x2, y])
    return


# equation_coeff : a0,a1,a2,a3,...,an -> a0+a1(x-x0)+a2(x-x0)(x-x1)+...+an-1(x-x0)(x-x1)..(x-xn-1)
# x_points : x0,x1,x2,...xn
# data_range: [start of interval, end of interval]
# step_size : give if data step size is very small
def plot_newton_equation(equation_coeff, x_points, data_range, step_size=0.01,color='r'):
    x = arange(float(data_range[0]), float(data_range[1]),
               step_size)  # get values between data_range[1] and data_range[1] with 0.01 step and set to y
    y = float(equation_coeff[0])
    i = 1
    for idx in range(1, len(equation_coeff)):
        x_fun = 1
        for x_idx in range(0,i):
            x_fun *= (x - x_points[i])
        y += float(equation_coeff[idx]) * x_fun
        i += 1
    plot(x, y, color)

    return


################ Main ########################
# testing all but newton function
# arrayOfElements = read_points_from_csv("reg1.csv")
# arrayOfElements1 = read_points_from_csv("reg2.csv")
# arrayOfElements2 = read_points_from_csv("reg3.csv")
# eq_coeff_range = read_equation_coeff_from_csv("reg3_sp1.csv")
# figure()
# plot_polynomial_equation(eq_coeff_range[0][0:-2], eq_coeff_range[0][-2:len(eq_coeff_range[0])])
# plot_linear_equation(eq_coeff_range[0][0:-2], eq_coeff_range[0][-2:len(eq_coeff_range[0])])
#
# # plot_polynomial_equation([1,1],[-10,10])
# # plot_polynomial_equation([1,1,1],[-10,10])
# figure()
# plot_points(arrayOfElements)
# plot_points(arrayOfElements1, 'b')
#
# figure()
# plot_points(arrayOfElements2, 'g')
#
# # show reset the figure index and show the previous figures
# show()

#loop on the files inside a folder and draw the figname_function.csv
path = "./project1/part_three_datasets/"
for (dirpath, dirnames, filenames) in walk(path):
    for filename in filenames:
        fig_function = filename.split('_')
        filename = path + filename
        # draw raw data
        if len(fig_function) == 1:
            figure(fig_function[0].split('.')[0])
            points = read_points_from_csv(filename)
            plot_points(points,'b')
        elif len(fig_function) == 2:
            #plot Newton data
            if fig_function[1] == "newton.csv":
                figure(fig_function[0])
                row_arr = read_equation_coeff_from_csv(filename)
                points = read_points_from_csv(path+fig_function[0]+'.csv')
                plot_newton_equation(row_arr[0][0:-1], points[0], [min(points[0]),max(points[0])])

            #plot spline data
            elif fig_function[1] == "spline.csv":
                figure(fig_function[0])
                row_arr = read_equation_coeff_from_csv(filename)
                for row in row_arr:
                    step_size = (float(row[-1]) - float(row[-2]))/1000
                    if step_size == 0.0:
                        print("range are equal in file: ",filename,"\nrow: ",row)
                    else:
                        plot_polynomial_equation(row[0:-2], row[-2:len(row)], step_size)


            else:
                print("wrong function in file name")
        else:
            print('Error wrong file name many _')
show()