import java.util.*;

public class Main {
  static boolean[] c = new boolean[20*100000+10];
  static int[] a = new int[20];
  static int n ; 
  public static void solve(int index, int sum){
    if(index==n) {
      c[sum]= true; 
      return;
    }
    solve(index+1,sum+a[index]);
    solve(index+1, sum);
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    n=sc.nextInt();
    for(int i=0; i<n; i++) a[i]=sc.nextInt();
    solve(0,0);
    int num=1; 
    while(true){
      if(c[num]==false) {
        System.out.println(num);
        break;
      }
      num++;
    }
  }
}
