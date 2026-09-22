public class EvenOddCount{
	public static void main(String[] args){
		int[] arr = {1,2,3,4,5,6,7};
		int even = 0, odd = 0;
		
		for(int i : arr){
			if(i % 2 == 0){
				even += 1;
			}
			else{
				odd += 1;
			}
		}
		System.out.println("Even : " + even);
		System.out.println("Odd : " + odd);
	}
}
