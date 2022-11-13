from itertools import combinations

N, S = map(int, input().split())
sequence = list(map(int, input().split()))
cnt=0


for i in range(1,N+1):
    combi = list(combinations(sequence,i))
    for j in combi:### combi 리스트 안에 있는 것이기 때문에 그 리스트에다가 돌려야 한다. 
        #if sum(combi)==S:
        if sum(j)==S:
            cnt+=1
            
print(cnt)