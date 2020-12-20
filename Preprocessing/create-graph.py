'''
@author Carlos Eduardo Atencio Torres
@email catencio@unsa.edu.pe
@date 2020

This file tries to create a Trie
'''

import datetime
import re
import sys

from os import listdir
from os.path import isfile, join

nodeCounter = 0
class Node:
    def __init__(self):
        self.isEnd = False
        self.children = {}
        global nodeCounter
        nodeCounter+=1
        self.label = nodeCounter

    def insert(self, word, idx):
        if idx == len(word):
            self.isEnd = True
            return

        if word[idx] not in self.children.keys():
            self.children[word[idx]] = Node()
        self.children[word[idx]].insert(word, idx+1)


class Tree:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        self.root.insert(word,0)

    def getTotalSize(self):
        return self.getTotalSizeRecursively(self.root)
    
    def getTotalSizeRecursively(self,node):
        sumy = 0
        for child in node.children.keys():
            sumy += self.getTotalSizeRecursively(node.children[child])
        return sumy + sys.getsizeof(node) + sys.getsizeof(node.children)

    def printGraph(self, toPath, errorPath):
        try:
            with open(toPath, 'w', errors='ignore') as f:
                global nodeCounter
                f.write("TOTAl: {:} nodes\n".format(nodeCounter))
                queue = []
                queue.append(self.root)
                while len(queue) > 0:
                    node = queue.pop(0)
                    for child in node.children.keys():
                        f.write( "{:} {:} {:}\n".format(node.label, node.children[child].label, child ))
                        queue.append( node.children[child] )
        except:
            with open(errorPath,'w', errors='ignore') as f:
                errorPath.write("unknow error")
                    

#TEST
'''
tree = Tree()
tree.insert("carlos")
tree.insert("carla")
print("Nodes created:", nodeCounter)
tree.printGraph()
'''

#MAIN
fromPath = "Processed"
logPath = "create-graph.log"
errorPath = "create-graph.error.log"

splitRule = '[\\s!"#$%&\'()*+,-./:;<=>?@\[\\\\\]^_`\{|\}~°]+'

onlyfiles = [f for f in listdir(fromPath) if isfile(join(fromPath,f))]

#variables
count = 0
wordCounter = 0
tree = Tree()
#print("Tree size:", tree.getTotalSize() )

print("Starting ", datetime.datetime.now() )

for filename in onlyfiles:
    count+=1
    if count%10000 == 0:
        print("Procesando:", count,"files, ", nodeCounter, "nodes and", wordCounter,"words" )
        print("\t",datetime.datetime.now() )
    if count%1000000 ==0:
        break #solo hasta los 1 millon primeros archivos    
    try:
        with open(fromPath+"/"+filename, 'r', errors='ignore') as f:
            lines = f.readlines()
            for line in lines:
                words = re.split( splitRule, line)
                for word in words:
                    wordCounter += 1
                    tree.insert(word)                
    except:
        print("ERROR",filename)
        
print("Nodes created:", nodeCounter)
#print("Tree size:", tree.getTotalSize() )
tree.printGraph(logPath,errorPath)
