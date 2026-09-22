class Encapsulation{
	private int data;

	public void setData(int a){
		data = a;
	}

	public int getData(){
		return data;
	}

	public static void main(String[] args){
		Encapsulation e = new Encapsulation();
		e.setData(10);
		System.out.println(e.getData());
	}
}
