public class sumArrayMethod{
	static int sum(int[] arr){
		int s = 0;
		for (int i : arr){
			s += i;
		}
		return s;
	}
	
	public static void main(String[] args){
		int[] arr = {2,4,6,8};
		
		System.out.println("The sum of the array is : " + sum(arr));
	}
}
