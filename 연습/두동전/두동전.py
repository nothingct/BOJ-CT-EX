dx = [-1,0,1,0]
dy = [0,-1,0,1]
def solve(cnt,x1,y1,x2,y2):
  if cnt == 11 : return -1
  drop1=False
  drop2=False
  if x1<0 or x1>=n or y1<0 or y1>=m: drop1=True
  if x2<0 or x2>=n or y2<0 or y2>=m: drop2=True
  if drop1 and drop2 : return -1
  if drop1 or drop2 : return cnt
  
  ans = -1 
  for i in range(4) : 
    nx1,ny1 =x1+dx[i],y1+dy[i]
    nx2,ny2 =x2+dx[i],y2+dy[i]
    if 0<=nx1<n and 0<=ny1<m and board[nx1][ny1] == '#': 
      nx1,ny1=x1,y1
    if 0 <= nx2 < n and 0 <= ny2 < m and board[nx2][ny2] == '#':
      nx2, ny2 = x2, y2
    ret = solve(cnt+1,nx1,ny1,nx2,ny2)
    if ret==-1: continue
    if ans==-1 or ans > ret : ans = ret
  return ans

n,m = map(int ,input().split())
x1=y1=x2=y2=-1
board =[list(input()) for _ in range(n)]

for i in range(n): 
  for j in range(m):
    if board[i][j]=='o':
      if x1==-1:
        x1,y1=i,j
      else: 
        x2,y2=i,j
      board[i][j]='.'
print(solve(0,x1,y1,x2,y2))