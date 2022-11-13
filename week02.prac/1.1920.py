import sys
input = sys.stdin.readline


#####
#####
####### *****이진 탐색을 하기 위해서는 반드시 자료를 미리 정렬해야 한다 .******8
#####def binary_search(a,x):
#####    start=0
#####    end = len(a)-1
#####    
#####    
#####    while start <= end :
#####        #3
#####        mid = (start+end)//2 
#####        if x == a[mid]:
#####            return 1 ##리스트 a의 중간값과  x가 같다면         ####두번째  리스트 기준으로 설정해야 한다. 돌면서 가운데 기준 왼쪽에서 같은것을 발견 하면 cnt 1 개 증가시키기  
#####        elif x > a[mid]:
#####            start=mid+1 ###반으로 나눠서 왼쪽으로 쭉쭉 이동해야 하니까 start-> <-end 
#####        else:
#####            end= mid-1 #에서 미드로 쭉쭉이동한다. 
#####            
#####    return 0 
#####
#####
#####n=int(input())
#####a=list(map(int,input().split())) ## map 함수는 리스트의 요소를 지정되 함수로 처리해준다 .여러개의 데이터를 한번에 다른 형태로 변화하기 위해 사용한다 .
#####a.sort()
#####m=int(input())
#####x=list(map(int,input().split())) ## 이진 탐색을 해야하는 리스트
#####
#####for i in range(m):
#####    print(binary_search(a,x[i]))   ### 리스트 a와 리스트 x의 인덱스를 비교합니다.  
#####    
### 재귀로 푸는것도 생각해보자 
def binary_search(a,x,start,end):
    if start >end:
        return False 
    mid = (start+end)//2 
    if a[mid] == x:
        return True
    elif a[mid]> x:
        return binary_search(a,x,start,mid-1)
    else:
        return binary_search(a,x,mid+1,end)
    
n= int(input())
a=list(map(int,input().split()))
m=int(input())
m_l=a=list(map(int,input().split()))
a =sorted(a)

for m in m_l:
    if binary_search(a,m,0,n-1):
        print(1)
    else:
        print(0)    
        