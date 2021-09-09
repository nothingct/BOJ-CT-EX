def readWords(mask,words):
  cnt= 0
  for word in words :
    if (word & (1<<26)-1-mask)==0: cnt+=1
  return cnt
def solve(index,k, learned, words):
  if k < 0 : return 0 
  if index==26: return readWords(learned,words)
  ans = 0
  temp =0
  #a,n,t,i,c아니어서 배우는 경우.
  if index not in [ord('a')-ord('a') , ord('n')-ord('a'),ord('t')-ord('a'),ord('i')-ord('a'),ord('c')-ord('a')]:
    temp = solve(index+1, k-1, learned | (1 << index), words)
    ans=max(ans,temp)
  #a,n,t,i,c는 이미 배워서 배울 필요 없고, a,n,t,i,c아닌데 그냥 안배우는경우
  temp = solve(index+1,k, learned,words)
  ans = max(ans,temp)
  return ans
n,k=map(int,input().split())
if k < 5:
  print(0)
  exit(0)
if k== 26:
  print(n)
  exit(0)
#a,n,t,i,c 는 필수로 배운다
learnedMask = (1<<(ord('a')-ord('a')))
learnedMask |= (1 << (ord('n')-ord('a')))
learnedMask |= (1 << (ord('t')-ord('a')))
learnedMask |= (1 << (ord('i')-ord('a')))
learnedMask |= (1 << (ord('c')-ord('a')))
#a,n,t,i,c를 배웠으니 배울수 있는 알파벳은 k-5개이다
k-=5
#단어의 비트마스크를 저장할 words 배열을 만든다
words = [0]*n
#단어들에서 접두사 "anta" 와 접미사 "tica"는 이제 어차피 읽을 수 있으니 단어 에서 잘라낸다. 
for i in range(n):
  s=input()
  s=s[4:-4]
  for c in s:
    words[i] |= (1<<(ord(c)-ord('a')))
print(solve(0,k,learnedMask,words))
