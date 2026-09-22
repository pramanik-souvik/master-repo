class RectangleClass{
	int length, width;

	int area(){
		return length * width;
	}
	
	public static void main(String[] args){
		RectangleClass r = new RectangleClass();
		
		r.length = 7;
		r.width = 4;

		System.out.println("Area : " + r.area());
	}
}
