n = int(input())
papers = []

for _ in range(n):
    row = list(map(int,input().rsplit()))
    papers.append(row)
