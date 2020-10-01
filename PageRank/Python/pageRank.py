
from collections import defaultdict
import numpy as np
import logging

logging.basicConfig(level=logging.DEBUG)

class PageRank:

    def __init__(self,teleprtationProb=0.8,maxIter=40):
        self.adjList = defaultdict(list)
        self.outDegree = {}
        self.inDegree = {}
        self.N = 0  # number of nodes
        self.beta = teleprtationProb # (1-beta) is the teleprtation Probability
        self.iter = maxIter

    def updateOutDegree(self,x):
        # update OutDegree
        if x not in self.outDegree:
            self.outDegree[x] = 1
        else:
            self.outDegree[x] += 1

    def updateInDegree(self,y):
        # update InDegree
        if y not in self.inDegree:
            self.inDegree[y] = 1
        else:
            self.inDegree[y] += 1

    def readFile(self, filename):
        logging.debug("Inside ReadFile: FILENAME->{}\n".format(filename) )
        
        file = open(filename)
        for line in file.readlines():
            x, y = map( int,line.split() )

            # handling multiple edges
            if y not in self.adjList[x]:
                # we are dealing with directed graph
                self.adjList[x].append(y)   # add Edge

                self.updateInDegree(y)
                self.updateOutDegree(x)
                self.N = max(self.N,x,y)
        # print(self.outDegree)

    def createMatrices(self):
        M = [ [ 0 for i in range(self.N)] for j in range(self.N) ]
        for i in range(self.N):
            for j in range(self.N):
                if j+1 in self.adjList[i+1]:
                    M[i][j] = 1/self.outDegree[i+1]
        
        
        
        M = np.array(M)
        r = np.ones((self.N,1))
        return r,M
    
    def powerIteration(self):
        A,M = self.createMatrices()

        # r0 = A * 1/n
        r = np.dot(1/self.N,A)

        # start powerIterations
        # r = A*(1-beta)/n + beta*M*r
        # here 1-beta is the teleportation probality or dampening Factor
        for i in range( 1,self.iter ):
            t1 = np.dot((1-self.beta)/self.N,A)
            t2 = np.dot(self.beta,M)
            t2 = np.dot(t2,r)
            r = t1 + t2

        # r will now contain the saturated PageRanks of all the Nodes
        return r
    

        

            
            
            
