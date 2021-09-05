def go(a,index,sum,s):
  if index==len(a):
    if sum==s: return 1
    else: return 0
  return go(a,index+1,sum+a[index],s)+go(a,index+1,sum,s)
n,s=map(int,input().split())
a=list(map(int,input().split()))
ans = go(a,0,0,s)
if s==0 : ans-=1
print(ans)