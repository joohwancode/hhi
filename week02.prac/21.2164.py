import sys
input=sys.stdin.readline

from collections import deque

N=int(input())
queue=deque([i for i in range(1,N+1)])

while(len(queue)>1):
    queue.popleft()
    queue.append(queue.popleft()) ##끝쪽에 젤 위쪽 값을 넣는다. ##반복한다.
print(queue[0]) ##첫번째 