#include <iostream>
using namespace std;

bool c[20*100000+10];
int a[20];
int n;
void solve(int index, int sum){
  if(index==n){
    c[sum]=true;
    return;
  }
  solve(index+1,sum+a[index]);
  solve(index+1,sum);
}

int main(){
  cin>>n;
  for(int i=0; i<n; i++){
    cin>>a[i];
  }
  solve(0,0);
  int num=1;
  while(true){
    if(c[num]==false){
      cout<<num<<'\n';
      break;
    }
    num++;
  }
  return 0;
}