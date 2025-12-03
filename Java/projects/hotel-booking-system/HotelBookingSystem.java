import java.io.*;
import java.util.*;

public class HotelBookingSystem {
    private static final String FILE_NAME = "bookings.txt";
    private static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int choice;
        do {
            System.out.println("\n--- Hotel Booking System ---");
            System.out.println("1. Book a Room");
            System.out.println("2. View All Bookings");
            System.out.println("3. Search Booking by Name");
            System.out.println("0. Exit");
            System.out.print("Enter choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // consume newline

            switch (choice) {
                case 1: bookRoom(); break;
                case 2: viewBookings(); break;
                case 3: searchBooking(); break;
                case 0: System.out.println("Exiting..."); break;
                default: System.out.println("Invalid choice!"); 
            }
        } while (choice != 0);
    }

    private static void bookRoom() {
        System.out.print("Enter your name: ");
        String name = sc.nextLine();
        System.out.print("Enter room type (Single/Double/Suite): ");
        String roomType = sc.nextLine();
        System.out.print("Enter number of nights: ");
        int nights = sc.nextInt();
        sc.nextLine();

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(name + "," + roomType + "," + nights);
            writer.newLine();
            System.out.println("Room booked successfully!");
        } catch (IOException e) {
            System.out.println("Error booking room: " + e.getMessage());
        }
    }

    private static void viewBookings() {
        System.out.println("\n--- All Bookings ---");
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                System.out.println("Name: " + parts[0] + ", Room Type: " + parts[1] + ", Nights: " + parts[2]);
            }
        } catch (IOException e) {
            System.out.println("No bookings found or error reading file.");
        }
    }

    private static void searchBooking() {
        System.out.print("Enter name to search: ");
        String searchName = sc.nextLine().toLowerCase();
        boolean found = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts[0].toLowerCase().contains(searchName)) {
                    System.out.println("Name: " + parts[0] + ", Room Type: " + parts[1] + ", Nights: " + parts[2]);
                    found = true;
                }
            }
            if (!found) System.out.println("No bookings found for that name.");
        } catch (IOException e) {
            System.out.println("Error reading bookings: " + e.getMessage());
        }
    }
}