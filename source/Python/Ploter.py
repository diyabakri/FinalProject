import matplotlib.pyplot as plt
import numpy as np
from tkinter import *  
from .ResultsReader import ResultsReader
from .Config import Config
from .macro import*
from matplotlib import colors, rcParams
# rcParams['grid.alpha'] = 0.0
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
        
        for i in range(len(self.config.filter.orbitList)): 

            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            
            if (i > 0 and  n!= self.config.filter.orbitList[i-1][0]) or i==0 :
                plt.figure()
                plt.axes(projection = 'polar')
                plt.xlabel("R($\AA$)")

            results = self.reader.getResultsByNKM(n,k,0)
            plt.polar(results[0],results[1]/unit,label = ('k = '+(str)(k)),linewidth=5)
            plt.legend(frameon=True, loc='lower center', ncol=3)
            plt.savefig("fig_%s_N_%d_2D.svg"%(self.config.timeStamp,n))

        # if  self.config.type ==2 :
            self.plotDeltaPhi()
        plt.show()

    def plotDeltaPhi(self):

        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])

        for i in range(len(sortedOrbitList)): 

            orbit = sortedOrbitList[i]
            n= orbit[0]
            k= orbit[1]
            analical_val = self.calc_accrute_deltaPHi(k)
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                plt.figure()
                plt.ylabel("(${rad}$)")
                plt.xlabel("revelution")

            results = np.unique(self.reader.getResultsByNKM(n,k,0,reletive=True))
            print(results)
            analitcal = []
            for j in range(len(results)):
                analitcal.append(analical_val*j)
            plt.plot(results,label = ('simulated N='+(str)(n)+' K = '+str(k)),linewidth=5)
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                plt.plot(analitcal,'r.',label = ('accurate K = '+(str)(k)))
            plt.legend(frameon=True, loc='lower center', ncol=3)
    
    def plotDeltaPhiSpherical(self):

        
        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])
        for i in range(len(self.config.filter.orbitList)): 

            orbit = sortedOrbitList[i]

            n= orbit[0]
            k= orbit[1]
            m= orbit[2]
            analical_val = self.calc_accrute_deltaPHi(k)
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                plt.figure()
                plt.ylabel("(${rad}$)")
                plt.xlabel("revelution")

            results = np.unique(self.reader.getResultsByNKM(n,k,m,reletive=True))
            analitcal = []
            for j in range(len(results)):
                analitcal.append(analical_val*j)
            
            plt.plot(results,label = ('simulated N='+(str)(n)+' k='+str(k) + ' m='+str(m)),linewidth=3)
            
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :

                plt.plot(analitcal,'r.',label = ('accurate K = '+(str)(k)))

            plt.legend(frameon=True, loc='lower center', ncol=3)
        
    def calc_accrute_deltaPHi(self,k:int):
        
        C =29979245800
        e =4.8032068E-10
        h_bar =1.05457266E-27

        arg1 = h_bar*C*k
        arg1 = (e*e)/arg1
        arg1*=arg1
        arg1 = 1-arg1
        arg1 = np.sqrt(arg1)

        return (((2*np.pi)/arg1)-2*np.pi)

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
            ax.plot(-convertedResults[0]/unit,-convertedResults[1]/unit,-convertedResults[2]/unit,label = ('k = %d m = %d')%(k,m),linewidth=4)
            plt.legend(frameon=True, loc='lower center', ncol=3)
            plt.savefig("fig_%s_N_%d_3D.svg"%(self.config.timeStamp,n))
        if self.config.type == 4:
            self.plotDeltaPhiSpherical()
        plt.show()

