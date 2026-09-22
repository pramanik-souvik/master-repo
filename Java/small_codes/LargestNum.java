public class LargestNum{
	public static void main(String[] args){
		int[] arr = {8, 4, 2, 5, 9, 1, 3, 7};
		int max = arr[0];

		for(int i : arr){
			if (i > max){
				max = i;
			}
		}
		System.out.println(max);
	}
}
