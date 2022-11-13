T = int(input())
#몇번의 반복횟수를 할 것인지를 정한다. 
for n in range(T):
    a,b=map(int,input().split())
    print(a+b)
# a와 b 값을 입력 한다. 
# 공백을 스플릿으로 구분해 준다. 
# 그리고  리스트를 정수로 변환해줄때 쓰는 map 함수를 쓴다.