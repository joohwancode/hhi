#소수 구하기 
##소수의 개수 추출하기 
#자기자신외에는 나머지가 절대 0으로 안된다. 
## a마지막  리스트로 변경한다음에 .len()
import sys
input = sys.stdin.readline

n =int(input())
sosu= list(map(int, input().split()))
def prime(num):
    if num == 1:
        return False
    elif num ==2:
        return True
    for i in range(2,num):
        if num%i==0:
            return False 
        else:
            return True
count=0
for i in sosu:
    if prime(i):
        count+=1
print(count)  

'''소수를 판별하는 문제이다.

 

소수를 판별하는 함수(prime)을 만들어 주고, prime에 입력받은 값을 넣었을때

 

return값이 True라면 count를 증가시켜 준다.

 

count를 print 해준다.''''
            



