n=int(input())
a=list(map(int,input().split()))
c= [False]*(n*100000+10)
def solve(index,sum):
  if index==n:
    c[sum]=True
    return
  solve(index+1,sum+a[index])
  solve(index+1,sum)
solve(0,0)
num=1
while True:
  if c[num]==False:
    print(num)
    break
  num+=1

