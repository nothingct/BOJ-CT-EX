def solve(a):
  n=len(a)
  if n==2 : return 0
  ans = 0
  for i in range(1,n-1):
    e = a[i-1]*a[i+1]
    b = a[:i] + a[i+1:]
    e += solve(b)
    ans =max(ans,e)
  return ans
n=int(input())
a=list(map(int,input().split()))
print(solve(a))