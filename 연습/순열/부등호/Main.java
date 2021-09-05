import java.util.Scanner;

public class Main {
  //java,python -> next_permutation, prev_permutation 직접 구현할 수 있도록 연습 
  public static boolean next_permutation(int []a ){
    //맨 끝에서부터
    int i= a.length-1;
    //가장 긴 감소하는 수열을 찾는다.
    while(i>0 && a[i-1]>=a[i]) i-=1;
    if(i<=0) return false;
    //맨 끝에서부터 i보다 크거나 같으면서,
    int j=a.length-1;
    //a[i-1]보다 큰 a[j]를 찾는다.
    while(a[j]<=a[i-1]) j-=1;
    //a[j]와 a[i-1]을 스왑한다.
    int temp =a[i-1];
    a[i-1]=a[j];
    a[j]=temp;
    //a[i]부터 끝까지 순열을 뒤집는다.
    j=a.length-1;
    while( i< j ) {
      temp = a[i];
      a[i]=a[j];
      a[j]=temp;
      i+=1;
      j-=1;
    }
    return true;
  }
  
  public static boolean prev_permutation(int[] a) {
    //맨 끝에서부터
    int i = a.length - 1;
    //가장 긴 증가하는 부분수열을 찾는다.
    while (i > 0 && a[i - 1] <= a[i])
      i -= 1;
    if (i <= 0)
      return false;
    //맨 끝에서부터 i보다 작거나 같으면서
    int j = a.length - 1;
    //a[i-1]보다 작은 a[j]를 찾는다.
    while (a[j] >= a[i - 1])
      j -= 1;
    //a[j]와 a[i-1]을 스왑한다. 
    int temp = a[i - 1];
    a[i - 1] = a[j];
    a[j] = temp;
    //a[i]부터 끝까지 스왑한다. 
    j = a.length - 1;
    while (i < j) {
      temp = a[i];
      a[i] = a[j];
      a[j] = temp;
      i += 1;
      j -= 1;
    }
    return true;
  }
  public static boolean check(int[] perm,char[] a){
    for(int i=0; i<a.length; i++){
      if (a[i] == '<' && perm[i] > perm[i + 1]) {
        return false;
      }
      if (a[i] == '>' && perm[i] < perm[i + 1]) {
        return false;
      }
    }
    return true;
  }

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int k= sc.nextInt();
    char a[] = new char[k];
    for(int i=0; i<k ; i++) a[i]=sc.next().charAt(0);
    int small[] = new int[k+1];
    int big[] = new int[k+1];
    for(int i=0; i<=k; i++){
      small[i]=i;
      big[i]=9-i;
    }
    do{
      if(check(small, a)) break;
    }while(next_permutation(small));

    do{
      if(check(big, a)) break;
    }while(prev_permutation(big));

    for(int i=0; i<big.length; i++){
      System.out.print(big[i]);
    }
    System.out.println();
    for (int i = 0; i < small.length; i++) {
      System.out.print(small[i]);
    }
    System.out.println();
  }
}
