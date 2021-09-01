#include <iostream>
#include <vector>
using namespace std;
vector<int> ans;
void solve(vector<int>& arr, int index, int cnt){
  if(cnt == 6 ) {
    for(int num : ans){
      cout<<num<<' ';
    }
    cout<<'\n';
    return;
  }
  int n = arr.size(); 
  if(n==index) return;

  ans.push_back(arr[index]);
  solve(arr,index+1,cnt+1);
  ans.pop_back(); //모든 과정을 끝나면 결국 ans는 빈 벡터가 되어있음이 보장됨.
  solve(arr,index+1,cnt);
}
int main(){
  while(true){
    int n; 
    cin>>n;
    if(n==0) break;

    vector<int> arr(n);
    for(int i=0; i<n ; i++){
      cin>>arr[i];
    }
    solve(arr,0,0);
    cout<<'\n';
  }
  return 0;
}