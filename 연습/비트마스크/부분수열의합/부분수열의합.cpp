#include <iostream>
#include <vector>

using namespace std;

const int MAX =100000;
bool check[MAX*20+10];

int main(){
  int n ; 
  cin>>n;
  vector<int> a(n);
  for(int i=0; i<n; i++) cin>>a[i];

  for(int i=0; i< (1<<n); i++){
    int sum=0;
    for(int j=0; j<n; j++){
      if(i & (1<<j) ){
        sum+=a[j];
      }
    }
    check[sum]=true;
  }

  for(int i=1;; i++){
    if(check[i]==false){
      cout<<i<<'\n';
      break;
    }
  }
  return 0;
}