import sys
input=sys.stdin.readline
from collections import deque
n=int(input())

queue=deque([])
for i in range(n):
    command = input().split()
    
    if command[0]=='push':
        queue.append(command[1])
    elif command[0]=='pop':
        if not queue:
            print(-1)
        else:
            print(queue.popleft())
    elif command[0]=='size':
        print(len(queue))
    elif command[0]=='empty':
        if not queue:
            print(1)
        else:
            print(0)
    elif command[0]=='front':
        if len(queue)==0:
            print(-1)
        else:
            print(queue[0])
    elif command[0]=='back':
        if not queue:
            print(-1)
        else:
            print(queue[-1])       
