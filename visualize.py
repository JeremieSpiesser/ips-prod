#!/bin/env python3
# coding: utf-8

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import csv

# This python script opens up a .csv file to visualize the results
# of the Schrodinger calculations.
# Usage : python visualize.py
#   
# Note : The scripts expects two csv files (results.csv and points.csv) organized like such :
# For the results.csv
# traditional matrix with a_i,j = \psi_i(z_j)

# For the points.csv :
#-5;-4;-3;-2;-1;0;1;2;3;4;5




if __name__ == "__main__":
    with open("results.csv",'r') as f:
        # Results contains the matrix of all the results (a_i,j = \psi_i(z_j))
        results = list(csv.reader(f,delimiter=','))

    with open("points.csv",'r') as f:
        # Points is a list of all the points (all the z_i)
        #points = list(csv.reader(f,delimiter=','))
        points = f.readlines()


    ax = Axes3D(plt.figure())

    # Dict containing the results, ordered by precision (n)
    # First key : n : precision
    # Second key : if "Z" : contains the list of all the \psi_n(z_j)
    #              if "P" : contains the list of all the points (duplicate for matplotlib)
    resultsDict={}


    i = 0
    for n,line in enumerate(results):
        for j,res in enumerate(line):
            if n not in resultsDict:
                resultsDict[n] = {"Z": [], "P": []}

            resultsDict[n]["Z"].append(float(points[j]))
            resultsDict[n]["P"].append(float(res))

    main = 0

    for n in resultsDict:
        opacity = 1*(n==main) + 0.6*(n<main) + 0.01*(n>main) 
        size = len(resultsDict[n]["Z"])
        ax.plot(size*[n],resultsDict[n]["Z"], resultsDict[n]["P"], linewidth="3",alpha=opacity)


    ax.set_xlabel('$n$', fontsize=15)
    ax.set_ylabel('$z$', fontsize=15)
    ax.set_zlabel('$\psi_n(z)$', fontsize=15)
    ax.set_title('Résolution de l\'équation de Schrödinger pour différentes \
            précisions')
    plt.show()

