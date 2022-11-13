import heapq
import sys
heap = []
for _ in range(int(input())):
    n = int(sys.stdin.readline())
    if n!=0:
        heapq.heappush(heap,(-n,n))
    else:
        if heap:
            print(heapq.heappop(heap)[1]) ##최댓값출력한디ㅏ.
        else:
            print(0)
