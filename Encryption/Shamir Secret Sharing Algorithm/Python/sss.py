# Yashasvi Goel
# 14/9/20
# SSS algorithm

import random

def f(x,coeff):
    ans=0
    power=1
    for i in coeff:
        ans+=i*power
        power=power*x
#        print(i)

    return ans
secret=input("Input your secret\n")
e=""#Temporary variable to store the secret key
k=2 #Number of min keys
n=4 #number of total keys
for i in secret: #converting ascii to decimal
    e+=str(ord(i))

S=int(e)
P=random.randint(S,S*15) #generating a random number greater than S 
print(P)
a=[]    #list of coeff for f(x)
a.append(P) #a0
for i in range(1,k):
    a.append(random.randint(1,P)) #populating the coeff 

D=[]
for i in range(1,n+1):
    D.append([i, f(i,a)%P])
print(D)


#++++++++DECODE+++++++++++++++++


p1=input("Input your secret1\n")
p2=int(input("Input your secret2\n"))
p1=int(p1)
#(x-p1)/(p2-p1)+(x-p2)/(p1-p2)
print(1+((p2-p1)/(p1-p2))%P) #this is the equation that'd give us our answers;

