#include <iostream>
#include <vector>
#include <string>
using namespace std;
//상,하,좌,우
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
const int LIMIT = 10;
//k를 10자리 4진법 으로 변환(원래는 해당 A[0]~A[LIMIT-1]을 뒤집어야 하지만,어차피 방향에 대한 완전탐색이 목적이므로 굳이 뒤집지 X)
vector<int> gen(int k ){
  vector<int> a(LIMIT);
  for(int i=0; i<LIMIT; i++){
    a[i] = (k&3);
    k>>=2;
  }
  return a;
}
//(움직임여부,구멍에 빠짐여부)반환, simulate(보드,방향,구슬의 x,y좌표)
pair<bool,bool> simulate(vector<string>&a,int k,int& x, int& y){
  if(a[x][y]=='.') return make_pair(false,false); //현재 위치가 빈 공간=>이미 해당 구슬이 구멍에 빠졌음을 의미
  //보드의 행,열
  int n = a.size();
  int m = a[0].size();
  //움직였는지 여부
  bool moved = false;
  //움직일 수 없을 때까지 계속 K방향으로 이동한다.
  while(true){

    int nx = x+dx[k];
    int ny= y+dy[k];
    //모서리에 이동하였는지 확인(모서리는 벽이므로 사실의미가 없다. )
    if(nx <0||nx>=n||ny<0||ny>=m){
      return make_pair(moved,false);
    }
    //벽을 만났다면, 이동할 수 없음을 의미한다.
    if(a[nx][ny]=='#'){
      return make_pair(moved,false); 
    }else if(a[nx][ny]=='R'||a[nx][ny]=='B'){//벽이 아닌 자신 이외의 구슬을 만났다면, 역시 막혀서 이동할 수 없음을 의미한다. 
      return make_pair(moved,false);
    }else if(a[nx][ny]=='.'){//빈 칸을 만났다면, 해당 방향으로 이동한다. 
      swap(a[nx][ny],a[x][y]);
      x=nx;
      y=ny;
      moved= true;
    }else if(a[nx][ny]=='O'){//가장 중요함!-> 구멍을 만났다면, 구멍에 들어갔으므로(이동), 원래 있던 위치의 구슬(R||B)은 빈 공간이 된다.
      a[x][y]='.';
      moved=true;
      return make_pair(moved,true); //오직 이경우 에만 두번째 반환값인 구멍 들어감 여부를 true로 반환한다.
    }
  }
  return make_pair(false,false);
}
//(움직인 횟수 반환)check(a:보드판,dir: 10번 각각의 방향이 적힌 4진법bitmask)
int check(vector<string> a, vector<int>& dir){
  int n = a.size();
  int m= a[0].size();
  //일단 구멍, 빨간구슬, 파란구슬의 위치를 찾는다. 
  int hx,hy,rx,ry,bx,by;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(a[i][j]=='O'){
        hx=i; hy=j;
      }else if(a[i][j]=='R'){
        rx=i; ry=j;
      }else if(a[i][j]=='B'){
        bx=i; by=j;
      }
    }
  }
  int cnt = 0; 
  //10번에 걸친 k 
  for(int k : dir){
    cnt+=1;
    bool holeR=false, holeB=false; //빨간 구슬, 파란 구슬이 구멍에 빠졋는지 여부 기록
    //두 구슬이 움직일 수 없거나 하나 또는 두 구슬 모두 구멍에 빠질때까지 이동한다.
    while(true){
      auto r=simulate(a,k,rx,ry);
      auto b=simulate(a,k,bx,by);
      //빨간 구슬, 파란 구슬 모두 움직일 수 없는 경우:다음 이동을 하러간다.
      if(r.first==false && b.first==false) break;
      //구슬이 구멍에 빠졋는지 하나씩 검사한다. 
      if(r.second) holeR=true;
      if(b.second) holeB=true;
    }
    //파란 구슬이 빠진 경우(두 구슬이 모두 빠진 경우를 고려해 파란구슬이 구멍에 들어갔는지 여부를 먼저 체크)
    if(holeB) return -1;
    if(holeR) return cnt;
  }
  //10번에 걸친 이동 이후 는 -1을 반환
  return -1;
}
//10번의 움직임 중 의미있는 이동으로만 구성되었는지 확인한다.
//의미 없는 경우: 연속해서 같은 방향 또는 연속해서 반대방향 
bool isValidDirections(vector<int> & dir){
  int l = dir.size();
  for(int i=0; i+1<l; i++){
    //상하 반대
    if(dir[i]==0 && dir[i+1]==1) return false;
    if(dir[i]==1 && dir[i+1]==0) return false;
    //좌우 반대
    if(dir[i]==2 && dir[i+1]==3) return false;
    if(dir[i]==3 && dir[i+1]==2) return false;
    //같은 방향
    if(dir[i]==dir[i+1]) return false;
  }
  //10번 의 이동이 모두 의미없지 않다면, 의미있는 이동들로만 구성되어있음이 보장된다.
  return true;
}

int main(){
  int n,m;
  cin>>n>>m;
  vector<string> a(n);
  for(int i=0; i<n; i++){
    cin>>a[i];
  }
  int ans = -1; 
  //이동가능한 모든 10번동안의 이동조합 에 관하여 탐색 시작
  for(int k=0; k<(1<<(LIMIT*2)); k++){
    //10번의 이동가능한 조합 의 bitmask k를 10개의 이동을 의미하는 배열로 반환.
    vector<int> dir = gen(k);
    //의미있는 이동들로만 이루어졌는지 확인.
    if(!isValidDirections(dir)) continue;
    //해당 이동조합의 횟수를 가져온다.
    int cur = check(a,dir);
    if(cur==-1) continue;
    if(ans==-1 || ans> cur) ans = cur;
  }
  cout<<ans<<'\n';
  return 0;
}