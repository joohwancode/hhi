T = int(input()) ###dfs 

for i in range(T) :
    n = int(input())
    dp = [0]*(n+1)##range는 +1 0 부터 시작하기 때문에 
    if n == 1 :
        print(1)
    elif n == 2 :
        print(2)
    elif n == 3 :
        print(4)
    else :
        dp[1] = 1
        dp[2] = 2
        dp[3] = 4
        for j in range(4,n+1) :
            dp[j] = dp[j-1] + dp[j-2] + dp[j-3]
        print(dp[n])

