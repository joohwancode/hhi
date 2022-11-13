##전위 순회한 결과를 후위 순회한 결과로 바로 나오게 한다.

tree = []

while True:  # 무한 루프
    try:
        tree.append(int(input()))
    except:
        break

##루트
end = len(tree) - 1
start = 0


def post(start, end):
    if start > end:
        return
    mid = end + 1  ### 한번 더가서 또 분할
    for i in range(start + 1, end + 1):  ##루트 노드 다음 부터 시작이기 때문에
        if tree[start] < tree[i]:
            mid = i
            break
    post(start + 1, mid - 1)  ## 루트 노드
    post(mid, end)
    print(tree[start])


post(0, len(tree) - 1)
