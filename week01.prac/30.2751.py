import sys 
arr=[]

n=int(input())

for i in range(n):
    arr.append(int(sys.stdin.readline().rstrip()))
def Quicksort(left,right,arr):
    ##left가 클경우 종료한다 .
    if(left>=right):
        return
    i=left 
    j=right
    pivot=arr[(left+right)//2]
    
    while(i<=j):
        ##i가 작은 거라면 통과 한다.
        while (arr[i]<pivot):
            i+=1
        while (arr[j]>pivot):
            j-=1
        if(i<=j):
            #교환한다. 
            arr[i],arr[j]=arr[j],arr[i]
            i+=1
            j-=1
    Quicksort(left,j,arr)
    Quicksort(i,right,arr)
    
Quicksort(0,n-1,arr)
for i in range(n):
    print(arr[i])

    