class Circle{
	double radius;

	double area(){
		return Math.PI * radius * radius;
	}
	
	public static void main(String[] args){
		Circle c = new Circle();
		c.radius = 5;
		System.out.println(c.area());
	}
}
