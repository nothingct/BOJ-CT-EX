n,m=map(int,input().split())
check= [[False]*m for _ in range(n)]
a = [list(map(int,input().split())) for _ in range(n)]

dx=[-1,0,1,0]
dy=[0,-1,0,1]
ans = 0 

def solve(cnt,sum,x,y):
  global ans
  if cnt==4:
    if ans < sum : ans = sum
    return
  if x < 0 or x >= n or y <0 or y>=m: return
  if check[x][y] : return
  check[x][y] = True
  for i in range(4):
    solve(cnt+1,sum+a[x][y],x+dx[i],y+dy[i])
  check[x][y]=False

for i in range(n):
  for j in range(m):
    solve(0,0,i,j)
    #ㅗ,ㅜ 테트로미노 
    if j+2 <m :
      base = a[i][j]+a[i][j+1]+a[i][j+2]
      if i-1 >= 0:
        sum = base+a[i-1][j+1]
        if sum>ans : ans = sum
      if i+1 < n : 
        sum =base+a[i+1][j+1]
        if sum>ans : ans = sum 
    if i+2 <n : 
      base= a[i][j]+a[i+1][j]+a[i+2][j]
      if j-1 >= 0 : 
        sum=base+a[i+1][j-1]
        if sum > ans : ans = sum
      if j+1 < m : 
        sum = base+a[i+1][j+1]
        if sum > ans : ans = sum
print(ans)
  
      
  