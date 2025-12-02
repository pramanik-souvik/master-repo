import java.io.*;

class Employee implements Serializable {
    private static final long serialVersionUID = 1L;
    String name;
    int id;

    Employee(String name, int id) {
        this.name = name;
        this.id = id;
    }
}

public class Serialization {
    public static void main(String[] args) {
        Employee e = new Employee("Souvik", 101);

        // Serialize
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("employee.ser"))) {
            out.writeObject(e);
            System.out.println("Object serialized.");
        } catch (IOException ex) {
            System.out.println("Serialization error: " + ex.getMessage());
        }

        // Deserialize
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream("employee.ser"))) {
            Employee e2 = (Employee) in.readObject();
            System.out.println("Deserialized Employee: " + e2.name + ", ID: " + e2.id);
        } catch (IOException | ClassNotFoundException ex) {
            System.out.println("Deserialization error: " + ex.getMessage());
        }
    }
}