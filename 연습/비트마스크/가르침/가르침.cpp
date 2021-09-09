#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int radWords(int mask, vector<int>& words){
  int cnt=0;
  for(int word: words){
    if( (word & ((1<<26)-1-mask)) == 0 ) cnt+=1;
  }
  return cnt;
}

int solve(int index, int k, int learned, vector<int>& words){
  if(k<0) return 0;
  if(index == 26) return radWords(learned,words);
  int ans =0;
  int temp=0;
  //a,n,t,i,c가 아니고 배우는 경우
  if(index != 'a'-'a'&& index!='n'-'a' && index!='t'-'a'&&index!='i'-'a'&&index!='c'-'a'){
    temp=solve(index+1,k-1,learned|(1<<index), words);
    if(ans < temp ) ans = temp;
  }
  //a,n,t,i,c 이든 아니든 안배우는경우(어차피 배워놔서 상관이 X)
  temp= solve(index+1,k,learned,words);
  if(ans <temp ) ans = temp;
  return ans;
}

int main(){
  int n,k;
  cin>>n>>k;
  vector<int> words(n); // n개의 단어들의 비트마스크 정보를 저장.
  //a,n,t,i,c 5개는 무조건 배워야 한다.  
  if(k < 5){
    cout<<0<<'\n';
    return 0;
  }
  // 모든 알파벳을 배웠으면 주어진 모든 단어를 읽을 수 있다.
  if(k == 26){
    cout<<n<<'\n';
    return 0;
  }
  //a,n,t,i,c는 배웠으므로 bitmask 에 기록.
  int learnBitMask = 0;
  learnBitMask|=(1<<('a'-'a'));
  learnBitMask|=(1<<('n'-'a'));
  learnBitMask|=(1<<('t'-'a'));
  learnBitMask|=(1<<('i'-'a'));
  learnBitMask|=(1<<('c'-'a'));
  //접두사 anta 와 접미사 tica는 어차피 읽을 수 있으므로 s에서 잘라낸다.
  for(int i=0; i<n; i++){
    string s; 
    cin>>s;
    s.erase(s.begin(),s.begin()+4);
    s.erase(s.end()-4,s.end());
    //anta---tica 사이에 읽어야 하는 알파벳 정보를 비트마스크로 기록한다.
    for (char c : s){
      words[i] |= (1<<(c-'a'));
    }
  }
  cout<<solve(0,k-5,learnBitMask,words)<<'\n';
  return 0;
}