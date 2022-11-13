import sys
input = sys.stdin.readline


N = int(input())
tree={}  ####딕셔너리 생성

for n in range(N):
    root,left,right = map(str, sys.stdin.readline().split()) ##문자열로 받는다 .
    tree[root]=[left,right]
def preorder(root): ### root 에다가 프리오더 넣기 
    if root !='.':
        print(root,end='') #루트
        preorder(tree[root][0]) ##왼쪽 ###left가 새로운 루트가 된다.
        preorder(tree[root][1]) ## 오른쪽 

def inorder(root): ### root 에다가 프리오더 넣기 
    if root !='.':
        
        inorder(tree[root][0]) #왼쪽
        print(root,end='') ##루트 
        inorder(tree[root][1])
        
def postorder(root): ### root 에다가 프리오더 넣기 
    if root !='.':
        
        postorder(tree[root][0]) #왼쪽  
        postorder(tree[root][1]) ##오른쪽 
        print(root,end='') ##루트 

preorder('A')
print()
inorder('A')
print()
postorder('A')




#{"A":("B","C")} A가 부모인 노드가 BC A의 자식이 B,C

