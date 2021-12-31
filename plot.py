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
    sub_file = (int)(configLines[7][configLines[7].find("=")+1:])
    log_p = (int)(configLines[9][configLines[9].find("=")+1:])
    result_path =configLines[10][configLines[10].find("\"")+1:-2]
    itrs = (int)(itrs/log_p)
    return tuple([itrs,file_num,sub_file,result_path])

def main():
    compile = sp.Popen(['make'])
    o,e = compile.communicate()
    prog = sp.Popen(['make','run'])
    o,e = prog.communicate()
    # print(o.decode("ascii"))
    unit = 1e-8
    colors = ['b.','g.','r.','c.','m.','y.','k.','w.']# ploting colors
    
    itrs , file_num , sub_file ,result_path = getInitVals()
    
    for i in range(1,file_num+1): 
        if(i < sub_file):
            continue
        plt.figure()
        plt.axes(projection = 'polar',)
        plt.xlabel("R($\AA$)")

        for j in range(i):
            if j < sub_file-1:
                continue
            curr_file_p = result_path%(i,j)
            result_f = open(curr_file_p,"r")
        
            for k in range(itrs):
                currLine = result_f.readline()
                # if currLine == '':
                #     plt.polar(curr_values[0],curr_values[1]/unit,colors[j%8],label = ('l = '+(str)(i-j)+'$\hbar$'))
                #     break
                curr_values = get_R_Theta(currLine)
                if k < itrs-1:
                    plt.polar(curr_values[0],curr_values[1]/unit,colors[j%8])
                else:#add lable to the final point of a simulation
                    plt.polar(curr_values[0],curr_values[1]/unit,colors[j%8],label = ('l = '+(str)(i-j)+'$\hbar$'))
            result_f.close()
            if sub_file != 0:
                break
            
        plt.legend(frameon=True, loc='lower center', ncol=3)
        
    plt.show(block = False)
    plt.waitforbuttonpress(0)
    plt.close('all')

if(__name__ == "__main__"):
    main()
