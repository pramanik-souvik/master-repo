class Car{
	String brand;
	
	void show(){
		System.out.println(brand);
	}

	public static void main(String[] args){
		Car c = new Car();
		c.brand = "Tesla";
		c.show();
	}
}
