import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class HotelBookingSystemGUI extends JFrame {
    private JTextField nameField, roomField, nightsField, searchField;
    private JTextArea displayArea;
    private static final String FILE_NAME = "bookings.txt";

    public HotelBookingSystemGUI() {
        setTitle("Hotel Booking System");
        setSize(600, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Top panel for booking
        JPanel topPanel = new JPanel(new GridLayout(4, 2, 5, 5));
        topPanel.setBorder(BorderFactory.createTitledBorder("Book a Room"));

        topPanel.add(new JLabel("Name:"));
        nameField = new JTextField();
        topPanel.add(nameField);

        topPanel.add(new JLabel("Room Type:"));
        roomField = new JTextField();
        topPanel.add(roomField);

        topPanel.add(new JLabel("Number of Nights:"));
        nightsField = new JTextField();
        topPanel.add(nightsField);

        JButton bookButton = new JButton("Book Room");
        topPanel.add(bookButton);

        JButton viewButton = new JButton("View All Bookings");
        topPanel.add(viewButton);

        add(topPanel, BorderLayout.NORTH);

        // Center panel for display
        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);
        scrollPane.setBorder(BorderFactory.createTitledBorder("Bookings"));
        add(scrollPane, BorderLayout.CENTER);

        // Bottom panel for search
        JPanel bottomPanel = new JPanel(new FlowLayout());
        bottomPanel.setBorder(BorderFactory.createTitledBorder("Search Booking"));
        bottomPanel.add(new JLabel("Name:"));
        searchField = new JTextField(15);
        bottomPanel.add(searchField);
        JButton searchButton = new JButton("Search");
        bottomPanel.add(searchButton);

        add(bottomPanel, BorderLayout.SOUTH);

        // Button actions
        bookButton.addActionListener(e -> bookRoom());
        viewButton.addActionListener(e -> viewBookings());
        searchButton.addActionListener(e -> searchBooking());

        setVisible(true);
    }

    private void bookRoom() {
        String name = nameField.getText().trim();
        String room = roomField.getText().trim();
        String nights = nightsField.getText().trim();

        if (name.isEmpty() || room.isEmpty() || nights.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Please fill all fields!");
            return;
        }

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(name + "," + room + "," + nights);
            writer.newLine();
            JOptionPane.showMessageDialog(this, "Room booked successfully!");
            nameField.setText("");
            roomField.setText("");
            nightsField.setText("");
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Error booking room: " + e.getMessage());
        }
    }

    private void viewBookings() {
        displayArea.setText("");
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                displayArea.append("Name: " + parts[0] + ", Room Type: " + parts[1] + ", Nights: " + parts[2] + "\n");
            }
        } catch (IOException e) {
            displayArea.setText("No bookings found or error reading file.");
        }
    }

    private void searchBooking() {
        String searchName = searchField.getText().trim().toLowerCase();
        if (searchName.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Enter a name to search!");
            return;
        }

        displayArea.setText("");
        boolean found = false;
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts[0].toLowerCase().contains(searchName)) {
                    displayArea.append("Name: " + parts[0] + ", Room Type: " + parts[1] + ", Nights: " + parts[2] + "\n");
                    found = true;
                }
            }
            if (!found) displayArea.setText("No bookings found for that name.");
        } catch (IOException e) {
            displayArea.setText("Error reading bookings: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new HotelBookingSystemGUI());
    }
}