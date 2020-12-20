import datetime

from os import listdir
from os.path import isfile, join


def getWord(line,idx):
    ini,fin = idx,idx
    while ini>-1 and line[ini].isalpha():
        ini-=1
    while fin<len(line) and line[fin].isalpha():
        fin+=1
    return line[ini+1:fin]


fromPath = "Processed"
logPath = "capturar-diccionario-letras.log"
errorPath = "capturar-diccionario-letras.error.log"

print("Creating the dictionary of letters starting at ")
print(datetime.datetime.now() )



onlyfiles = [f for f in listdir(fromPath) if isfile(join(fromPath,f))]

words = {}

count = 0
for filename in onlyfiles:
    count+=1
    if count%10000 == 0:
        print("Procesando:", count,"files")
        print(datetime.datetime.now() )
    
    try:
        with open(fromPath+"/"+filename, 'r', errors='ignore') as f:
            lines = f.readlines()
            for line in lines:
                for i in range(len(line)):
                    if line[i].isalpha():
                        if line[i] not in words:
                            words[line[i]] = getWord(line, i)
    except:
        with open(errorPath,'a') as err:
            err.write( "ERROR {:}\n".format(filename))

with open(logPath,'w') as log:
    for key in words.keys():
        log.write( "{:} [{:}] => {:}\n".format(key, ord(key), words[key]) )