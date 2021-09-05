#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
// 중복 제거 + 순열 + 문자를 인덱스로 + 계산함수 구현
using namespace std;
//문자 => ascII 기준 256(char) 
//alpha[x] : 문자 x 가 갖는 값
int alpha[256];
//현재 입력으로 주어진 문자열 a에 대하여 ,등장한 문자들 letters 에 perm 에 의해 매겨진 값으로 a를 계산하였을 때의 합.
int calc(vector<string> &a,vector<char>& letters,vector<int>& perm){
  int m = letters.size();
  //perm 에 의해 각 문자들에게 매겨진 값을 할당.
  for(int i=0; i<m; i++){
    alpha[letters[i]]=perm[i];
  }
  //각 단어들의 총 합 : sum
  int sum=0;
  //각 단어에 대하여.
  for(string s : a){
    //해당 단어의 계산 결과 값 : now
    int now = 0;
    //각 단어의 각 문자들을, 자릿수에 맞게 계산.
    for(char x : s){
      now = now*10+alpha[x];
    }
    //해당 단어의 계산 결과 값을 총합에 더한다. 
    sum+=now;
  }
  return sum;
}

int main(){
  int n; 
  cin>>n;
  //입력으로 주어진 단어들을 저장한다.
  vector<string> a(n);
  //입력으로 주어진 단어들 안에 등장한 문자(알파벳)들을 저장한다.
  vector<char> letters;
  for(int i=0; i<n; i++){
    //각 단어를 입력받는다. 
    cin>>a[i];
    for(char x: a[i]){
      //각 단어에 포함된 문자들을 일단 모두 letters에 넣는다.
      letters.push_back(x);
    }
  }
  //문자 중복제거 를 한다. (정렬 => 삭제 순서 지켜줘야 한다. )
  sort(letters.begin(),letters.end());
  letters.erase(unique(letters.begin(),letters.end()),letters.end());
  //입력에 등장한 알파벳의 개수 를 저장
  int m=letters.size();
  vector<int> perm;
  //합의 최대를 구하는 것이기에 9에서부터 m개의 수들을 각 문자에 할당할 값으로 지정한다. 
  for(int i=9; i>9-m; i--){
    perm.push_back(i);
  }
  //next_permutation을 사용하기 위해 정렬.
  sort(perm.begin(),perm.end());
  int ans=0;
  do{
    //현재 perm에 할당된 값에 의해 문자의 값을 저장했을 때의 단어들의 계산 결과.
    int now = calc(a,letters,perm);
    if(ans <now ) ans = now;
  }while(next_permutation(perm.begin(),perm.end()));
  cout<<ans<<'\n';
  return 0;
}