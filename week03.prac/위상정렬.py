from collections import deque

##노드의 개수와 간선의 개수를 입력받기
v, e = map(int, input().split())

##모든 노드에 대한 진입차수는 0으로 초기화
indegree = [0] * (v + 1)
##각 노드에 연결된 간선 정보를 담기 위한 연결 리스트 초기화
graph = [[] for i in range(v + 1)]

# 방향 그래프의 모든 간선 정보를 입력받기
for i in range(e):
    a, b = map(int, input().split())
    graph[a].append(b)  ## 정점 a에서 b로 연결 가능하다 .
    ##진입차수를 1증가 시킨다. ##연결이 되어 있기 때무에
    indegree[b] += 1


def topology_sort():
    result = []  ##알고리즘 수행결과를 담을 리스ㅌ이다.
    q = deque()  ##큐 기능을 위한 deque 라이브러리 사용한다.

    for i in range(1, v + 1):
        if indegree[i] == 0:  ## 진입 차수가 0이면
            q.append(i)
    # 큐가 빌때까지 반복한다.
    while q:  ## 참인 동안 계속 반복한다.
        ##큐에서 원소 꺼내기
        now = q.popleft()
        result.append(now)

        for i in graph[now]:
            indegree[i] -= 1  ##진입차수 1개를 줄여준다.
            ##새롭게 진입차수가 0인되는 노드를 큐에 삽입
            if indegree[i] == 0:
                q.append(i)
    for i in result:
        print(i, end=" ")


topology_sort()
