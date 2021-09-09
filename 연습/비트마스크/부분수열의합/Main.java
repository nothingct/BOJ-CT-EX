package 부분수열의합;
import java.util.*;
public class Main{
  public static void main(String[] args){
    Scanner sc =new Scanner(System.in);
    int n = sc.nextInt();
    int a[] =new int[n];
    boolean check[] = new boolean[n*100000+10];

    for(int i=0; i<n; i++) a[i]=sc.nextInt();
    
    for(int i=0; i<(1<<n); i++){
      int sum =0; 
      for(int j=0; j<n; j++){
        if( (i & (1<<j))!=0) sum+=a[j]; 
      }
      check[sum]= true;
    }
    for(int i=1; ; i++){
      if(check[i]==false){
        System.out.println(i);
        break;
      }
    }
  }
}