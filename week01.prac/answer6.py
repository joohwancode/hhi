x,y,w,h= map(int,input().split())

if x<=y and x<=h-y and x<=w-x:
    print(x) 
elif y<=x and y<=h-y and y<=w-x:
    print(y) 
elif h-y<=x and h-y<=y and h-y<=w-x:
    print(h-y)
elif w-x<=x and w-x<=y and w-x<=h-y:
    print(w-x)
