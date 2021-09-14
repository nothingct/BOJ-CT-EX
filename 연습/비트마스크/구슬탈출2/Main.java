import java.util.*;
//pair가 없기 때문에 따로 클래스를 정의
class Marble{
  boolean moved, hole;
  int x,y;

  public Marble(boolean moved, boolean hole, int x, int y) {
    this.moved = moved;
    this.hole = hole;
    this.x = x;
    this.y = y;
  }  
}

public class Main{
  // 상,하,좌,우
  static int [] dx = {1,-1,0,0};
  static int [] dy = {0,0,1,-1};
  static final int LIMIT= 10;
  // k를 10자리 4진법 으로 변환(원래는 해당 A[0]~A[LIMIT-1]을 뒤집어야 하지만,어차피 방향에 대한 완전탐색이 목적이므로 굳이
  // 뒤집지 X)

  public static int[] gen(int k){
    int []a= new int[LIMIT];
    for(int i=0; i<LIMIT; i++){
      a[i]=(k&3);
      k>>=2;
    }
    return a;
  }
  // (움직임여부,구멍에 빠짐여부)반환, simulate(보드,방향,구슬의 x,y좌표)

  public static Marble simulate(char [][]a,int k,int x,int y){
    if(a[x][y]=='.') return new Marble(false,false,x,y);
    // 보드의 행,열

    int n = a.length;
    int m = a[0].length;
    // 움직였는지 여부
    boolean moved = false;
    // 움직일 수 없을 때까지 계속 K방향으로 이동한다.
    while(true){
      int nx = x+dx[k];
      int ny = y+dy[k];
      //모서리에 도달했나?(모서리 == 벽이므로 사실은 절대 불가능한 case)
      if(nx<0||nx>=n||ny<0||ny>=m) return new Marble(moved, false, x, y);
      //벽을 만났나 ? => 이동 X 구멍 X
      if(a[nx][ny]=='#') { return new Marble(moved, false, x, y); }
      else if(a[nx][ny]=='R'||a[nx][ny]=='B') { 
      // 현재 이동하는 구슬이 다른 구슬(R->B, B->R)을 만났나?=>이동 X 구명 X
        return new Marble(moved, false, x, y); 
      }else if(a[nx][ny]=='.'){
      // 빈 칸을 만났나?=>이동 O, 구멍 X
        char temp = a[nx][ny];
        a[nx][ny] = a[x][y];
        a[x][y]= temp;
        x=nx; y=ny; moved=true;
      }else if(a[nx][ny]=='O'){
      // (중요!) 구멍을 만났나? =>이동 O , 구멍 O
        //구슬->구멍 이동해야 하므로 현재 구슬 위치(x,y)는 빈칸이 된다.
        a[x][y]='.';
        moved=true;
        return new Marble(moved, true, x, y);
      }
    }
  }
  // (움직인 횟수 반환)check(a:보드판,dir: 10번 각각의 방향이 적힌 4진법bitmask)
  public static int check(char[][] a, int[] dir){
    int n = a.length;
    int m= a[0].length;
    // 일단 구멍, 빨간구슬, 파란구슬의 위치를 찾는다.
    int hx=0, hy=0; 
    int rx=0, ry=0;
    int bx=0, by=0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] == 'O') {
          hx = i;
          hy = j;
        } else if (a[i][j] == 'R') {
          rx = i;
          ry = j;
        } else if (a[i][j] == 'B') {
          bx = i;
          by = j;
        }
      }
    }
    int cnt = 0;
    // 10번에 걸친 방향 k 에 대하여 
    for(int k : dir){
      cnt+=1;
      // 빨간 구슬, 파란 구슬이 구멍에 빠졋는지 여부 기록
      boolean holeR = false, holeB=false;  
      // 두 구슬이 움직일 수 없거나 하나 또는 두 구슬 모두 구멍에 빠질때까지 이동한다.
      while(true){
        Marble r= simulate(a, k, rx, ry);
        rx=r.x; ry=r.y;
        Marble b = simulate(a, k, bx, by);
        bx=b.x; by=b.y;
      // 빨간 구슬, 파란 구슬 모두 움직일 수 없는 경우:다음 이동을 하러간다.
        if(r.moved==false && b.moved==false) break;
        // 구슬이 구멍에 빠졌는지 하나씩 검사한다. 
        if(r.hole) holeR=true;
        if(b.hole) holeB=true;
      }
      //파란구슬이 빠진 경우(두 구슬이 모두 빠진 경우를 고려해야 하기에 파란 구글 먼저 check)
      if(holeB) return -1;
      //파란 구슬 빠지지 X, 빨간 구슬 빠진 경우
      if(holeR) return cnt;
    }
    // 10번 에 걸친 이동 이후의 횟수는 의미 X
    return -1;
  }

  // 10번의 움직임 중 의미있는 이동으로만 구성되었는지 확인한다.
  // 의미 없는 경우: 연속해서 같은 방향 또는 연속해서 반대방향
  public static boolean isValidDirections(int [] dir){
    int l= dir.length;
    for(int i=0; i+1<l; i++){
      //상하 반대
      if(dir[i]==0&&dir[i+1]==1) return false;
      if(dir[i]==1&&dir[i+1]==0) return false;
      //좌우 반대 
      if(dir[i]==2&&dir[i+1]==3) return false;
      if(dir[i]==3&&dir[i+1]==2) return false;
      //같은 방향 
      if(dir[i]==dir[i+1]) return false;
    }
    //10번의 이동이 모두 의미없지 않아야만, 의미있는 이동으로만 10번의 이동이 구성되어 있다. 
    return true;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();
    String [] map = new String[n];
    char[][] a = new char[n][m];
    for(int i=0; i<n; i++){
      map[i] = sc.next();
    }
    int ans = -1;
    // 이동가능한 모든 10번동안의 이동조합 에 관하여 탐색 시작
    for(int k=0; k<(1<<(LIMIT*2)); k++){
      // 10번의 이동가능한 조합 의 bitmask k를 10개의 이동을 의미하는 배열로 반환.
      int[] dir = gen(k);
      // 의미있는 이동들로만 이루어졌는지 확인.
      if(!isValidDirections(dir)) continue;
      for(int i=0; i<n; i++){
        a[i]= map[i].toCharArray();
      }
      int cur= check(a,dir);
      if(cur==-1) continue;
      if(ans==-1 || ans>cur) ans= cur;
    }
    System.out.println(ans);
  }
}