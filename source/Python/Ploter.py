import matplotlib.pyplot as plt
import numpy as np
from tkinter import *  
from .ResultsReader import ResultsReader
from .Config import Config
from .macro import*

class Ploter:

    reader:ResultsReader
    config:Config

    def __init__(self,config:Config , reader:ResultsReader):

        self.config = config
        self.reader = reader
        
    def getlimits(slef,N):

        a = N**4
        b = N**2

        c = (a-b)**0.5

        a = N**2 + c
        b = N**2 - c

        return (-a*0.52977210903 , a * 0.52977210903)

    def convertToSpherical(self,results):

        X_list = results[2]*np.cos(results[0])*np.sin(results[1])
        Y_list = results[2]*np.sin(results[0])*np.sin(results[1])
        Z_list = results[2]*np.cos(results[1])
        return np.vstack((X_list,Y_list,Z_list))

    def plotPolar(self):
        
        unit = 1e-8
        
        colors = ['b.','g.','r.','c.','m.','y.','k.','w.']# ploting colors
        


        for i in range(len(self.config.filter.orbitList)): 

            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            if (i > 0 and  n!= self.config.filter.orbitList[i-1][0]) or i==0 :
                plt.figure()
                plt.axes(projection = 'polar')
                plt.xlabel("R($\AA$)")

            results = self.reader.getResultsByNKM(n,k,0)
            plt.polar(results[0],results[1]/unit,label = ('l = '+(str)(k)+'$\hbar$'))
            plt.legend(frameon=True, loc='lower center', ncol=3)
                
        plt.show()

    def sphericalPlot(self):

        unit = 1e-8

        for i in range(len(self.config.filter.orbitList)): 
            
            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            m= orbit[2]

            if (i > 0 and  n!=self.config.filter.orbitList[i-1][0]) or i==0 :

                fig = plt.figure()
                ax = fig.add_subplot(projection = '3d')
                ax.set_xlabel("X($\AA$)")
                ax.set_ylabel("Y($\AA$)")
                ax.set_zlabel("Z($\AA$)")

                lim = self.getlimits(orbit[0])
                
                ax.set_xlim(lim)
                ax.set_ylim(lim)
                ax.set_zlim(lim)

            results = self.reader.getResultsByNKM(n,k,m)
            convertedResults = self.convertToSpherical(results) 
            ax.plot(-convertedResults[0]/unit,-convertedResults[1]/unit,-convertedResults[2]/unit,label = ('k = %d m = %d')%(k,m))
            plt.legend(frameon=True, loc='lower center', ncol=3)
            
        plt.show()

