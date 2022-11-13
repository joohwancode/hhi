

###a=int(input())
###
###class FixedStack:
###    ###고정길이 스택 클래스 
###    class Empty(Exception):
###        pass ###비어있는 픽스드 스택에 팝 또는 피크할대 내보내는 예외 처리
###    class Full(Exception):
###        pass###가득찬 픽스드 스택에 푸시할때 내보내는 예외처리
###    
###    def __init__(self,capacity:int=256)->None:
###        ###스택초기화
###        self.stk=[None]*capacity ## 스택 본체
###        self.capacity=capacity ## 스택의 크기 
###        self.ptr=0 ##스택의 포인터
###    def size(self)->int:##스택에 쌓여있는 데이터 갯수를 반환하자 
###        return self.ptr 
###    def empty(self)->bool:
###        return self.ptr<=0 ##스택이 비어있는지 판단 
###    def is_full(self)-> bool:
###        return self.ptr >= self.capacity
###    def push(self, value: Any)-> None: ##스택에 밸류를 넣는다. 
###        if self.is_full(): ##스택이 가득찬 경우 
###            raise FixedStack.Full ##예외처리 발생 
###        self.stk[self.ptr]=value
###        self.ptr+=1
###    
###    def pop(self)->Any: ##스택에서 데이터를 팝 (꼭대기 데이터를 꺼냄)
###        if self.empty(): ##스택이 비어있는 경우 
###            raise FixedStack.Empty ##예외처리 발생 
###        self.ptr-=1
###        return self.stk[self.ptr]
###    def top(self)->Any:
###        if self.empty():
###            raise FixedStack.Empty
###        return self.stk[self.ptr-1]
###
###    

import sys
input=sys.stdin.readline

n=int(input()) ##정수로 바꿔주질 않음 파이썬은 입력하면 기본적으로 문자임 

stack=[]
for i in range(n):
    command = input().split()
    
    ###push X: 정수 X를 스택에 넣는 연산이다.
    
    if command[0]=='push': ###첫번째 값이 push 일때
        stack.append(command[1]) ##command의 2번째 값을 넣어라 
    elif command[0]=='pop':
        if len(stack)== 0:
            print(-1)
        else:
            print(stack.pop())
    elif command[0]=='size':
        print(len(stack))
    elif command[0]=='empty':
        if len(stack)==0:
            print(1)
        else:
            print(0)
    elif command[0]=='top':
        if len(stack)==0:
            print(-1)
        else:
            print(stack[-1])
