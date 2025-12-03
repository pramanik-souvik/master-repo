import java.io.*;
import java.util.*;

class Student implements Serializable {
    private static final long serialVersionUID = 1L;
    private int id;
    private String name;
    private int age;
    private String course;

    public Student(int id, String name, int age, String course) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.course = course;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public int getAge() { return age; }
    public String getCourse() { return course; }

    public void setName(String name) { this.name = name; }
    public void setAge(int age) { this.age = age; }
    public void setCourse(String course) { this.course = course; }

    @Override
    public String toString() {
        return String.format("ID: %d | Name: %s | Age: %d | Course: %s", id, name, age, course);
    }
}

public class StudentInfoSystem {
    private static final String FILE_NAME = "students.dat";
    private static List<Student> students = new ArrayList<>();

    public static void main(String[] args) {
        loadData();

        Scanner sc = new Scanner(System.in);
        while (true) {
            System.out.println("\n===== Student Information System =====");
            System.out.println("1. Add Student");
            System.out.println("2. View All Students");
            System.out.println("3. Search Student by ID");
            System.out.println("4. Update Student");
            System.out.println("5. Delete Student");
            System.out.println("6. Sort Students");
            System.out.println("7. Export to Text File");
            System.out.println("8. Exit");
            System.out.print("Choose option: ");

            int choice;
            try {
                choice = Integer.parseInt(sc.nextLine());
            } catch (Exception e) {
                System.out.println("Invalid input! Please enter a number.");
                continue;
            }

            switch (choice) {
                case 1 -> addStudent(sc);
                case 2 -> viewAll();
                case 3 -> searchStudent(sc);
                case 4 -> updateStudent(sc);
                case 5 -> deleteStudent(sc);
                case 6 -> sortStudents(sc);
                case 7 -> exportToFile();
                case 8 -> {
                    saveData();
                    System.out.println("Data saved. Goodbye!");
                    return;
                }
                default -> System.out.println("Invalid choice.");
            }
        }
    }

    private static void addStudent(Scanner sc) {
        try {
            System.out.print("Enter ID: ");
            int id = Integer.parseInt(sc.nextLine());
            for (Student s : students) {
                if (s.getId() == id) {
                    System.out.println("Student ID already exists.");
                    return;
                }
            }

            System.out.print("Enter Name: ");
            String name = sc.nextLine();
            System.out.print("Enter Age: ");
            int age = Integer.parseInt(sc.nextLine());
            System.out.print("Enter Course: ");
            String course = sc.nextLine();

            students.add(new Student(id, name, age, course));
            System.out.println("Student added successfully!");
        } catch (Exception e) {
            System.out.println("Invalid input, student not added.");
        }
    }

    private static void viewAll() {
        if (students.isEmpty()) {
            System.out.println("No students found.");
            return;
        }
        System.out.println("\n--- Student List ---");
        students.forEach(System.out::println);
    }

    private static void searchStudent(Scanner sc) {
        System.out.print("Enter student ID: ");
        int id = Integer.parseInt(sc.nextLine());
        for (Student s : students) {
            if (s.getId() == id) {
                System.out.println("Found: " + s);
                return;
            }
        }
        System.out.println("Student not found.");
    }

    private static void updateStudent(Scanner sc) {
        System.out.print("Enter student ID to update: ");
        int id = Integer.parseInt(sc.nextLine());
        for (Student s : students) {
            if (s.getId() == id) {
                System.out.print("Enter new Name (current: " + s.getName() + "): ");
                s.setName(sc.nextLine());
                System.out.print("Enter new Age (current: " + s.getAge() + "): ");
                s.setAge(Integer.parseInt(sc.nextLine()));
                System.out.print("Enter new Course (current: " + s.getCourse() + "): ");
                s.setCourse(sc.nextLine());
                System.out.println("Student updated successfully!");
                return;
            }
        }
        System.out.println("Student not found.");
    }

    private static void deleteStudent(Scanner sc) {
        System.out.print("Enter student ID to delete: ");
        int id = Integer.parseInt(sc.nextLine());
        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            if (iterator.next().getId() == id) {
                iterator.remove();
                System.out.println("Student deleted successfully!");
                return;
            }
        }
        System.out.println("Student not found.");
    }

    private static void sortStudents(Scanner sc) {
        System.out.println("Sort by: 1.ID  2.Name  3.Age");
        int opt = Integer.parseInt(sc.nextLine());
        switch (opt) {
            case 1 -> students.sort(Comparator.comparingInt(Student::getId));
            case 2 -> students.sort(Comparator.comparing(Student::getName));
            case 3 -> students.sort(Comparator.comparingInt(Student::getAge));
            default -> {
                System.out.println("Invalid sort option.");
                return;
            }
        }
        System.out.println("Students sorted successfully!");
        viewAll();
    }

    private static void exportToFile() {
        try (PrintWriter pw = new PrintWriter("students.txt")) {
            for (Student s : students) {
                pw.println(s);
            }
            System.out.println("Student list exported to students.txt");
        } catch (IOException e) {
            System.out.println("Error exporting file: " + e.getMessage());
        }
    }

    private static void saveData() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(students);
        } catch (IOException e) {
            System.out.println("Error saving data: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    private static void loadData() {
        File file = new File(FILE_NAME);
        if (!file.exists()) return;
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
            students = (List<Student>) ois.readObject();
        } catch (Exception e) {
            System.out.println("Error loading data: " + e.getMessage());
        }
    }
}