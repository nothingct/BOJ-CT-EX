package 연산자끼워넣기;
import java.util.*;
class Pair{
  public int max,min;
  public Pair(int max, int min) {
    this.max = max;
    this.min = min;
  }
}

public class Main{
  static Pair cal(int[] a, int res, int idx, int add, int sub, int mul , int div){
    int n = a.length;
    if(idx==n){
      return new Pair(res,res);
    }
    ArrayList<Pair> results= new ArrayList<>();
    if (add > 0) results.add(cal(a, res + a[idx], idx + 1, add - 1, sub, mul, div));
    if (sub > 0) results.add(cal(a, res - a[idx], idx + 1, add, sub - 1, mul, div));
    if (mul > 0) results.add(cal(a, res * a[idx], idx + 1, add, sub, mul - 1, div));
    if (div > 0) results.add(cal(a, res / a[idx], idx + 1, add, sub, mul, div - 1));
    Pair ans = results.get(0);
    for (Pair result : results) {
      if(ans.max < result.max) ans.max=result.max;
      if(ans.min > result.min) ans.min=result.min;
    }
    return ans;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int[] a = new int[n];
    for(int i=0; i<n; i++){
      a[i] = sc.nextInt();
    }
    int add= sc.nextInt();
    int sub = sc.nextInt();
    int mul = sc.nextInt();
    int div = sc.nextInt();
    Pair ans = cal(a,a[0],1,add,sub,mul,div);
    System.out.println(ans.max);
    System.out.println(ans.min);
  }
}