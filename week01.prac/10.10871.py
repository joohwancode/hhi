n,x= map(int,input().split())
num= list(map(int,input().split()))
for i in range(n):# 12345
    if num[i]<x:
        print(num[i],end=" ")
# dlfeks 10과 5를 입력하면 그것 
#10 5 를 만약에 입력하면 5678910 이 도출되어야 한다. 
# 이것보다 작은 것들을 한번에 출력하여야 한다
#c의 숫자중에 5보다 작은 것들을 출려한다. 
# 튜플 개념을 알아야 한다.튜플은 파이썬의 리스트와 비슷합니다. 

#
# 한칸씩 띄어주면서 출력한다!end=" "
