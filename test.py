

'''array=[7,6,9,0,1,3,1,6,2,4,8]

for i in range(1,len(array)):
    for j in range(i,0,-1):## 인덱스 i 부터 1까지 1씩 감소하며 반복하는 문법
        if array[j]<array[j-1]:##한칸씩 왼쪽으로 이동
            array[j],array[j-1]=array[j-1],array[j]##대입하는 것 
        else:
            break
print(array)'''

#선택정렬 알고리즘 
'''array=[7,6,9,0,1,3,1,6,2,4,8]
for i in range(len(array)):
    min_index=i 
    for j in range(i+1,len(array)):
        if array[min_index]>array[j]:
            min_index=j
    array[i],array[min_index]=array[min_index],array[i]
print(array)'''
## 퀵 정렬 알고리즘 
'''array=[7,6,9,0,1,3,1,6,2,4,8]

def quick_sort(array,start,end):
    if start >= end:
        return
    pivot =start ## 피봇은 첫번째 원소이다. 
    left =start+1
    right= end
    while(left<=right):
        while(left <= end and array[left]<=array[pivot]):
            left+=1
        while(right>start and array[right]>=array[pivot]):
            right-=1
        if(left>right):##엇갈렸다면 작은 데이터와 피벗을 교체 
            array[right],array[pivot]=array[pivot],array[right]
        else:#엇갈리지 않았다면 작은 데이터와 큰데이터를 교체한다. 
            array[left],array[right]=array[right],array[left]
     ##분할 이후에 왼쪽부분과 오른쪽에서 각각 정렬 수행한다.         
    quick_sort(array,start,right-1)
    quick_sort(array,right+1,end)
    
quick_sort(array,0,len(array)-1) ##7까지 (start /stop /step)
print(array)'''


## 파이썬의 장점을 살린 퀵 정렬 소스 코드 

array=[5,7,9,0,3,1,6,2,4,8]

def quick_sort(array):
    if len (array)<=1:
        return array
    pivot=array[0]
    tail=array[1:]
    
    left_side = [x for x in tail if x<=pivot]
    right_side= [x for x in tail if x>pivot]
    
    
    return quick_sort(left_side)+[pivot]+quick_sort(right_side)
print(quick_sort(array))


##계수 정렬 코드

## 모든 원소의 값이 0보다 크거나 같다고 가정한다. 
array=[7,5,9,0,3,1,6,2,9,1,4,8,0,5,2]
# 모든 범위를 포함하는 리스트 선언 ( 모든 값은 0으로 초기화)

count=[0]*(max(array)+1) # 각 데이터에 해당하는 인덱스의 값 증가 

for i in range(len(array)):
    count[array[i]]+=1

for i in range(len(count)):## 리스트에 기록된 정렬 정보 확인
    for j in range(count[i]):
        print(i,end='')