from ast import Lambda
from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import numpy as np
from tkinter import *  
from .ResultsReader import ResultsReader
from .Config import Config
from .Globals import*
from matplotlib import colors, rcParams
from matplotlib.ticker import FormatStrFormatter


class Ploter:

    reader:ResultsReader
    config:Config

    def __init__(self,config:Config , reader:ResultsReader):

        self.config = config
        self.reader = reader
              
    def plotPolar(self):
        # Anit Armstrong 
        unit = 1e-8

        plotTitles = 'abcdefghijklmn'

        for i in range(len(self.config.filter.orbitList)): 

            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            lim = getlimits(n)
            if (i > 0 and  n!= self.config.filter.orbitList[i-1][0]) or i==0 :

                plt.figure()
                plt.xlabel("x ($\AA$)",fontdict=font)
                plt.ylabel("y ($\AA$)",fontdict=font)
                plt.title(("(%c)")%plotTitles[n-1],fontdict=titleFont)
                plt.xticks(fontsize=TICKS_FONT_SIZE)
                plt.yticks(fontsize=TICKS_FONT_SIZE)
                # plt.ylim(lim)

            # results = [Phi , Roh]
            results = self.reader.getResults(n,k,0)
            # results = [x , y]
            results = polarToCartzaian(results)

            lineType = getLineType(k)
            # exg k = 1
            #plt.plot(   X          ,          Y     , "-"   , label = "k = 1" )
            plt.plot(results[0]/unit,results[1]/unit,lineType,label = ('k = '+(str)(k)),linewidth = LINE_WIDTH-2)
            
            # uncomment to show plot legend
            ''' plt.legend(frameon=True, loc='lower center', ncol=3)'''
            
            # plt.savefig("./plots/fig_%s_N_%d_2D.eps"%(self.config.timeStamp,n))

        # drow Center point
        plt.plot(0,0,'ko')
        self.plotDeltaPhi()

        plt.show()

    def plotDeltaPhi(self):

        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])

        for i in range(len(sortedOrbitList)): 

            orbit = sortedOrbitList[i]
            n= orbit[0]
            k= orbit[1]
            reletive = True
            if self.config.type == 1:
                reletive = False
            
            analical_val = calc_accrute_deltaPHi(k,reletive=reletive)
            # analical_val = 0
            
            if (i > 0 and  n!= sortedOrbitList[i-1][0]) or i==0 :
                plt.figure()
                plt.ylabel("$10^8\Delta\psi$",fontdict=font)
                plt.xlabel("revolution number",fontdict=font)
                plt.xticks(range(0,11),fontsize=30) 
                plt.yticks(fontsize=30)
                # plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%.8f'))
            
            results = np.unique(self.reader.getResults(n,k,0,reletive=True))
            analitcal = []

            for j in range(len(results)):
                analitcal.append(analical_val*j)
            
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                lineType = getLineType(k)
                plt.plot(analitcal,lineType,label = ('accurate K = '+(str)(k)),linewidth = LINE_WIDTH)
            
            marker = getMarkerType(k)

            plt.plot(results,marker,label = ('simulated N='+(str)(n)+' K = '+str(k)),markersize = MARKER_SIZE)
    
    def plotDeltaPhiSpherical(self):

        
        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])
        for i in range(len(self.config.filter.orbitList)): 

            orbit = sortedOrbitList[i]

            n= orbit[0]
            k= orbit[1]
            m= orbit[2]
            reletive = True
            if self.config.type == 3:
                reletive = False
            
            analical_val = calc_accrute_deltaPHi(k,reletive=reletive)

            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                plt.figure()
                plt.ylabel("(${rad}$)")
                plt.xlabel("revelution")

            results = np.unique(self.reader.getResults(n,k,m,reletive=True))
            analitcal = []
            for j in range(len(results)):
                analitcal.append(analical_val*j)
            
            plt.plot(results,label = ('simulated N='+(str)(n)+' k='+str(k) + ' m='+str(m)),linewidth = LINE_WIDTH)
            
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :

                plt.plot(analitcal,'.',label = ('accurate K = '+(str)(k)))

            plt.legend(frameon=True, loc='lower center', ncol=3)
        
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

                lim = getlimits(orbit[0])
                
                ax.set_xlim(lim)
                ax.set_ylim(lim)
                ax.set_zlim(lim)

            results = self.reader.getResults(n,k,m)
            convertedResults = convertToSpherical(results) 
            ax.plot(-convertedResults[0]/unit,-convertedResults[1]/unit,-convertedResults[2]/unit,getLineType(k),label = ('k = %d m = %d')%(k,m),linewidth = LINE_WIDTH)
            # plt.legend(frameon=True, loc='lower center', ncol=3)

            # plt.savefig("fig_%s_N_%d_3D.svg"%(self.config.timeStamp,n))

        if self.config.type == 4:
            self.plotDeltaPhiSpherical()
        plt.show()

