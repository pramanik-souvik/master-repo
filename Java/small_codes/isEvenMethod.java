import java.util.Scanner;

public class isEvenMethod{
	static boolean isEven(int n){
		return n % 2 == 0;
	}
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a number to check : ");
		
		int num = sc.nextInt();
		
		System.out.println("Is Even : " + isEven(num));
	}
}
