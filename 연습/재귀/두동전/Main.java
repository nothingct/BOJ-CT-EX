package 두동전;
import java.util.*;

public class Main {
  static int n,m;
  static char board[][];
  static final int[] dx ={-1,0,1,0};
  static final int[] dy = { 0, -1, 0,1 };
  static int solve(int cnt, int c1_x, int c1_y,int c2_x, int c2_y){
    if(cnt==11) return -1; 
    boolean c1_drop= false;
    boolean c2_drop= false;
    if(c1_x< 0 || c1_x>=n || c1_y<0 || c1_y>=m) c1_drop=true;
    if (c2_x < 0 || c2_x >= n || c2_y < 0 || c2_y >= m) c2_drop = true;
    if(c1_drop && c2_drop) return -1;
    if(c1_drop ||c2_drop) return cnt;
    int ans = -1;
    // 아니라면, 다음으로 움직인다
    for (int i = 0; i < 4; i++) {
      int c1_nx = c1_x + dx[i];
      int c1_ny = c1_y + dy[i];
      int c2_nx = c2_x + dx[i];
      int c2_ny = c2_y + dy[i];
      if (0 <= c1_nx && c1_nx < n && 0 <= c1_ny && c1_ny < m && board[c1_nx][c1_ny] == '#') {
        c1_nx = c1_x;
        c1_ny = c1_y;
      }
      if (0 <= c2_nx && c2_nx < n && 0 <= c2_ny && c2_ny < m && board[c2_nx][c2_ny] == '#') {
        c2_nx = c2_x;
        c2_ny = c2_y;
      }
      int ret = solve(cnt + 1, c1_nx, c1_ny, c2_nx, c2_ny);
      if (ret == -1)
        continue;
      if (ans == -1 || ans > ret)
        ans = ret;
    }
    return ans;
  }

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    n= sc.nextInt();
    m= sc.nextInt();
    board = new char[n][m];
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=c1_y=c2_x=c2_y=-1;
    for(int i=0; i<n; i++){
      board[i]=sc.next().toCharArray();
      for(int j=0; j<m; j++){
        if(board[i][j] == 'o'){
          if(c1_x==-1){
            c1_x=i;
            c1_y=j;
          }else{
            c2_x=i;
            c2_y=j;
          }
          board[i][j]='.';
        }
      }
    }
    System.out.println(solve(0,c1_x,c1_y,c2_x,c2_y));
  }
}
