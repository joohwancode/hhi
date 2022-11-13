

####큐를 이용하는 방법 

n,k =map(int,input().split())

arr=[i for i in range(1,n+1)]
key=0
result=[]
while len(arr)>0:
    key=(key+(k-1))%len(arr) ###요니푸스의 개념을 알아야 함 key를 계속 뽑아서  result에 넣어준다. 
    result.append(arr.pop(key))

print('<'+', '.join(map(str, result))+'>')
