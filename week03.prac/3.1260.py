import sys

input = sys.stdin.readline
from collections import deque


def dfs(graph, v, visited):
    visited[v] = True
    print(v, end=" ")

    # 재귀로 계속 파고드는 것임
    for k in graph[v]:
        if not visited[k]:
            dfs(graph, k, visited)


def bfs(graph, v, visited):
    ###큐구현을 위해 deque 라이브러리를 사용한다.
    queue = deque([v])
    ##현재 노드를 방문처리한다.
    visited[v] = True

    while queue:

        now = queue.popleft()
        ##탐색 순서 출력
        print(now, end=" ")
        for i in graph[now]:
            if not (visited[i]):
                queue.append(i)
                visited[i] = True


##n: 정점의 개수 m:간선의 개수 v: 탐색을 시작할 정점의 번호
if __name__ == "__main__":
    n, m, v = map(int, input().split())
    graph = [[] for _ in range(n + 1)]  ### 빈 공백을 만들어준다.
    for i in range(m):  ##이진 트리라서 이렇게 밖에 안된다.
        a, b = map(int, input().split())
        graph[a].append(b)  ###노드를 양쪽방향으로 연결시키는 것이다 .
        graph[b].append(a)
        ### 최소노드만을 선택하게 하기 위해서 정렬을 이행해 주어야 한다.
        for i in range(n + 1):
            graph[i].sort()

visited = [False] * (n + 1)
dfs(graph, v, visited)
print("")  # 한칸 띄는 것이다 .
visited = [False] * (n + 1)
bfs(graph, v, visited)
