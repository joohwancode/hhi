import sys

input = sys.stdin.readline
from collections import deque


def dfs(v):
    visited[v] = 1

    # 재귀로 계속 파고드는 것임
    for k in graph[v]:
        if not visited[k]:

            dfs(k)


N = int(input())
M = int(input())

graph = [[] for _ in range(N + 1)]
for i in range(M):  ## M은 간선의 수랑 같은 것이다.
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

visited = [0] * (N + 1)

dfs(1)
print(sum(visited) - 1)
### 함수는
