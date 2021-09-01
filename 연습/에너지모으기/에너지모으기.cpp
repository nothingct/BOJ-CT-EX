#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int> &a ){
  int n = a.size();
  if(n==2) return 0;
  int ans = 0 ; 
  for(int i=1; i<n-1; i++){
    int e = a[i-1]*a[i+1];
    vector<int> b(a);
    b.erase(b.begin()+i);
    e+=solve(b);
    ans = max(ans,e);
  }
  return ans;
}

int main(){
  int n; 
  cin>>n;
  vector<int> a(n); 
  for(int i=0; i<n; i++) cin>>a[i];
  cout<<solve(a)<<'\n';
}