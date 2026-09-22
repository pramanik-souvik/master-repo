import java.util.Scanner;

public class findMaxMethod{
	static int max(int a, int b){
		if(a > b){
			return a;
		}
		else{
			return b;
		}
	}
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Enter 2 integers : ");
		int n1 = sc.nextInt();
		int n2 = sc.nextInt();
		
		System.out.println("The maximum number between " + n1 + " and " + n2 + " is : " + max(n1,n2));
	}
}
