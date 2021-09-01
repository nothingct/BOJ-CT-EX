package 부분수열의합;
import java.util.*;
public class Main {
  public static int go(int[] a, int index, int sum,int s){
    if(index==a.length){
      if(sum==s) return 1; 
      else return 0;
    }
    return go(a,index+1,sum+a[index],s)+go(a,index+1,sum,s);
  }
  public static void main(String args[]){
    Scanner sc = new Scanner(System.in);
    int n=sc.nextInt();
    int s=sc.nextInt();
    int[] a = new int[n];
    for(int i=0; i<n; i++) a[i]=sc.nextInt();
    int ans = go(a,0,0,s);
    if(s==0) ans-=1;
    System.out.println(ans);
  }
}
