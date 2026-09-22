class BankAccount{
	int balance = 1000;
	
	void deposit(int amount){
		balance += amount;
	}

	void show(){
		System.out.println(balance);
	}

	public static void main(String[] args){
		BankAccount b = new BankAccount();
		b.deposit(500);
		b.show();
	}
}
