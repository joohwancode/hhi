from collections import deque  # Queue를 사용하기 위한 collection library 사

n, m, k, x = map(int, input().split())
distance = [0] * (n + 1)
graph = [[] for _ in range(n + 1)]
for i in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    # graph[b].append(a)
    ##노드를 연결시켰다.
    ##탐색을 시작해야홤 왜 bfs 끝까지 가지않고 중간에 멈춰야 한다.
distance = [0] * (n + 1)
visited = [False] * (n + 1)


def bfs(start):
    queue = deque([start])
    answer = []

    visited[start] = True
    distance[start] = 0

    while queue:
        now = queue.popleft()

        for i in graph[now]:
            if not (visited[i]):
                visited[i] = True
                queue.append(i)
                distance[i] = distance[now] + 1  ##한칸 더 이동한다.
                if distance[i] == k:
                    answer.append(i)

    if len(answer) == 0:
        print(-1)
    else:
        answer.sort()
        for i in answer:
            print(i, end=" ")


bfs(x)
