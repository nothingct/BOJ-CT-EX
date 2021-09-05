#include <iostream>
using namespace std;
bool chess[15][15];
int n ; 
bool check_col[15];
bool check_lu2rd[40];
bool check_ru2ld[40];
//row,col 에 퀸을 놓을 수 있는지 확인.
bool check(int row, int col){
  //열 확인 : 이미 해당 열에 퀸이 존재하면 false  
  if(check_col[col]) return false;
  //좌상단->우하단 대각선 확인 
  if(check_lu2rd[row+col]) return false;
  //우상단->좌하단 대각선 확인 
  if(check_ru2ld[n+row-col]) return false;
  //이외는 놓을 수 있음 
  return true;
}
//0~row-1행은 이미 퀸을 놓았고, row번째 행에 , 퀸을 놓아서 N-Queen 을 만들 수 있는 경우의 수 .
int cal(int row){
  //정답을 찾은 경우: 마지막 n-1번쨰 행까지 퀸들을 모두 배치한 경우.
  if(row==n){
    //1가지 경우를 찾음 
    return 1;                                                                                   
  }
  int cnt = 0; 
  for(int col = 0; col <n; col++){
    //row,col에 퀸을 놓을 수 있다면,
    if(check(row,col)){
      //해당 위치에 퀸을 배치했다는 정보 on
      check_col[col]= true;
      check_lu2rd[row+col]=true;
      check_ru2ld[n+row-col] = true;
      chess[row][col]=true;
      //다음 탐색 
      cnt+= cal(row+1);
      //bruete-force-> 퀸 배치 정보 초기화
      check_col[col]= false;
      check_lu2rd[row+col]=false;
      check_ru2ld[n+row-col] = false;
      chess[row][col]=false;
    }
  }
  return cnt;
}

int main(){
  cin>>n; 
  cout<<cal(0)<<'\n';
  return 0;
}