n=int(input())
ans=[]

for i in range(n):
    
    ###입력과 동시에 append를 해준다.
    ans.append(input())
    
##중복 문자를 제거해주고 다시 리스트 형태로 바꾸어 준다.     
temp=set(ans)
ans=list(temp)


ans.soet()
ans.sort(key=len)
##알파벳 길이대로 정렬해준다. 
for i in ans:
    print(i)