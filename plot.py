from array import ArrayType
from distutils.command.config import config
from typing import List
import matplotlib.pyplot as plt
import subprocess as sp
import numpy as np
from source.Python.Config import Config
from source.Python.ResultsReader import ResultsReader
import platform

def getlimits(N):

    a = N**4
    b = N**2

    c = (a-b)**0.5

    a = N**2 + c
    b = N**2 - c

    return (-a*0.52977210903 , a * 0.52977210903)

def convertToSpherical(results:ArrayType):
    X_list = results[2]*np.cos(results[0])*np.sin(results[1])
    Y_list = results[2]*np.sin(results[0])*np.sin(results[1])
    Z_list = results[2]*np.cos(results[1])
    return np.vstack((X_list,Y_list,Z_list))

def plotPolar(config:Config , reader :ResultsReader):
    
    unit = 1e-8
    
    colors = ['b.','g.','r.','c.','m.','y.','k.','w.']# ploting colors
    

    for n in range(1,config.energyLevel+1): 

        if n < config.kList.min():
            continue

        plt.figure()
        plt.axes(projection = 'polar')
        plt.xlabel("R($\AA$)")

        for k in range(1,n+1):
        
            
            if k not in config.kList and config.kList.all()!= 0:
                continue
            results = reader.getResultsByNKM(n,k,0)
            plt.polar(results[0],results[1]/unit,label = ('l = '+(str)(k)+'$\hbar$'))
            plt.legend(frameon=True, loc='lower center', ncol=3)
        
    plt.show()
    plt.waitforbuttonpress(0)
    plt.close('all')

def sphericalPlot(config:Config , reader:ResultsReader):

    unit = 1e-8

    colors = ['b.','g.','r.','c.','m.','y.','k.','w.']# ploting colors
    
    for n in range(1,config.energyLevel+1): 

        if n < config.kList.min():
            continue

        fig = plt.figure()
        ax = fig.add_subplot(projection = '3d')
        ax.set_xlabel("X($\AA$)")
        ax.set_ylabel("Y($\AA$)")
        ax.set_zlabel("Z($\AA$)")

        lim = getlimits(n)
        
        ax.set_xlim(lim)
        ax.set_ylim(lim)
        ax.set_zlim(lim)
        for k in range(1,n+1):
        
            
            if k not in config.kList and config.kList.all()!= 0:
                continue
            for m in range(k+1):
                if m not in config.mList and config.mList[0]!= -1:
                    continue
                results = reader.getResultsByNKM(n,k,m)
                convertedResults = convertToSpherical(results) 
                ax.plot(-convertedResults[0]/unit,-convertedResults[1]/unit,-convertedResults[2]/unit,label = ('k = %d m = %d')%(k,m))
                plt.legend(frameon=True, loc='lower center', ncol=3)
        
    plt.show()
    plt.waitforbuttonpress(0)
    plt.close('all')

def main():
    
    OS_name = platform.system()
    makeCMD = ""
    
    if(OS_name == "Windows"):
        makeCMD = "mingw32-make"
    else:
        makeCMD = "make"
    
    compile = sp.Popen([makeCMD])
    o,e = compile.communicate()
    prog = sp.Popen([makeCMD,'run'])
    o,e = prog.communicate()
    
    config = Config("config.ini")
    reader =  ResultsReader(config)
    
    if config.spherical:

        sphericalPlot(config,reader)
        
    else:

        plotPolar(config,reader)
    

if(__name__ == "__main__"):
    main()