from typing import List
import matplotlib.pyplot as plt
import subprocess as sp

def get_R_Theta(currLine):# extracts the value of "r" and "theta" from string

    r_index = currLine.find("r= ")+3
    th_index = currLine.find("th= ")+4
    
    r_val = currLine[r_index:]
    th_val = currLine[th_index:]
    
    r = (float)(r_val[:r_val.find("\t")])
    th = (float)(th_val[:th_val.find("\t")])

    return (tuple)([th,r])

def getInitVals():

    config = open("config/config.ini","r")
    configLines = config.readlines()
    itrs = (int)(configLines[0][configLines[0].find("=")+1:])
    file_num = (int)(configLines[6][configLines[6].find("=")+1:])
    log_p = (int)(configLines[7][configLines[7].find("=")+1:])
    result_path =configLines[8][configLines[8].find("\"")+1:-2]
    itrs = (int)(itrs/log_p)
    return tuple([itrs,file_num,result_path])

def main():
    
    prog = sp.Popen(['make','make clean','./electronSimulation'])
    o,e = prog.communicate()
    # print(o.decode("ascii"))

    colors = ['b.','g.','r.','c.','m.','y.','k.','w.']# ploting colors

    # plt.figure()
    # plt.axes(projection = 'polar')

    
    itrs , file_num , result_path = getInitVals()
    
    for i in range(1,file_num+1): 
        plt.figure()
        plt.axes(projection = 'polar')
        for j in range(i):
            
            curr_file_p = result_path%(i,j)
            result_f = open(curr_file_p,"r")
        
            for k in range(itrs):
                currLine = result_f.readline()
                curr_values = get_R_Theta(currLine)

                if k < itrs-1:
                    plt.polar(curr_values[0],curr_values[1],colors[j%8])
                else:#add lable to the final point of a simulation
                    plt.polar(curr_values[0],curr_values[1],colors[j%8],label = ('l = '+(str)(i-j)+'$\hbar$'))
            result_f.close()

        plt.legend(frameon=True, loc='lower center', ncol=3)
    plt.show(block = False)
    plt.waitforbuttonpress(0)
    plt.close('all')

if(__name__ == "__main__"):
    main()
