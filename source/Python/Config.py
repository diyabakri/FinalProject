from array import ArrayType
from distutils.command.config import config
from importlib.resources import path
from sqlite3 import Timestamp
import numpy as np
from .filter import Filter

class Config:
    
    itrations:int
    log_p:int
    energyLevel:int
    filter:Filter
    spherical:bool
    resultFormat:str
    resultsPath = []
    timeStamp:str

    def __init__(self,configPath:str,filterpath:str):

        config = open(configPath,"r")
        configLines = config.readlines()

        for i in range(len(configLines)):
            currLine = configLines[i]
            valueIndex = currLine.find('=')+1
            if "itrs" in  currLine:
                self.itrations = (int)(currLine[valueIndex:])
            elif "N" in currLine:
                self.energyLevel = (int)(currLine[valueIndex:])
            elif "logPerod" in currLine:
                self.log_p = (int)(currLine[valueIndex:])
            elif "Type" in currLine:
                b = (int)(currLine[valueIndex:])
                if b > 2:
                    self.spherical = True
                else:
                    self.spherical =False
            elif "TimeStamp" in currLine:
                self.timeStamp = currLine[valueIndex:-1]
            
        pathStr = self.timeStamp+"/results_N%d/results_K%d"
        
        if self.spherical:
            pathStr+= "/results_M%d.txt"
        else:
            pathStr+= ".txt"

        self.resultFormat = pathStr

        self.filter = Filter(filterpath,self.spherical)
        self.createListFiles()
        


    def createListFiles(self):

        for i in range(len(self.filter.orbitList)):            
            orbit = self.filter.orbitList[i]
            if  self.spherical:

                self.resultsPath.append(self.resultFormat%(orbit[0],orbit[1],orbit[2]))
            else:
                self.resultsPath.append(self.resultFormat%(orbit[0],orbit[1]))
