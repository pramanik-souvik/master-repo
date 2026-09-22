class ConstructorDemo{
	int x;
	
	ConstructorDemo(int a){
		x = a;
	}
	
	public static void main(String[] args){
		ConstructorDemo obj = new ConstructorDemo(10);
		System.out.println(obj.x);
	}
}
