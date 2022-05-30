
class Filter:
    
    orbitList = []

    def __init__(self,filterPath:str,sperical:bool):

        filterFile = open(filterPath,"r")
        
        filterLines = filterFile.readlines()
        orbit = [-1,-1,-1]
        for i in range(len(filterLines)):

            currLine = filterLines[i]
            
            if 'N' in currLine:
                orbit[0] =(int)(currLine[currLine.find("N")+1])
                
                if "{}" in currLine:
                
                    if sperical:
                
                        for j in range(1,orbit[0]+1):
                            orbit[1] = j

                            for k in range(j+1):
                                orbit[2] = k
                                self.orbitList.append(orbit.copy())
                    else:
                        for j in range(1,orbit[0]+1):
                            orbit[1] = j
                            self.orbitList.append(orbit.copy())


            elif 'K' in currLine:
                orbit[1] =(int)(currLine[currLine.find("K")+1])
                
                if not sperical:
                    self.orbitList.append(orbit.copy())
                
                elif "{}" in currLine  and sperical:
                
                    for j in range(orbit[1]+1):
                        orbit[2] = j
                        self.orbitList.append(orbit.copy())

            if sperical:
                
                if 'M' in currLine:    
                    orbit[2] =(int)(currLine[currLine.find("M")+1])
                    self.orbitList.append(orbit.copy())
                