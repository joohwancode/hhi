import sys

n,c =list(map(int,input().split()))

array=[]

for _ in range(n):
    array.append(int(sys.stdin.readline()))
array=sorted(array)

##roq 스타트 값을 지정해 준다.


start = 0
end = array[-1]-array[0] + 1

while start+1 < end : ##
     ##중간 갭 이 뭔지를 정해줘야 한다 .
    mid = (start+end)//2
    value= array[0]##공유기 초기 설치 위치 
    count=1
    ###현재의 mid(공유기 사이 거리)를 이용한 공유기 설치 
    for i in range(1,len(array)):##앞에서 부터 설정한다.  1은 뭘까 ??>> 공유기 사이가 거리가 최소 1이기때문에 ????? 
        if array[i]>=value+mid:
        ## i번째 숫자 0번째 정렬과 mid를 더한 것 보다 클때 
            ####공유기 설치 위치 변경 
            value = array[i]###vaule는 arra[i]이며
            ###개수 증가하기 
            count+=1
    if count >= c:##c개 이상의 공유기를 설치할 수 있는 경우 
        #스타트를 옮겨준다 
        start = mid
  
    else:
        end=mid
        
print(start)