'''N 정렬할 개수 
A(수 저장 및 리스트 설정 하기 )
for i 0 ~ N-1 만큼 반복하기 
    for j  N-1-i k만큼 반복 :
        현재 리스트의 값보다 1칸 오른쪽 리스트의 값이 더 작으면 두수 바꾸기 
A 출력하기'''

##버블 정렬로 풀기 
N=int(input())
A=[0]*N ##초기화작업 

for i in range(N):
    A[i]=int(input())
    for j in (N-1-j):
            print(A[j])

        