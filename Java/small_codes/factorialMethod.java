import java.util.Scanner;

public class factorialMethod{
	static int fact(int n){
		if(n == 0){
			return 1;
		}
		else{
			return n * fact(n-1);
		}
	}
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a number to calculate the factorial : ");
		
		int num = sc.nextInt();
		
		System.out.println("The factorial of " + num + " is : " + fact(num));
	}
}
