package 에너지모으기;
import java.util.*;

public class Main {
  static int solve(ArrayList<Integer> a){
    int n = a.size(); 
    if ( n== 2) return 0;
    int ans= 0 ; 
    for(int i=1; i<n-1; i++){
      int e = a.get(i-1)*a.get(i+1);
      ArrayList<Integer> b = new ArrayList<>(a);
      b.remove(i);
      e+= solve(b);
      if( ans < e ) ans = e;  
    }
    return ans; 
  }
  public static void main(String [] args){
    Scanner sc = new Scanner(System.in);
    int n= sc.nextInt();
    ArrayList<Integer> a = new ArrayList<>();
    for(int i=0; i<n; i++) a.add(sc.nextInt());
    System.out.println(solve(a));
  }
}
