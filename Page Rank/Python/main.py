from pageRank import *
import numpy as np 

# input the file name of the graph
# graph will be of the form
# x y 
# x,y denotes directed edge from x to y
filename = "graph2.txt"
PR = PageRank(maxIter=40)
PR.readFile(filename)
rank = PR.powerIteration()

s = np.sum(rank)
print("Total Nodes in the Graph: {}".format(rank.shape[0]))
print("Max Rank of Node: {} is {}".format(max(rank),np.argmax(rank)+1))

perc = []
for i in range(rank.shape[0]):
    p = 100*rank[i]/s
    perc.append(p)
perc = np.array(perc)
print("Percentages of PageRank")
print("Node \t PageRank(%)")
for i in range(rank.shape[0]):
    print("{} \t {}".format(i+1,perc[i]))
