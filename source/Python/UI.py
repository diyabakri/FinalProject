
from doctest import master
import os
from tkinter import *
from PIL import Image, ImageTk
from .Ploter import Ploter
from .Config import Config
from .ResultsReader import ResultsReader
import platform
import subprocess as sp
from .Globals import*



class UI:

    config:Config
    reader:ResultsReader
    root:Tk
    listbox:Listbox
    configWin:Toplevel
    configInfoText: StringVar
    filterInfoText: StringVar
    polarImg:Image
    sphircalImg:Image
    renderImg:ImageTk
    image:Label
    def __init__(self,config:Config,reader:ResultsReader,ploter:Ploter):

        self.config = config
        self.reader = reader
        self.ploeter = ploter
        self.root = Tk()
        self.root.title("Bohr's Spin Simulation")
        self.root.iconphoto(False, PhotoImage(file='icon.png'))
        self.listbox = Listbox()
        self.configInfoText = StringVar()
        self.filterInfoText = StringVar()
        self.configInfoText.set(""+str(config))
        self.filterInfoText.set(""+str(config.filter))
        self.polarImg = Image.open("./imgs/2D.png").resize((300,300))
        self.sphircalImg = Image.open("./imgs/3D.png").resize((300,300))
        self.image = Label()
        self.refreshImage()

        self.initUi()

    def selectRes(self,args):
    
        for i in self.listbox.curselection():
            newTimeStamp = self.listbox.get(i)
        
        self.setInfo(newTimeStamp)
        
    def showRes(self):
        
        if self.config.spherical:

            self.ploeter.sphericalPlot()
            
        else:

            self.ploeter.plotPolar()

    def setInfo(self,newTimeStamp:str):

        resultsList = os.listdir(RESULT_P+newTimeStamp)
        
        for file in resultsList:
            if "meta.txt" in file:
                self.config.readFromFile(RESULT_P+newTimeStamp+"/meta.txt")
                self.configInfoText.set(""+str(self.config))
                self.filterInfoText.set(""+str(self.config.filter))

                break
        
        self.refreshImage()
    
    def refreshImage(self):
        if not self.config.spherical:
            self.renderImg = ImageTk.PhotoImage(self.polarImg)
        else:
            self.renderImg = ImageTk.PhotoImage(self.sphircalImg)
        if self.image.master != None:
            self.image.configure(image=self.renderImg)
    def refresh(self):

        resultsList = []

        ls = os.listdir(RESULT_P)

        for i in range(len(ls)):
            if '22' in ls[i]:
                resultsList.append(ls[i])

        resultsList.sort()

        self.listbox.delete(0,self.listbox.size()-1)

        for filename in resultsList:
            self.listbox.insert(0, filename)

        newTimeStamp = self.listbox.get(0)
        self.setInfo(newTimeStamp)


    def resultListInit(self):


        #get all file names inside esults path
        resultsList = os.listdir(RESULT_P)
        
        resultsFrame = LabelFrame(self.root,text="Results List")
        # sort by time 
        resultsList.sort()

        scrollbar = Scrollbar(resultsFrame)
        scrollbar.pack( side = LEFT, fill = Y )

        self.listbox = Listbox(resultsFrame, yscrollcommand = scrollbar.set,width=52)
        
        for filename in resultsList:
            self.listbox.insert(0, filename)

        self.listbox.bind("<<ListboxSelect>>", self.selectRes)
        self.listbox.pack( side = LEFT, fill = BOTH )

        scrollbar.config( command = self.listbox.yview )

        resultsFrame.grid(column=0,row=0)

    def btnInit(self):

        buttonFrame = LabelFrame(self.root)

        showBtn = Button(buttonFrame,text="Plot Results",command=lambda:self.showRes())
        showBtn.pack(side=RIGHT)
        makeCMD = self.getSystemName()

        compileBtn = Button(buttonFrame,text="Compile",command=lambda:self.compileClick(makeCMD))
        compileBtn.pack(side =LEFT)
        
        runBtn = Button(buttonFrame,text="Run Simulation",command=lambda:self.runClick(makeCMD))
        runBtn.pack(side=LEFT)

        buttonFrame.grid(column=0,row=1)

    def saveComand(self,saveButton:Button,itrs:Text,revelutions:Text,itrationMode:Text,deltaPsiMode:Text,timestep:Text,type:Text,log_p:Text):
        
        self.config.itrations = (int)(itrs.get("1.0","end-1c"))                     
        self.config.revolutions = (float)(revelutions.get("1.0","end-1c"))
        if "T" in itrationMode.get("1.0","end-1c") or "t" in itrationMode.get("1.0","end-1c"):       
            self.config.iterationMode = 1
        else:
            self.config.iterationMode = 0
        if "T" in deltaPsiMode.get("1.0","end-1c") or "t" in deltaPsiMode.get("1.0","end-1c"):       
            self.config.deltaPsiMode = 1
        else:
            self.config.deltaPsiMode = 0

        self.config.t_inrev = (float)(timestep.get("1.0","end-1c"))
        self.config.type = (int)(type.get("1.0","end-1c"))
        self.config.log_p = (int)(log_p.get("1.0","end-1c"))
        
        self.config.writeToFile()
        saveButton['state'] = DISABLED

    def enableBtn(self,btn:Button):
        btn['state'] = NORMAL

    def initFillter(self):
        
        filterFrame = LabelFrame(self.root,text="Filter")
        filterTextBox = Text(filterFrame,width= 80,height=20)
        filterTextBox.pack()
        filterFile = open(self.config.fillterPath,"r")
        filterLines = filterFile.readlines()

        for line in filterLines:
            filterTextBox.insert(END,line)
        filterFile.close()

        saveBtn = Button(filterFrame,state=DISABLED,text="Save",width=78,command = lambda : self.saveBtnFilter(saveBtn,filterTextBox.get('1.0',END)))
        saveBtn.pack(side=BOTTOM)    
        filterTextBox.bind("<Key>",lambda event:  self.enableBtn(saveBtn))

        filterFrame.grid(column=0,row=2,columnspan=2,rowspan=2)

    def saveBtnFilter(self,btn:Button,text:str):

        filterFile = open(self.config.fillterPath,"w")
        filterFile.write(text)
        btn['state'] = DISABLED
        filterFile.close()

    def configUiInit(self):

        configFrame = LabelFrame(self.root,text = "Config",width = 30,height=30)
        rowI = IntVar()
        rowI.set(0)
        # itrations
        itrsTextB = Text(configFrame,height=1,width=15)
        itrsTextB.insert(END,(str)(self.config.itrations))
        itrsTextB.grid(column=1,row=rowI.get())
        itrLabel = Label(configFrame,text="Iterations:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)
        # ---------
        #revelutions
        revTextBox= Text(configFrame,height=1,width=15)
        revTextBox.insert(END,(str)(self.config.revolutions))
        revTextBox.grid(column=1,row=rowI.get())
        revLabel = Label(configFrame,text="Revolutions:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #-----------
        #Revelutions mode
        revModeText = Text(configFrame,height=1,width=15)
        revModeText.insert(END,(str)(self.config.iterationMode))
        revModeText.grid(column=1,row=rowI.get())
        revLabel = Label(configFrame,text="Iteration mode:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #----------------
        #DeltaPsi mode
        delModeText = Text(configFrame,height=1,width=15)
        delModeText.insert(END,(str)(self.config.deltaPsiMode))
        delModeText.grid(column=1,row=rowI.get())
        deltaLabel = Label(configFrame,text="DeltaPsi mode:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #----------------
        #T interval
        timeText = Text(configFrame,height=1,width=15)
        timeText.insert(END,(str)(self.config.t_inrev))
        timeText.grid(column=1,row=rowI.get())
        timeLabel = Label(configFrame,text="Time step:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #----------
        #simulation type 
        typeText = Text(configFrame,height=1,width=15)
        typeText.insert(END,(str)(self.config.type))
        typeText.grid(column=1,row=rowI.get())
        typeLabel = Label(configFrame,text = "Type:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #---------------
        #log period
        logText = Text(configFrame,height=1,width=15)
        logText.insert(END,(str)(self.config.log_p))
        logText.grid(column=1,row=rowI.get())
        logLabel = Label(configFrame,text = "Log perod:").grid(column=0,row=rowI.get())
        rowI.set(rowI.get()+1)

        #----------
        saveButton = Button(configFrame,text="Save",width=15,pady=10,state=DISABLED,command=lambda:self.saveComand(saveButton,itrsTextB,revTextBox,revModeText,delModeText,timeText,typeText,logText))
        saveButton.grid(column=0,row=rowI.get(),columnspan=2,rowspan=2)
        
        itrsTextB.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        revModeText.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        delModeText.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        revTextBox.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        timeText.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        typeText.bind("<Key>",lambda event:  self.enableBtn(saveButton))
        logText.bind("<Key>",lambda event:  self.enableBtn(saveButton))

        configFrame.grid(column=1,row=0,rowspan=2)

    def getSystemName(self):

        OS_name = platform.system()
        makeCMD = ""
        
        if(OS_name == "Windows"):
            makeCMD = "mingw32-make"
        else:
            makeCMD = "make"

        return makeCMD

    def compileClick(self,makeCMD:str):
        
        compile = sp.Popen([makeCMD])
        o,e = compile.communicate()

    def infoBoxInit(self):
        infoFrame = LabelFrame(self.root,text = "Seleceted info")
        
        filterFrame = LabelFrame(infoFrame,text = "Filter")
        configFrame = LabelFrame(infoFrame,text = "Config")
        self.image = Label(infoFrame,image=self.renderImg)
        self.image.grid(column=0,row=0)
        configStr = Label(configFrame,textvariable=self.configInfoText,wraplength=300).grid(column=0,row=0)
        filterStr = Label(filterFrame,textvariable=self.filterInfoText,wraplength=300).grid(column=0,row=1)
        configFrame.grid(column=0,row=1,)
        filterFrame.grid(column=0,row=2,columnspan=2,sticky='s')
        infoFrame.grid(column=2,row=0,rowspan=4,sticky='n') 

    def runClick(self,makeCMD:str):

        prog = sp.Popen([makeCMD,'run'])
        o,e = prog.communicate()
        self.refresh()
        
    def initUi(self):

        self.resultListInit()

        self.btnInit()

        self.configUiInit()

        self.infoBoxInit()

        self.initFillter()


        
