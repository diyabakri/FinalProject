import numpy as np
from source.Python.Config import Config

class ResultsReader:

    config:Config

    def __init__(self,config:Config):
        self.config = config

    def getResultsByNKM(self,n:int,k:int,m:int):
        if(self.config.spherical):
            resultFile = open(self.config.resultFormat%(n,k,m),"r")
        else:
            resultFile = open(self.config.resultFormat%(n,k),"r")

        resultLines = resultFile.readlines()

        resultsArr = []
        phi_arr = []
        roh_arr = []
        th_arr = []

        for i in range(len(resultLines)):
            currLine = resultLines[i]
            
            r_index = currLine.find("r= ")+3
            r_val = currLine[r_index:]
            r = (float)(r_val[:r_val.find("\t")])
            roh_arr.append(r)

            phi_index = currLine.find("phi= ")+5
            phi_val = currLine[phi_index:]
            phi = (float)(phi_val[:phi_val.find("\t")])
            phi_arr.append(phi)
            
            if self.config.spherical:
                th_index = currLine.find("theta= ")+7
                th_val = currLine[th_index:]
                th = (float)(th_val[:th_val.find("\t")])
                th_arr.append(th)
                
        if self.config.spherical:
            resultsArr = np.vstack((phi_arr,th_arr,roh_arr))
        else:
            resultsArr = np.vstack((phi_arr,roh_arr))
            
        return resultsArr 
    
    def getResultsByFile(self,fileName:str):
        
        resultFile = open(fileName,"r")
        resultLines = resultFile.readlines()

        resultsArr = np.array([])
        phi_arr = np.array([])
        roh_arr = np.array([])
        th_arr = np.array([])

        for i in range(len(resultLines)):
            currLine = resultLines[i]
            
            r_index = currLine.find("r= ")+3
            r_val = currLine[r_index:]
            r = (float)(r_val[:r_val.find("\t")])
            np.append(roh_arr,r)

            phi_index = currLine.find("phi= ")+5
            phi_val = currLine[phi_index:]
            phi = (float)(phi_val[:phi_val.find("\t")])
            np.append(phi_arr,phi)
            if self.config.spherical:
                th_index = currLine.find("theta= ")+7
                th_val = currLine[th_index:]
                th = (float)(th_val[:th_val.find("\t")])
                np.append(th_arr,th)
        if self.config.spherical:
            resultsArr = np.vstack((phi_arr,th_arr,roh_arr))
        else:
            resultsArr = np.vstack((phi_arr,roh_arr))
            
        return resultsArr 
    
    def getAllResults(self):
        
        Allresults = []

        for i in range(len(self.config.restultsPath)):
            currFileName = self.config.restultsPath[i]
            Allresults.append(self.getResultsByFile(currFileName))
        
        return np.array(Allresults)