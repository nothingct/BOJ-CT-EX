#상, 하, 좌, 우
dx=[-1,1,0,0]
dy=[0,0,-1,1]
LIMIT = 10 
#Marble 클래스
class Marble:
  def __init__(self,moved,hole,x,y):
    self.moved =moved
    self.hole=hole
    self.x=x
    self.y=y
#k를 10자리 4진법 으로 변환(원래는 해당 A[0]~A[LIMIT-1]을 뒤집어야 하지만, 어차피 방향에 대한 완전탐색이 목적이므로 굳이 뒤집지 X)
def gen(k):
  a=[0]*LIMIT
  for i in range(LIMIT):
    a[i]= (k&3)
    k>>=2
  return a
#움직임여부, 구멍에 빠짐여부)반환, simulate(보드, 방향, 구슬의 x, y좌표)
def simulate(a,k,x,y):
  #보드의 행,열 
  n=len(a)
  m=len(a[0])
  if a[x][y]=='.': return Marble(False,False,x,y)
  #움직였는지 여부 
  moved =False 
  #움직일 수 없을 때까지 계속 k방향으로 이동한다. 
  while True : 
    nx,ny=x+dx[k],y+dy[k]
    #모서리에 이동하였는지 확인(모서리는 벽이므로 사실의미가 없다.)
    if nx < 0 or nx >= n or ny < 0 or ny >= m:
      return Marble(moved, False, x, y)
    ch = a[nx][ny]
    #벽을 만났다면, 이동할 수 없음을 의미한다.
    if ch == '#':
      return Marble(moved, False, x, y)
    #벽이 아닌 자신 이외의 구슬을 만났다면, 역시 막혀서 이동할 수 없음을 의미한다.
    elif ch in 'RB':
      return Marble(moved, False, x, y)
    #빈 칸을 만났다면, 해당 방향으로 이동한다.
    elif ch == '.':
      a[x][y],a[nx][ny]=a[nx][ny],a[x][y]
      x,y=nx,ny
      moved=True
    #가장 중요함!=>구멍을 만났다면, 구멍에 들어갔으므로(이동), 원래 있던 위치의 구슬(R||B)은 빈 공간이 된다.
    elif ch == 'O':
      a[x][y]='.'
      moved=True
      return Marble(moved,True,x,y)
    
#움직인 횟수 반환)check(a: 보드판, dir: 10번 각각의 방향이 적힌 4진법bitmask)
def check(a,dir):
  n=len(a)
  m=len(a[0])
  #일단 구멍,빨간 구슬, 파란구슬의 위치를 찾는다. 
  hx,hy=0,0
  rx,ry=0,0
  bx,by=0,0
  for i in range(n):
    for j in range(m):
      if a[i][j] =='O' : hx,hy=i,j
      elif a[i][j]=='R' : rx,ry=i,j
      elif a[i][j]=='B' : bx,by=i,j
  cnt=0
  #10번에 걸친 k 
  for k in dir : 
    cnt+=1
    #빨간 구슬, 파란 구슬이 구멍에 빠졋는지 여부 기록
    holeR=holeB=False
    #두 구슬이 움직일 수 없거나 하나 또는 두 구슬 모두 구멍에 빠질때까지 이동한다.
    while True:
      r = simulate(a,k,rx,ry)
      rx,ry=r.x,r.y
      b = simulate(a,k,bx,by)
      bx,by=b.x,b.y
      #빨간 구슬, 파란 구슬 모두 움직일 수 없는 경우:다음 이동을 하러간다.
      if not r.moved and not b.moved : break
      #구슬이 구멍에 빠졋는지 하나씩 검사한다.
      if r.hole : holeR =True
      if b.hole : holeB =True
    if holeB: return -1
    if holeR: return cnt
  #10번에 걸친 이동 이후 는 - 1을 반환
  return -1

#10번의 움직임 중 의미있는 이동으로만 구성되었는지 확인한다.
#의미 없는 경우: 연속해서 같은 방향 또는 연속해서 반대방향
def isValidDirections(dir) : 
  l = len(dir)
  for i in range(l-1):
    #상하 반대 
    if dir[i]==0 and dir[i+1]==1 : return False 
    if dir[i]==1 and dir[i+1]==0 : return False
    #좌우 반대 
    if dir[i]==2 and dir[i+1]==3 : return False
    if dir[i]==3 and dir[i+1]==2 : return False
    #같은 방향 
    if dir[i]==dir[i+1] : return False 
  #10번 의 이동이 모두 의미없지 않다면, 의미있는 이동들로만 구성되어있음이 보장된다.
  return True

n,m = map(int,input().split())
original = [input() for _ in range(n)]
ans = -1 
#이동가능한 모든 10번동안의 이동조합에 관하여 탐색 시작 
for k in range(1<<(LIMIT*2)):
  #10번의 이동가능한 조합 비트마스크 k를 10개의 이동을 의미하는 배열로 반환
  dir = gen(k)
  #해당 이동조합이 의미있는 조합인지 체크
  if not isValidDirections(dir): continue
  #해당 이동조합의 횟수를 가져온다 
  #오리지널 맵은 보존, copy맵 a를 인자로 전달한다. 
  a = [list(row) for row in original]
  cur = check(a,dir)
  if cur==-1: continue
  if ans == -1 or ans > cur : ans = cur
print(ans)
