import java.util.Scanner;

public class Factorial{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a number to determine factorial : ");
		
		int num = sc.nextInt();
		int fact = 1;
		while (num > 0){
			fact *= num;
			num -= 1;
		}
		System.out.println(fact);
	}
}
