def cal(a,res,idx,add,sub,mul,div):
  if idx==len(a): return (res,res)
  restuls =[] 
  if add > 0:
    restuls.append(cal(a, res+a[idx], idx+1, add-1, sub, mul, div))
  if sub > 0:
    restuls.append(cal(a, res-a[idx], idx+1, add, sub-1, mul, div))
  if mul > 0:
    restuls.append(cal(a, res*a[idx], idx+1, add, sub, mul-1, div))
  if div > 0 : 
    if res >= 0:
      restuls.append(cal(a, res//a[idx], idx+1, add, sub, mul, div-1))
    else:
      restuls.append(cal(a, -(-res//a[idx]), idx+1, add, sub, mul, div-1))
  ans = (max([p[0] for p in restuls]), min([p[1] for p in restuls]))
  return ans
n=int(input())
a=list(map(int,input().split()))
add,sub,mul,div = map(int,input().split())
ans=cal(a,a[0],1,add,sub,mul,div)
print(ans[0])
print(ans[1])
