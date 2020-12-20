'''
@author Carlos Eduardo Atencio Torres
@email catencio@unsa.edu.pe
@date 2020


This rutine:
- reads all files from a folder and transform all the extra characters to ascii, for example '¢' is transformed to 'c' or ñ is transformed to 'n'
- Eliminates punctuations. 
- Transform to lowercase
- The files are stored but using an index '0001.txt', '0002.txt' and adds a file with the mapped names.
'''

import datetime

from os import listdir
from os.path import isfile, join

from math import log

fromPath = "../Processed"
toPath = "../Ascii"
transformPath = "transform-dictionary.txt"
logPath = "transform-to-ascii.log"
errorPath = "transform-to-ascii.error.log"
listNamesPath = "list-of-names.txt"

print("Transforming to ascii ")
print(datetime.datetime.now() )

print("Loading transform dictionary")
transform = {}
with open(transformPath,'r') as f:
    for line in f.readlines():
        a,b,c = line.rstrip().split('\t')
        transform[int(a)] = c #b es solo para visualizar    



onlyfiles = [f for f in listdir(fromPath) if isfile(join(fromPath,f))]

mapFiles = {}
for filename in onlyfiles:
    mapFiles[filename] = str(len(mapFiles)+1)

sizeOfFormat = int(log(len(mapFiles))//log(10)) + 1

for filename in mapFiles:
    mapFiles[filename] = mapFiles[filename].zfill(sizeOfFormat)

count = 0
for filename in onlyfiles:
    count+=1
    if count%10000 == 0:
        print("Procesando:", count,"files")
        print(datetime.datetime.now() )
        
    try:
        with open(fromPath+"/"+filename, 'r', errors='ignore') as f:
            with open(toPath+"/"+mapFiles[filename]+".txt", 'w' ) as g:
                for line in f.readlines():
                    line = list(line)
                    for i in range(len(line)):
                        cod = ord(line[i])
                        if cod > 128:
                            if cod in transform:
                                line[i] = transform[cod]
                            else:
                                line[i] = ''
                        else:
                            if not line[i].isalpha():
                                line[i] = ' '
                    g.write(''.join(line).lower()+"\n")
                    
    except:
        with open(errorPath,'a') as err:
            err.write( "ERROR {:}\n".format(filename))

try:
    with open(listNamesPath, 'w') as f:
        for filename, number in mapFiles.items():
            f.write(number + " " + filename + "\n")
except:
    with open(errorPath,'a') as err:
        err.write( "ERROR trying to save the map of list" )

print("Done")
print(datetime.datetime.now() )
