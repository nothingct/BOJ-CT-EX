#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minAns = 1000000001;
int maxAns = -1000000001;
int n;
int a[12];
void cal(int cnt, int add, int sub, int mul, int div, int res){
  if(cnt==n){
    minAns= min(minAns,res);
    maxAns=max(maxAns,res);
    return;
  }
  if(add > 0) cal(cnt+1,add-1,sub,mul,div,res+a[cnt]);
  if(sub > 0) cal(cnt+1,add,sub-1,mul,div,res-a[cnt]);
  if(mul > 0) cal(cnt+1,add,sub,mul-1,div,res*a[cnt]);
  if(div > 0) cal(cnt+1,add,sub,mul,div-1,res/a[cnt]);
}

int main(){
  cin>>n;
  for(int i=0; i<n; i++) cin>>a[i];
  int add,sub,mul,div; 
  cin>>add>>sub>>mul>>div;
  cal(1,add,sub,mul,div,a[0]);
  cout<<maxAns<<'\n';
  cout<<minAns<<'\n';

  return 0;
}