import sys
input = sys.stdin.readline


a,b,v= map(int,input().split())
day= (v-b)/(a-b)+1 ## 가기전 까지 날짜를 구하고 
print(int(day))