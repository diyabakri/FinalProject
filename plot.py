import numpy as np
import matplotlib.pyplot as plt
import subprocess as sp

def get_R_Theta(currLine):
    r_index = currLine.find("r= ")+3
    th_index = currLine.find("th= ")+4
    
    r_val = currLine[r_index:]
    th_val = currLine[th_index:]
    

    r = (float)(r_val[:r_val.find("\t")])
    th = (float)(th_val[:th_val.find("\t")])

    return (tuple)([th,r])

def main():

    prog = sp.Popen(['./con'],stdout = sp.PIPE , stderr = sp.PIPE)
    o,e = prog.communicate()
    print(o.decode("ascii"))

    plt.axes(projection = 'polar')
    result_f = open("result.txt","r")
    
    itrs = open("config.ini")
    itrs = itrs.readline()
    itrs = (int)(itrs[itrs.find("=")+1:])
    for i in range(itrs):
        currLine = result_f.readline()
        curr_values = get_R_Theta(currLine)
        plt.plot(curr_values[0],curr_values[1],'g.')
    plt.show()
    # plt.draw()
    # plt.pause(5)
    
if(__name__ == "__main__"):
    main()
