from array import ArrayType
import numpy as np

class Config:
    
    itrations:int
    log_p:int
    energyLevel:int
    kList:ArrayType
    mList:ArrayType
    spherical:bool
    resultFormat:str
    restultsPath:ArrayType


    def __init__(self,configPath:str):

        config = open(configPath,"r")
        configLines = config.readlines()

        for i in range(len(configLines)):
            currLine = configLines[i]
            valueIndex = currLine.find('=')+1
            if "itrs" in  currLine:
                self.itrations = (int)(currLine[valueIndex:])
            elif "N" in currLine:
                self.energyLevel = (int)(currLine[valueIndex:])
            elif "K_LIST" in currLine:
                self.kList = self.parceIntArray(currLine)
            elif "M_LIST" in currLine:
                self.mList = self.parceIntArray(currLine)
            elif "logPerod" in currLine:
                self.log_p = (int)(currLine[valueIndex:])
            elif "Spherical" in currLine:
                b = (int)(currLine[valueIndex:])
                if b == 1:
                    self.spherical = True
                else:
                    self.spherical =False
            elif "results_path" in currLine:
                self.restultsPath = []
                self.resultFormat = currLine[valueIndex+1:-2]
                self.createListFiles(currLine[valueIndex+1:-2])

    def parceIntArray(self,str:str):
        
        numList = []
        start_index = str.find("=")+1
        numberStr = str[start_index:]
        while True:
            endindex = numberStr.find(",")
            if endindex == -1:
                numList.append(int(numberStr))
                break
            else:
                numList.append(int(numberStr[:endindex]))
                numberStr = numberStr[numberStr.find(",")+1:]
        return np.array(numList)

    def createListFiles(self,str:str):

        for n in range(1,self.energyLevel+1):
            if self.kList[0] != 0 :
                if n < np.min(self.kList):
                    continue
            for k in range(1,n+1):
                if (not (k  in self.kList)) and self.kList.all() != 0:
                    continue
                if self.spherical:
                    for m in range(k+1):
                        if (not (m  in self.mList)) and self.mList.all() != 0:
                            continue
                        self.restultsPath.append(str%(n,k,m))
                else:
                    self.restultsPath.append(str%(n,k,0))

