n=int(input())
a = list(map(int,input().split()))
check = [False]*(n*100000+10)
for i in range(1<<n):
  s=0
  for j in range(n):
    if( i & (1<<j) ) : 
      s+= a[j]
  check[s]= True
i=1
while True: 
  if check[i]== False: break
  i+=1
print(i)