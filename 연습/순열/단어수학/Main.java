import java.util.*;
public class Main {
  static boolean next_permutation(int[] a){
    int i = a.length-1;
    while(i>0 && a[i-1]>=a[i]) i-=1;
    if(i<=0) return false;
    int j = a.length-1;
    while(a[j] <=a[i-1]) j-=1;
    int temp = a[j];
    a[j]=a[i-1];
    a[i-1]=temp;

    j= a.length-1;
    while(i<j){
      temp=a[i];
      a[i]=a[j];
      a[j]=temp;
      i+=1;
      j-=1;
    }
    return true;
  }
  
  public static int[] alpha = new int[256];
  public static int calc(String[] a, Character[] letters, int[] perm){
    int m = letters.length;
    for(int i=0; i<m; i++) alpha[letters[i]]=perm[i];
    int sum=0;
    for(String s: a){
      int now = 0;
      for(char x : s.toCharArray()){
        now= now*10+alpha[x];
      }
      sum+=now;
    }
    return sum;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    String [] a = new String[n];
    HashSet<Character> s = new HashSet<>();
    for(int i=0; i<n; i++){
      a[i]=sc.next();
      for(char x: a[i].toCharArray()){
        s.add(x);
      }
    }
    Character[] letters = s.toArray(new Character[s.size()]);
    int m = letters.length;
    int[] perm = new int[m];
    for(int i=0; i<m; i++) perm[i]=9-i;
    Arrays.sort(perm);
    int ans = 0;
    do{
      int now = calc(a,letters,perm);
      if(ans < now ) ans = now;
    }while(next_permutation(perm));
    System.out.println(ans);
  }
}
