public class ClassObject {
    public static void main(String[] args) {
        // Create two Person objects
        Person p1 = new Person("Alice", 25);
        Person p2 = new Person("Bob", 30);

        // Call their introduce method
        p1.introduce();
        p2.introduce();

        // Optional: use getters and setters
        p1.setAge(26);
        System.out.println(p1.getName() + " is now " + p1.getAge() + " years old.");
    }
}

class Person {
    private String name;
    private int age;

    // Constructor
    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // Method to introduce the person
    public void introduce() {
        System.out.println("Hi, I'm " + name + " and I'm " + age + " years old.");
    }

    // Getters and setters
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
}