class StudentClass{
	String name;
	int age;
	
	void display(){
		System.out.println(name + " " + age);
	}
	
	public static void main(String[] args){
		StudentClass s = new StudentClass();
		
		s.name = "Alex";
		s.age = 24;
		s.display();
	}
}
