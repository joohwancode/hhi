n=int(input())
for _ in range(n):
    s=input()
    a=0
    b=0
    for i in (s):
        if i == "O":
            b+=1
        else:
            b=0
        a+=b
    print(a)
    
    ### 이렇게 풀수 도 있음