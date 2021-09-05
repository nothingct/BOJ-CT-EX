#include <iostream>
#include <cstring> //memset
#include <tuple>   //tie

using namespace std;

int a[10][10]; //주어진 스도미노쿠 
bool c[10][10]; //row[i][j] : i번쨰 row 에 숫자 j 가 이미 있는지
bool c2[10][10];//col[i][j] : i번째 col 에 숫자 j 가 이미 있는지
bool c3[10][10];//square[i][j] : i번째 square 에 숫자 j 가 이미 있는지
bool domino[10][10];//domino[i][j] : 숫자 i와j로 이루어진 도미노가 이미 쓰였는지.
int n=9; //스도미노쿠의 크기 : 9 

int dx[]={1,0}; // 도미노 | 방향
int dy[]={0,1};// 도미노 - 방향 

int boxing(int x, int y){ // 주어진 x,y 좌표가 몇번째 square에 속하는지 boxing하는 함수
  return (x/3)*3+(y/3);
}

pair<int,int> convert(string s){ // 입력에 주어지는 도미노(Ex:B4) 를 x와 y 좌표로 변환해서 반환.
  return make_pair(s[0]-'A',s[1]-'1');
}

bool isPossible(int x, int y,int num){ //좌표x,y 에 숫자 num을 놓을 수 있는지, 없는지 판단.
  return c[x][num] == false && c2[y][num]==false && c3[boxing(x,y)][num]==false;
}

void setValue(int x, int y, int num,bool val){//좌표 x,y에 num을 놓거나(true) 빼는(false) 함수
  c[x][num]= val; 
  c2[y][num]=val;
  c3[boxing(x,y)][num] = val;
}
//좌표 x,y 과 스도미노쿠 판 안 에 있는지 검사
bool check_range(int x, int y){
  return 0<=x && x<n && 0<=y && y<n; 
}
//z번째 칸에 대한 도미노를 채우는 함수. 
bool solve(int z){
  //z칸은 0~80 이므로 , 81에 왔음== 완료조건:정답을 찾음.
    if(z==81){
    for(int i=0; i<n;i++){
      for(int j=0; j<n; j++){
        cout<<a[i][j];
      }
      cout<<'\n';
    }
    return true;
  }
  //현재 z칸을 (x,y)로 좌표변환.
  int x = z/n;
  int y = z%n;
  //이미 채워져 있는 경우는 다음 칸을 호출한다. 
  if(a[x][y]!=0){
    return solve(z+1);
  }else{
    //채워져 있지 않은 경우, 도미노의 방향 - , | 과 , 넣을 수 있는 도미노를 확인한다. 
    for(int d=0; d<2; d++){
      int nx = x+dx[d]; 
      int ny = y+dy[d];
      //도미노의 2번째 칸이 범위에 속하는지 검사. 
      if(!check_range(nx,ny)) continue;
      //해당 nx,ny칸이 채워 져있는지 확인한다. 
      if(a[nx][ny] != 0 ) continue;
      //도미노를 넣을 수 있다면, 어떤 도미노를 넣을 수 있는지 확인한다. 
      for(int i=1; i<=9; i++){
        for(int j=1; j<=9; j++){
          //도미노 숫자가 같을 순 없으므로 pass
          if(i==j ) continue;
          //이미 쓴 도미노는 안됨
          if(domino[i][j] ) continue;
          //(x,y) , (nx,ny)에 해당 도미노를 넣을 수 있는지 검사.
          if(isPossible(x,y,i)&&isPossible(nx,ny,j)){
            //놓을 수 있다면 놓았다고 값을 설정 
            setValue(x,y,i,true);
            setValue(nx,ny,j,true);
            domino[i][j] = domino[j][i] = true;
            a[x][y] = i; 
            a[nx][ny]= j;
            //놓았으면 다음 칸 확인하러 간다.
            if(solve(z+1)) return true;
            //다시 돌아와서 해당 칸에 대한 모든 탐색을 맞췄으면 다시 초기화
            setValue(x,y,i,false);
            setValue(nx,ny,j,false);
            domino[i][j] = domino[j][i] = false;
            a[x][y] = 0; 
            a[nx][ny]= 0;
          }
        }
      }
    }
  }
  //모든 도미노중 어떤 도미노도 채울 수 없는 경우 : 해당 z칸을 채울 수 없음을 의미 
  return false;
}

int main(){
  int tc=1;
  while(true){
    //tc형식-> 데이터 초기화.
    memset(c,false,sizeof(c));
    memset(c2,false,sizeof(c2));
    memset(c3,false,sizeof(c3));
    memset(domino,false,sizeof(domino));
    memset(a,0,sizeof(a));
    int m;
    cin>>m;
    if(m==0) break;
    //m개의 도미노 를 입력받는다.
    for(int i=0;i <m; i++){
      int d1,d2;
      string s1,s2;
      cin>>d1>>s1>>d2>>s2;
      int x1,y1,x2,y2;
      tie(x1,y1) = convert(s1);
      tie(x2,y2) = convert(s2);
      a[x1][y1]=d1;
      a[x2][y2]=d2;
      domino[d1][d2]=domino[d2][d1]=true;
      setValue(x1,y1,d1,true);
      setValue(x2,y2,d2,true);
    }
    for(int i=1; i<=9; i++){
      string s; 
      cin>>s;
      int x,y;
      tie(x,y) = convert(s);
      a[x][y] = i; 
      setValue(x,y,i,true);
    }
    cout<<"Puzzle "<<tc<<'\n';
    solve(0);
    tc+=1;
  }
  return 0;
}

