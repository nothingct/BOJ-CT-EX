#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> cal(vector<int>& a, int res, int idx, int add, int sub, int mul,int div){
  int n = a.size(); 
  if(idx==n){
    return make_pair(res,res);
  }
  vector<pair<int,int>> results;
  if(add > 0 ) results.push_back(cal(a,res+a[idx],idx+1,add-1,sub,mul,div));
  if(sub > 0 ) results.push_back(cal(a,res-a[idx],idx+1,add,sub-1,mul,div));
  if(mul > 0 ) results.push_back(cal(a,res*a[idx],idx+1,add,sub,mul-1,div));
  if(div > 0 ) results.push_back(cal(a,res/a[idx],idx+1,add,sub,mul,div-1));

  auto ans = results[0];
  for( auto result: results){
    ans.first = max(ans.first,result.first);
    ans.second = min(ans.second,result.second);
  }
  return ans;
}

int main(){
  int n ; 
  cin>>n;
  
  vector<int> a(n);
  for(int i=0; i<n; i++) cin>>a[i];

  int add,sub,mul,div; 
  cin>>add>>sub>>mul>>div;

  auto ans = cal(a,a[0],1,add,sub,mul,div);
  cout<<ans.first<<'\n';
  cout<<ans.second<<'\n';
  return 0;

}