package 부분수열의합14225;
import java.util.*;
public class Main {
  public static int solve(int [] a, int index, int target){
    if(a.length==index) return target;
    if(a[index] > target) return target;
    return solve(a,index+1,target+a[index]);
  }

  public static void main(String args[]){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int [] a = new int[n];
    for(int i=0; i<n; i++){
      a[i] = sc.nextInt();
    }
    Arrays.sort(a);
    System.out.println(solve(a,0,1));
  }
}
