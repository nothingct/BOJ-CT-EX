#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int>& a, int index, int target){
  if(a[index]>target) return target;
  if(index==a.size()) return target;
  return solve(a,index+1,target+a[index]);
}

int main(){
  int n; 
  cin>>n;
  vector<int> a(n);
  for(int i=0; i<n; i++){
    cin>>a[i];
  }
  sort(a.begin(),a.end());
  cout<<solve(a,0,1)<<'\n';
}