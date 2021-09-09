import java.util.*; 

public class Main{
  public static int readWords(int mask, int[] words){
    int cnt = 0; 
    for(int word:words){
      if ( (word & ((1<<26) -1 -mask)) == 0 ) cnt+=1;
    }
    return cnt;
  }

  public static int solve(int index, int k, int learned, int[] words){
    if(k<0) return 0;
    if(index == 26) return readWords(learned,words);
    int ans =0;
    //배우는 경우,
    int temp=solve(index+1, k-1, learned|(1<<index), words);
    if(ans < temp ) ans = temp; 
    //a,n,t,i,c가 아닌데 배우지 않는 경우 
    if(index!='a'-'a' && index!= 'n'-'a'&&index!='t'-'a'&&index!='i'-'a'&&index!='c'-'a'){
      temp = solve(index+1, k, learned, words);
      if(ans <temp ) ans = temp ; 
    }
    return ans;
  }

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int k = sc.nextInt();
    int[] words =new int[n];
    for(int i=0; i<n; i++){
      String s= sc.next();
      for(char c : s.toCharArray()){
        words[i] |= (1<<(c-'a'));
      }
    }
    System.out.println(solve(0,k,0,words));
  }
}