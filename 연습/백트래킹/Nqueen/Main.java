package 백트래킹.Nqueen;

import java.util.*;
public class Main{
  static boolean[][] a = new boolean[15][15];
  static int n ;
  static boolean[] check_col = new boolean[15];
  static boolean[] check_lu_rd = new boolean[40];
  static boolean[] check_ru_ld = new boolean[40];

  static boolean check(int row, int col){
    if(check_col[col]) return false;
    if(check_lu_rd[row+col]) return false;
    if(check_ru_ld[n+row-col]) return false;
    return true;
  }
  static void setCheckValue(int row,int col,boolean val){
    check_col[col]=val;
    check_lu_rd[row+col]=val;
    check_ru_ld[row+n-col]=val;
    a[row][col] = val;
  }
  static int cal(int row){
    if(row==n) return 1;
    int cnt = 0 ; 
    for(int col =0; col <n; col++){
      if(check(row,col)){
        setCheckValue(row,col,true);
        cnt+=cal(row+1);
        setCheckValue(row, col, false);
      }
    }
    return cnt;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    n=sc.nextInt();
    System.out.println(cal(0));
  }
}