import sys
n=int(sys.stdin.readline())
num_list=[0]*10001

for _ in range(n):
    num_list[int(sys.stdin.readline())] +=1
    #### 리스트에 각 요소마다 0을 할당해놓고 입력값을 받을때마다 그 입력값고 ㅏ같은 인덱스에 +1씩해준다. 
for _ in range(10001):
    if num_list[i]!=0: ##인덱스가 0인아니면 
        for j in range(num_list):
            print(i)