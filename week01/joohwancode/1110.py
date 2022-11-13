N=int(input())
num=N
cnt=0

while True:
  a= num//10
  b= num %10
  c= (a+b)%10
  num=(b*10)+c ## 새로운 num값을 찾아야 한다. 
  cnt+=1 ## 새로운 num 값 찾으면 이동 
  if (N==num):
    break ## 입력값과 똑같은 num 값이 나오면 break

print (cnt)