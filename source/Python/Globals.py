import numpy as np 

RESULT_P = "./results/"

font = {
        'color':  'black',
        'weight': 'normal',
        'size': 30,
        }

titleFont = {
        'color':  'black',
        'weight': 'normal',
        'size': 18,
        }

LINE_WIDTH = 5

TICKS_FONT_SIZE = 20

MARKER_SIZE = 10

C =29979245800

e =4.8032068E-10

h_bar =1.05457266E-27

def convertToSpherical(results):

        X_list = results[2]*np.cos(results[0])*np.sin(results[1])
        Y_list = results[2]*np.sin(results[0])*np.sin(results[1])
        Z_list = results[2]*np.cos(results[1])
        return np.vstack((X_list,Y_list,Z_list))

def polarToCartzaian(results):

        X_list = results[1]*np.cos(results[0])
        Y_list = results[1]*np.sin(results[0])

        return np.vstack((X_list,Y_list))

def calc_accrute_deltaPHi(k:int ,reletive:bool = True):

        if not reletive:
                return 0

        arg1 = h_bar*C*k
        arg1 = (e*e)/arg1
        arg1*=arg1
        arg1 = 1-arg1
        arg1 = np.sqrt(arg1)

        return (((2*np.pi)/arg1)-2*np.pi)

def getlimits(N):

        a = N**4
        b = N**2

        c = (a-b)**0.5

        a = N**2 + c
        b = N**2 - c

        return (-a*0.52977210903 , a * 0.52977210903)

def getLineType(k):
        
        lineType = ['-.','-','--',':']
        return lineType[k%len(lineType)]
        
def getMarkerType(k):
        
        lineType = ['X','o','s','^']
        return lineType[k%len(lineType)]
  