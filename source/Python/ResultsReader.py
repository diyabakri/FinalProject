from distutils.command.config import config
import numpy as np
from source.Python.Config import Config
import os

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
            if 'M' in fileName:
                th_index = currLine.find("theta= ")+7
                th_val = currLine[th_index:]
                th = (float)(th_val[:th_val.find("\t")])
                th_arr.append(th)
        
        phi_arr = np.array(phi_arr)
        roh_arr = np.array(roh_arr)
        th_arr = np.array(th_arr)

        if 'M' in fileName:
            resultsArr = np.vstack((phi_arr,th_arr,roh_arr))
        else:
            resultsArr = np.vstack((phi_arr,roh_arr))
        return np.array(resultsArr) 
    
    def changeTimeStamp(self,timeStamp:str = None):
        
        self.config.filter.orbitList = []
        
        newOrbitList = []
        spherical = False

        if timeStamp == None:
            timeStamp = self.config.timeStamp

        nFileList = sorted(os.listdir("./"+timeStamp))
        
        kLists = []

        for nDir in nFileList:
            kLists.append(sorted(os.listdir("./"+timeStamp+"/"+nDir)))
        
        if(".txt" not in kLists[0][0]):
            mLists = []
            spherical = True
            for i in range(len(nFileList)):
                for j in range(len(kLists[i])):
                    mLists.append(sorted(os.listdir("./"+timeStamp+"/"+nFileList[i] +"/"+kLists[i][j])))


            m_index = 0
            for n_index in range(len(nFileList)):
                n =(int)(nFileList[n_index][-1:])
                
                for k_index in range(len(kLists[n_index])):
                
                    k = (int)(kLists[n_index][k_index][-1:])

                    for j in range (len(mLists[m_index])):
                        mFile = mLists[m_index][j]
                        m = mFile[mFile.find(".")-1:]
                        m = (int)(m[0:1])
                        newOrbitList.append([n,k,m])

                    m_index+=1
        else:
            for n_index in range(len(nFileList)):
                n =(int)(nFileList[n_index][-1:])

                for k_index in range(len(kLists[n_index])):
                    k = kLists[n_index][k_index]
                    k = k[k.find(".")-1:]
                    k = (int)(k[0:1])
                    newOrbitList.append([n,k,-1])

        self.config.setTimeStamp(timeStamp,spherical)
        self.config.filter.orbitList = newOrbitList.copy()
        
    def getAllResults(self):
        
        Allresults = []

        for i in range(len(self.config.restultsPath)):
            currFileName = self.config.restultsPath[i]
            Allresults.append(self.getResultsByFile(currFileName))
        
        return Allresults