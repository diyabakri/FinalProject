import numpy as np
from .filter import Filter

class Config:
    
    revolutions:int
    iterationMode:bool
    t_inrev:float
    itrations:int
    log_p:int
    energyLevel:int
    filter:Filter
    type:int
    spherical:bool
    resultFormat:str
    resultsPath = []
    timeStamp:str


    def __init__(self,configPath:str,filterpath:str = None):

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
                self.type = (int)(currLine[valueIndex:])
                if self.type > 2:
                    self.spherical = True
                else:
                    self.spherical =False
            elif "TimeStamp" in currLine:
                self.timeStamp = currLine[valueIndex:-1]
            elif "revolutions" in currLine:
                self.revolutions = (int)(currLine[valueIndex:])
            elif "iterationMode" in currLine:
                self.iterationMode = (bool)(currLine[valueIndex:]) 
            elif "t =" in currLine:
                self.t_inrev =  (float)(currLine[valueIndex:])
                 

        pathStr = self.timeStamp+"/results_N%d/results_K%d"
        
        if self.spherical:
            pathStr+= "/results_M%d.txt"
        else:
            pathStr+= ".txt"

        self.resultFormat = pathStr

        if(filterpath != None):
        
            self.filter = Filter(filterpath,self.spherical)
            self.createListFiles()
        
    def setTimeStamp(self,timeStamp:str,spherical:bool):

        self.timeStamp = timeStamp

        pathStr = self.timeStamp+"/results_N%d/results_K%d"
        
        if spherical:
            pathStr+= "/results_M%d.txt"
        else:
            pathStr+= ".txt"

        self.resultFormat = pathStr

        self.spherical = spherical
    
    def createListFiles(self):

        for i in range(len(self.filter.orbitList)):            
            orbit = self.filter.orbitList[i]
            if  self.spherical:

                self.resultsPath.append(self.resultFormat%(orbit[0],orbit[1],orbit[2]))
            else:
                self.resultsPath.append(self.resultFormat%(orbit[0],orbit[1]))

    def __str__(self) -> str:
        string = (str)(self.revolutions)+"\n"+(str)(self.itrations)+"\n"+(str)(self.iterationMode)+"\n"+(str)(self.t_inrev)+"\n"+(str)(self.type)+"\n"+(str)(self.log_p)+"\n"+(str)(self.timeStamp)+"\n"
        return string
