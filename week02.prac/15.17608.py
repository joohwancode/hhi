import sys
input=sys.stdin.readline


n=int(input())
stack=[int(input()) for _ in range(n)]

top=stack.pop() ##w제일 높은 막대기 
cnt=1

for i in range(1,n):
    now=stack.pop() ##지금 현재 막대기의 위치
    ##현재 막대기가 제일 높은 막대기 보다 높으면
    if now >top:
        cnt+=1
        top=now ##제일 높은 막대기를 현재 막대기로 초기화 한다. 
print(cnt)
