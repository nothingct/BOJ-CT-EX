#include <iostream>
using namespace std;

//i번째 row, col, 정사각형(3x3) 에 숫자 j 가 있는지 여부 
bool c2[10][10];
bool c[10][10];
bool c3[10][10];
int a[10][10];
int n=9;
int boxing(int x, int y){
  return (x/3)*3+(y/3);
}

//solve(int z) : 0~80까지의 칸중, 현재 z칸을 채우는 함수
bool solve(int z){
  //정답을 찾은 경우 : 80번까지의 모든 칸을 채운 경우
  if(z==81){
    for(int i=0; i<n;i++){
      for(int j=0; j<n; j++){
        cout<<a[i][j]<<' ';
      }
      cout<<'\n';
    }
    return true;
  }
  //현재 z칸을 (x,y)의 좌표로 변환한다.
  int x = z/n;
  int y = z%n;
  //이미 채워져 있는 경우는 다음 칸을 호출한다. 
  if(a[x][y]!=0){
    return solve(z+1);
  }else{
    //채워져 있지 않은 경우: 1부터 9 중, (x,y) 에 넣을 수 있는 숫자인지 확인하고 채운후 다음 칸을 호출한다. 
    for(int num=1; num<=9; num++){
      if(c[x][num]==0 &&c2[y][num]==0 && c3[boxing(x,y)][num]==0){
        c[x][num]=c2[y][num]=c3[boxing(x,y)][num]=true;
        a[x][y]= num;
        if(solve(z+1)) return true;
        a[x][y]=0;
        c[x][num]=c2[y][num]=c3[boxing(x,y)][num]=false;
      }
    }
  }
  //1~9중 어떤 수도 채울 수 없을 경우 : 해당 z칸을 채울 수 없음을 의미 : false 반환
  return false;
}

int main(){
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin>>a[i][j];
      if(a[i][j]!=0){
        c[i][a[i][j]]=true;
        c2[j][a[i][j]]=true;
        c3[boxing(i,j)][a[i][j]]=true;
      }
    }
  }
  solve(0);
  return 0;
}