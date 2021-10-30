#include <iostream>
#include <string>
#include <vector>

// right , left , down, up : 0,1,2,3
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
// 10 을 넘어가는 기울임 횟수 : 의미 없음.
const int LIMIT = 10;
// 10진법수 k를 4진법 수로 변환하여 반환(배열의 형태)
vector<int> convert10To4(int k){
  vector<int> a(LIMIT);
  for(int i=LIMIT-1; i>-1; i--){
    a[i] = k & 3;  
    k >>= 2;
  }
  return a;
}

bool isValidDirections(vector<int>& dir){
  int l = dir.size();
  for(int i=0; i<l-1; i++){
    // 이전 방향 과 반대 방향은 의미 없다. 
    if(dir[i]==0 && dir[i+1]==1) return false;
    if(dir[i]==1 && dir[i+1]==0) return false;
    if(dir[i]==2 && dir[i+1]==3) return false;
    if(dir[i]==3 && dir[i+1]==2) return false;
    // 이전 방향 과 같은 방향은 의미 없다. 
    if(dir[i]==dir[i+1]) return false;
  }
  return true;
}
pair<bool,bool> simulate(vector<string>&a, int k, int& x,int& y){
  // 현재 구슬위치 x,y 가 빈칸?=> 구슬이 보드에 없음=>이미 구멍에 빠짐 을 의미 
  if(a[x][y]=='.') return make_pair(false,false);

  int n = a.size();
  int m = a[0].size();

  bool moved = false;

  while(true){
    int nx = x+dx[k];
    int ny = y+dy[k];

    if(nx<0 || nx>=n || ny<0 || ny>= m ) return make_pair(moved,false);
    if(a[nx][ny]=='#') return make_pair(moved,false);
    else if(a[nx][ny]=='R'||a[nx][ny]=='B') return make_pair(moved, false);
    else if(a[nx][ny]=='.'){
      swap(a[nx][ny], a[x][y]);
      x= nx; y=ny; moved= true;
    }else if(a[nx][ny]=='O'){
      a[x][y]= '.';
      moved=true;
      return make_pair(moved,true)
    }
  }
  return make_pair(false,false)
}
int check(vector<string> a, vector<int> & dir ){
  int n = a.size();
  int m = a[0].size();

  int hx,hy,bx,by,rx,ry;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(a[i][j]=='O'){
        hx =i;
        hy =j;
      }else if(a[i][j] == 'R'){
        rx=i;
        ry=j;
      }else if(a[i][j]=='B'){
        bx=i;
        by=j;
      }
    }
    int cnt=0;
    // k는 dir[0]~dir[9]까지 10번 
    for(int k: dir){
      cnt+=1;
      bool holeR=false; holeB=false;
      while(true){
        auto r= simulate(a,k,rx,ry);
        auto b= simulate(a,k,bx,by);
        if(r.first==false && b.first==false) break;

        if(r.second) holeR = true;
        if(b.second) holeB = true;
      }
      if (holeB) return -1;
      if (holeR) return cnt;
    }
    return -1;
  } 
}

int main(){
  int n,m; 
  cin>>n>>m;
  vector<string> a(n); 
  for(int i=0; i<n; i++){
    cin>>a[i];
  }

  int ans = -1; 
  // brute force
  for(int k = 0; k < 1 <<(LIMIT*2); k++ ){
    vector<int> dir = convert10To4(k);
    if(! isValidDirections(dir)) continue;
    int cnt = check(a,dir);
    if (cnt == -1 ) continue; 
    if (ans==-1 || ans > cnt ) ans = cnt;
  }
  cout<<ans<<'\n';
}