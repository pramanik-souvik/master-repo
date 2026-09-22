import java.util.Scanner;

public class EvenOddNumbers{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a range : ");
		
		int range = sc.nextInt();
		
		sc.nextLine();
		
		System.out.println("Do you want Even or Odd :");
		
		String type = sc.nextLine();
		
			switch(type){
				case "Even":
					for(int i = 1; i <= range; i += 1){
						if(i % 2 == 0){
							System.out.print(i + " ");
						}
					}
					System.out.println();
					break;
				case "Odd":
					for(int i = 1; i <= range; i += 1){
						if(i % 2 != 0){
							System.out.print(i + " ");
						}
					}
					System.out.println();
					break;
				default:
					System.out.println("Invalid input type exactly 'Even' or 'Odd' maintaing the capital letters. ");
			}
	}
}
