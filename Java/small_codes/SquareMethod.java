import java.util.Scanner;

public class SquareMethod{
	static int square(int a){
		return a * a;
	}

	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a number : ");
		int num = sc.nextInt();

		System.out.println("The square of the number " + num + " is : " + square(num));
	}
}
