
import java.util.*;
public class Main {
  static int a[][] = new int[10][10];
  static boolean c[][] = new boolean[10][10];
  static boolean c2[][] = new boolean[10][10];
  static boolean c3[][] = new boolean[10][10];
  static boolean domino[][] = new boolean[10][10];
  static final int n = 9; 
  static final int dx[] = { 1, 0 };
  static final int dy[] = { 0, 1 };

  static int boxing(int x, int y){ return (x/3)*3+(y/3);}
  static boolean isPossible(int x, int y,int num){
    return (!c[x][num]&&!c2[y][num]&&!c3[boxing(x,y)][num]);   
  }
  static void setValue(int x, int y,int num,boolean val){
    c[x][num]=val;
    c2[y][num]=val;
    c3[boxing(x,y)][num]=val;
  }
  static boolean check_range(int x, int y){
    return 0<=x && x<n && 0<=y && y<n;
  }
  static boolean solve(int z){
    if(z==81){
      for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
          System.out.print(a[i][j]);
        }
        System.out.println();
      }
      return true;
    }
    int x= z/n;
    int y= z%n;
    if(a[x][y]!=0){
      return solve(z+1);
    }else{
      for(int d=0; d<2; d++){
        int nx = x+dx[d];
        int ny = y+dy[d];
        if(!check_range(nx, ny)) continue;
        if(a[nx][ny]!=0) continue;
        for(int i=1; i<=9; i++){
          for(int j=1; j<=9; j++){
            if(i==j) continue;
            if(domino[i][j]) continue;
            if(isPossible(x, y, i)&&isPossible(nx, ny, j)){
              setValue(x, y, i, true);
              setValue(nx, ny, j, true);
              domino[i][j]=domino[j][i]=true;
              a[x][y]=i;
              a[nx][ny]=j;
              if(solve(z+1)) return true;
              setValue(x, y, i, false);
              setValue(nx, ny, j, false);
              domino[i][j] = domino[j][i] = false;
              a[x][y] = 0;
              a[nx][ny] = 0;
            }
          }
        }
      }
    }
    return false;
  }
  public static void main(String[] args){
    int tc=1;
    Scanner sc = new Scanner(System.in);
    while(true){
      //자바의 2차원 배열 초기화 방법 숙지하기.
      for(int i=0; i<10; i++){
        Arrays.fill(c[i], false);
        Arrays.fill(c2[i], false);
        Arrays.fill(c3[i], false);
        Arrays.fill(domino[i], false);
        Arrays.fill(a[i], 0);

      }
      int m=sc.nextInt();
      if(m==0) break;
      for(int i=0; i<m; i++){
        int n1= sc.nextInt();
        String s1= sc.next();
        int n2= sc.nextInt();
        String s2 = sc.next();
        int x1= s1.charAt(0) - 'A';
        int y1 = s1.charAt(1) - '1';
        int x2 = s2.charAt(0) - 'A';
        int y2 = s2.charAt(1) - '1';
        a[x1][y1]=n1;
        a[x2][y2]=n2;
        domino[n1][n2]=domino[n2][n1]=true;
        setValue(x1, y1, n1, true);
        setValue(x2, y2, n2, true);
      }
      for(int i=1; i<=9; i++){
        String s=sc.next();
        int x= s.charAt(0)-'A';
        int y= s.charAt(1)-'1';
        a[x][y]=i;
        setValue(x, y, i, true);
      }
      System.out.println("Puzzle "+tc);
      solve(0);
      tc+=1;
    }
  }
}
