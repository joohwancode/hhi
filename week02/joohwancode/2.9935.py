word=input()
bomb=input()
stack=[]

for i in word:
    stack.append(i)
    if stack[-1]==bomb[-1]:
        if ''.join(stack[-len(bomb):])==bomb:
            del stack[-len(bomb):]
            
if stack:
    print(''.join(stack))
else:
    print("FRULA")