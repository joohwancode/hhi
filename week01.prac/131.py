#### 2번재 방법 이진 탐색 법  리스트가 있을때 중간값을 잡아 잘라주고 앞인지 뒤인지 정해서 또 중간 값 잡아서 나눠주고 그런형태이다.

from typing import Any,Sequence
def bin_search(a:Sequence,key:Any):

    pl=0 ##검색 범위의 맨 앞 원소의 인덱스이다 .
    pr=len(a)-1 ###검색 범위의 맨 마지막 인덱스이다. 
    while True:
        pc =(pl+pr)//2
        if a[pc]==key:
            return key
        elif a[pc]<key:
            pl=pc+1 ### 오른쪽으로 한칸 이동합니다.
        else:
            pr=pc-1
        if pl>pr : ##엇갈려도 안나오면 break 해야한다. 
            break 
    return -1 ## 걍 이렇게 정한다. 
if __name__ == '__main__':
            num = int(input('원소수를 입력하세요'))
            x=[None]*num
            
            
            print("배열 데이터를 오름차순으로 입력하세요")
            
            x[0] =int(input('x[0]:'))
            
            for i in range(1,num):
                while True:
                    x[i] = int(input(f'x{[i]}:'))
                    if x[i] >= x[i-1]:
                        break #### 오름 차순이 되도록 바로 직전에 입력한 원솟값보다 큰 값을 입력하다.
            
            ky =int(input('검색할 값을 입력해주세요 '))
            idx=bin_search(x,ky) 
            
            if idx ==-1:
                print("검색값을 가지는 원소가 존재하지 않습니다.") 
            else:
                print(f"검색값 {x[idx]}")        