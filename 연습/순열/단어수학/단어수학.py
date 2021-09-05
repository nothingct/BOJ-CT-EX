def next_permutation(a):
  i=len(a)-1
  while i>=0 and a[i-1]>=a[i] : i-=1
  if i <=0 : return False
  j=len(a)-1
  while a[j] <=a[i-1]: j-=1
  a[i-1],a[j] = a[j],a[i-1]
  j=len(a)-1
  while i < j : 
    a[i],a[j]=a[j],a[i]
    i+=1
    j-=1
  return True
def calc(a,letters,perm):
  m = len(letters)
  alpha=dict()
  ans=0
  for i in range(m):
    alpha[letters[i]] = perm[i]
  for s in a:
    now = 0
    for x in s:
      now = now*10 + alpha[x]
    ans+=now
  return ans
n=int(input())
a=['']*n
letters=set()
for i in range(n):
  a[i]=input()
  letters |= set(a[i])
letters= list(letters)
m=len(letters)
perm = [ 9-i for i in range(m)]
perm.sort()
ans = 0 
while True:
  now = calc(a,letters,perm)
  if ans <now : ans = now 
  if not next_permutation(perm): break
print(ans)