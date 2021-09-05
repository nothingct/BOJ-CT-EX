def solve(arr,index,lotto):
  if len(lotto)==6:
      print(' '.join(map(str,lotto)))
      return
  if index==len(arr): return 
  solve(arr,index+1,lotto+[arr[index]])
  solve(arr,index+1,lotto)
while True: 
  n, *arr=list(map(int,input().split()))
  if n== 0 : break
  solve(arr,0,[])
  print()
      