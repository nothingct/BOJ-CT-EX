#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,s;
int ans; 
void go(vector<int>&a,int index,int sum){
  if(index==n) return;
  if(sum+a[index]==s) ans+=1;
  go(a,index+1,sum+a[index]);
  go(a,index+1,sum);
}

int main(){
  cin>>n>>s;
  vector<int> a(n);
  for(int i=0; i<n; i++){
    cin>>a[i];
  }
  go(a,0,0);
  cout<<ans<<'\n';
}