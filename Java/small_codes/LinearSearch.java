import java.util.Scanner;

public class LinearSearch{
	public static void main(String[] args){
		int[] arr = {1,2,4,5,7,8,10,11,13,15,17,18};
		
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the key : ");
		
		int key = sc.nextInt();
	
		boolean found = false;

		for(int i = 0; i < arr.length; i++){
			if(arr[i] == key){
				System.out.println("Found at index : " + i);
				found = true;
				break;
			}
		}
		
		if(!found){
			System.out.println("Number not found in array.");
		}
	}
}
