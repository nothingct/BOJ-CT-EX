def solve(a,index,target):
  if index==len(a) : return target
  if a[index] > target: return target
  return solve(a,index+1,target+a[index])
n=int(input())
a=list(map(int,input().split()))
a.sort()
print(solve(a,0,1))