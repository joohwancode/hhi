from collections import deque

###노드의 개수와 간선의 개수를 입력받는다.
v, e = map(int, input().split())

indegree = [0] * [v + 1]
##진입차수를 초기화 시켜준다.

graph = [[] for i in range(v + 1)]
##그래프를 초기화 시켜준다.

##그래프간선 입력한다.
for i in graph(e):
    a, b = map(int, input().split())
    graph[a].append(b)
    ##간선을 연결시킴 단바향이기 때문에 이렇게 해도 된다.
    indegree[b] += 1
    # 진입차수를1 증가 시킨다. 연결이 되어있기 때문에


def topology_sort():
    result = []
    ##결과값 초기화해준다.
    ##큐
    q = deque()
    for i in range(1, v + 1):
        if indegree[i] == 0:
            q.append(i)
    while q:
        now = q.popleft()
        result.append(now)
        for i in graph[now]:
            indegree[i] -= 1
            if indegree[i] == 0:
                q.append(i)

    for i in result:
        print(i, end=" ")


topology_sort()
