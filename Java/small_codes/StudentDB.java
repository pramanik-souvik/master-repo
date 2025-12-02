import java.io.*;
import java.util.*;

public class StudentDB {
    private static final String FILE_NAME = "students.txt";

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int choice;

        do {
            System.out.println("\n--- Student Database Demo ---");
            System.out.println("1. Add Student");
            System.out.println("2. List Students");
            System.out.println("3. Search Student by Name");
            System.out.println("0. Exit");
            System.out.print("Enter choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    addStudent(sc);
                    break;
                case 2:
                    listStudents();
                    break;
                case 3:
                    searchStudent(sc);
                    break;
                case 0:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid choice!");
            }
        } while (choice != 0);

        sc.close();
    }

    private static void addStudent(Scanner sc) {
        System.out.print("Enter student name: ");
        String name = sc.nextLine();
        System.out.print("Enter student ID: ");
        String id = sc.nextLine();

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(id + "," + name);
            writer.newLine();
            System.out.println("Student added successfully!");
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }
    }

    private static void listStudents() {
        System.out.println("\n--- Student List ---");
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                System.out.println("ID: " + parts[0] + ", Name: " + parts[1]);
            }
        } catch (IOException e) {
            System.out.println("No students found or error reading file.");
        }
    }

    private static void searchStudent(Scanner sc) {
        System.out.print("Enter name to search: ");
        String searchName = sc.nextLine().toLowerCase();
        boolean found = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts[1].toLowerCase().contains(searchName)) {
                    System.out.println("ID: " + parts[0] + ", Name: " + parts[1]);
                    found = true;
                }
            }
            if (!found) System.out.println("No student found with that name.");
        } catch (IOException e) {
            System.out.println("No students found or error reading file.");
        }
    }
}