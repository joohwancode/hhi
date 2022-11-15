import sys

input = sys.stdin.readline


def dfs(start):
    visited[start] = True

    ###해당 시작점을 기준으로 계속해서 dfs로 그래프를 탐색한다
    for i in graph[start]:
        ##만약 방문하지 않았다면
        if not visited[i]:
            dfs(i)


N, M = map(int, input().split())
graph = [[] for _ in range(N + 1)]  ## 빈 그래프로 초기화 해준다.

for i in range(M):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

visited = [False] * (1 + N)  ##False로 초기화 시켜줌 true로 바꾸기 위해서
#####왜 1+N으로 하는가 중요하다 . (0번째가 빈리스트 이기 때문에
###왜 ? 0번째를 빈 리스트로 만들어 주고 시작한다.
count = 0
# 1~N번 노드를 각각돌면서
for i in range(1, N + 1):
    if not visited[i]:  # 만약 i번째 노드를 방문하지 않았다면
        if not graph[i]:  # 만약 해당 정점이 연결된 그래프가 없다면
            count += 1  # 개수를 + 1
            visited[i] = True  # 방문 처리
        else:  # 연결된 그래프가 있다면
            dfs(i)  # dfs탐색을 돈다.
            count += 1  # 개수를 +1

print(count)
