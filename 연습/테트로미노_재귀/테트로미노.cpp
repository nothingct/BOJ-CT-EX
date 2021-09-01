#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int a[500][500];
bool check[500][500];
int n,m;

int dx[]= {-1,0,1,0};
int dy[]= {0,-1,0,1};
int ans;

void solve(int cnt, int sum,int x, int y){
  if(cnt==4){
    ans=max(ans,sum);
    return;
  }
  if(x < 0 || x>= n || y<0||y>=m) return;
  if(check[x][y]) return;
  check[x][y]=true;
  for(int i=0; i<4; i++){
    int nx = x+dx[i];
    int ny = y+dy[i];
    solve(cnt+1,sum+a[x][y],nx,ny);
  }
  check[x][y]=false; //dfs 는 방문여부를 초기화하지 X=> Brute Force 와 DFS의 차이점
}

int main(){
  cin>>n>>m;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      cin>>a[i][j];
    }
  }
 //ㅗ , ㅜ, ㅏ, ㅓ 테트로미노 + 그 외 테트로미노 처리하기 
 for(int i=0; i<n; i++){
   for(int j=0; j<m; j++){
     solve(0,0,i,j);
     //ㅗ,ㅜ 테트로미노 
     if(j+2<m){
       int base= a[i][j]+a[i][j+1]+a[i][j+2];
       //ㅗ 테트로미노
       if(i-1 >= 0 ) {
         int sum = base+a[i-1][j+1];
         ans=max(ans,sum);
       }
       //ㅜ 테트로미노
       if(i+1<n){
         int sum = base+a[i+1][j+1];
         ans=max(ans,sum);
       }
     }
     //ㅓ,ㅏ 테트로미노 
     if(i+2<n){
       int base = a[i][j]+a[i+1][j]+a[i+2][j];
       //ㅓ 테트로미노 
       if(j-1 >= 0 ) {
         int sum = base+a[i+1][j-1];
         ans=max(ans,sum);
       }
       //ㅏ 테트로미노 
       if(j+1 < m) {
         int sum = base+a[i+1][j+1];
         ans=max(ans,sum);
       }
     }
   }
 }
 cout<<ans<<'\n';
 return 0; 
}