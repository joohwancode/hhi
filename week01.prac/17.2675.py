## 문자열 sd 입력받는다.
## 각문자를  R번 반복한다.
## 새문자열 P를 만든다.
##첫번째 문자로 R 두번째 문자로 R번 세번째 문자로 R번 
## 이중 반복문 같음 
"""n=int(input())"""
'''for _ in range(n):
    a=int(input())##a횟수만든 의 인덱스값에 있는 숫자들이 반복하여 출력된다. 
    b=str(input())
    for repeat_b in range(b):'''
    
    
n=int(input())
for _ in range(n):
    cnt,wrd = input().split()
    for x in wrd:
        print(x*int(cnt),end='')##end = '' 옆으로 붙임 
    print()##줄넘김 
        