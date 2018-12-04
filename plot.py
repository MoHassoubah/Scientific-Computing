import sys
import csv
from numpy import *
from matplotlib.pyplot import plot, show, figure


# read CSV file and define column size & row size &
def read_csv(file_name):

    with open(file_name,'r') as fileObj:
        reader = csv.reader(fileObj)
        csv_list = list(reader)

    csv_list.pop(0) #remove the headder
    col_size = len(csv_list[0])
    row_size = len(csv_list) # remove the header
    #reorder the list to be easier to access
    arr_of_elements =[[]]
    for idx in range(0,col_size-1):
        arr_of_elements.append([x[idx] for x in csv_list])
    arr_of_elements.pop(0) #remove the first element that is due to initialization & is empty

    return arr_of_elements

def plot_points(arr_of_elements,color):
    if len(arr_of_elements) == 2:
        plot(arr_of_elements[0],arr_of_elements[1],color+'o')
    elif len(arr_of_elements) == 3:
        plot(arr_of_elements[0],arr_of_elements[1],arr_of_elements[0],color+'o')
    return

# equation_coeff : a0,a1,a2,a3 -> a3X**3+a2X**2+a1X**1+a0
# equation_type : order
# data_range: [start of interval, end of interval]
# step_size : give if data step size is very small
def plot_polynomial_equation(equation_coeff, data_range,step_size=0.01):
    x = arange(data_range[0], data_range[1], step_size)  # get values between -10 and 10 with 0.01 step and set to y
    i = 0
    y =equation_coeff[0] * x**i
    i=i+1
    for idx in range(1,len(equation_coeff)):
        y = y + equation_coeff[idx] * x**i
        i = i + 1

    plot(x,y)
    return

################ Main ########################
# arrayOfElements= read_csv("reg1.csv")
# arrayOfElements1= read_csv("reg2.csv")
arrayOfElements2= read_csv("reg3.csv")
#
# plot_polynomial_equation([1,1,1,1],[-10,10])
# plot_polynomial_equation([1,1],[-10,10])
# plot_polynomial_equation([1,1,1],[-10,10])

# plot_points(arrayOfElements,'r')
# plot_points(arrayOfElements1,'b')
plot_points(arrayOfElements2,'g')
show()