import sys
from itertools import permutations

n = int(input())
a = list(map(int, input().split()))

cases = list(permutations(a))
### permutation을 사용할때 뒤에 몇개의 원소를 사용할지 정해주지 않았으므로 들어오는 리스트를 모두 permutation 해준다 .

print(cases)

###2번 반복한다 .
answer =0 
for cases in cases:
    check=0
    for i in range(n-1):
        check +=abs(cases[i]-cases[i+1])
    answer= max(answer,check) ### 답과 check 중에 가장 큰 최대값  
    
print(a)