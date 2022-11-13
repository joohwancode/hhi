import sys
input=sys.stdin.readline


##2가지 방법이 있다. 
a=int(input()) 
# ##무조건 (로 시작한다 .]
# for i in range(a):
#     b=input()
#     s=list(b) ## 리스트로 담아줘야 한다. 
#     sum=0
#     for i in s:
#         if i== '(':
#             sum+=1
#         elif i== ')':
#             sum-=1
#         if sum <0:
#             print('NO')
#             break ##반복문 나간다 .
#     if sum >0:
#         print('NO')    
#     elif sum ==0:
#         print('YES')

### 스택으로 푸는 법 
for i in range(a):
    b = input()
    s = list(b)
    k = False
    stack = []
    for i in s:
        if i == '(':
            stack.append(i)
        elif i == ')': 
            if len(stack) > 0:
                stack.pop()
            else:
                k = True
                break
    if k == True and len(stack) >0: print('NO')
    else : print('YES')