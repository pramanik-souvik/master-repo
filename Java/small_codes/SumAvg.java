public class SumAvg{
	public static void main(String[] args){
		int[] arr = {1,2,3,4,5,6,7};
		int sum = 0;
		
		for (int i : arr){
			sum += i;
		}
		System.out.println("Sum : " + sum);
		System.out.println("Average : " + (sum/arr.length));
	}
}
