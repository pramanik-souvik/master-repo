import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
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

public class StudentInfoSystemGUI extends JFrame {
    private static final String FILE_NAME = "students.dat";
    private java.util.List<Student> students = new ArrayList<>();
    private DefaultTableModel tableModel;

    private JTextField txtId, txtName, txtAge, txtCourse, txtSearch;
    private JComboBox<String> sortOptions;

    public StudentInfoSystemGUI() {
        setTitle("Student Information System");
        setSize(850, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Load data
        loadData();

        // Table
        tableModel = new DefaultTableModel(new String[]{"ID", "Name", "Age", "Course"}, 0);
        JTable table = new JTable(tableModel);
        refreshTable();
        JScrollPane scrollPane = new JScrollPane(table);

        // Input panel
        JPanel inputPanel = new JPanel(new GridLayout(2, 4, 10, 10));
        txtId = new JTextField();
        txtName = new JTextField();
        txtAge = new JTextField();
        txtCourse = new JTextField();
        inputPanel.add(new JLabel("ID:"));
        inputPanel.add(txtId);
        inputPanel.add(new JLabel("Name:"));
        inputPanel.add(txtName);
        inputPanel.add(new JLabel("Age:"));
        inputPanel.add(txtAge);
        inputPanel.add(new JLabel("Course:"));
        inputPanel.add(txtCourse);

        // Buttons
        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton btnAdd = new JButton("Add");
        JButton btnUpdate = new JButton("Update");
        JButton btnDelete = new JButton("Delete");
        JButton btnExport = new JButton("Export");
        JButton btnSaveExit = new JButton("Save & Exit");

        // Sorting options
        sortOptions = new JComboBox<>(new String[]{"Sort by ID", "Sort by Name", "Sort by Age", "Sort by Course"});
        JButton btnSort = new JButton("Sort");

        buttonPanel.add(btnAdd);
        buttonPanel.add(btnUpdate);
        buttonPanel.add(btnDelete);
        buttonPanel.add(btnExport);
        buttonPanel.add(sortOptions);
        buttonPanel.add(btnSort);
        buttonPanel.add(btnSaveExit);

        // Search bar
        JPanel searchPanel = new JPanel(new FlowLayout());
        txtSearch = new JTextField(20);
        JButton btnSearch = new JButton("Search by ID");
        searchPanel.add(new JLabel("Search:"));
        searchPanel.add(txtSearch);
        searchPanel.add(btnSearch);

        // Layout
        setLayout(new BorderLayout());
        add(scrollPane, BorderLayout.CENTER);
        add(inputPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.SOUTH);
        add(searchPanel, BorderLayout.WEST);

        // Actions
        btnAdd.addActionListener(e -> addStudent());
        btnUpdate.addActionListener(e -> updateStudent(table));
        btnDelete.addActionListener(e -> deleteStudent(table));
        btnSearch.addActionListener(e -> searchStudent());
        btnSort.addActionListener(e -> sortStudents());
        btnExport.addActionListener(e -> exportToFile());
        btnSaveExit.addActionListener(e -> {
            saveData();
            System.exit(0);
        });

        setVisible(true);
    }

    private void refreshTable() {
        tableModel.setRowCount(0);
        for (Student s : students) {
            tableModel.addRow(new Object[]{s.getId(), s.getName(), s.getAge(), s.getCourse()});
        }
    }

    private void addStudent() {
        try {
            int id = Integer.parseInt(txtId.getText());
            for (Student s : students) {
                if (s.getId() == id) {
                    JOptionPane.showMessageDialog(this, "ID already exists.");
                    return;
                }
            }
            String name = txtName.getText();
            int age = Integer.parseInt(txtAge.getText());
            String course = txtCourse.getText();
            students.add(new Student(id, name, age, course));
            refreshTable();
            clearFields();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Invalid input.");
        }
    }

    private void updateStudent(JTable table) {
        int row = table.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "Select a student to update.");
            return;
        }
        try {
            String name = txtName.getText();
            int age = Integer.parseInt(txtAge.getText());
            String course = txtCourse.getText();

            Student s = students.get(row);
            s.setName(name);
            s.setAge(age);
            s.setCourse(course);
            refreshTable();
            clearFields();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Invalid input.");
        }
    }

    private void deleteStudent(JTable table) {
        int row = table.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "Select a student to delete.");
            return;
        }
        students.remove(row);
        refreshTable();
    }

    private void searchStudent() {
        try {
            int id = Integer.parseInt(txtSearch.getText());
            for (Student s : students) {
                if (s.getId() == id) {
                    JOptionPane.showMessageDialog(this, "Found: " + s);
                    return;
                }
            }
            JOptionPane.showMessageDialog(this, "Student not found.");
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Invalid input.");
        }
    }

    private void sortStudents() {
        String choice = (String) sortOptions.getSelectedItem();
        if (choice == null) return;

        switch (choice) {
            case "Sort by ID":
                students.sort(Comparator.comparingInt(Student::getId));
                break;
            case "Sort by Name":
                students.sort(Comparator.comparing(Student::getName));
                break;
            case "Sort by Age":
                students.sort(Comparator.comparingInt(Student::getAge));
                break;
            case "Sort by Course":
                students.sort(Comparator.comparing(Student::getCourse));
                break;
        }
        refreshTable();
    }

    private void exportToFile() {
        try (PrintWriter pw = new PrintWriter("students.txt")) {
            for (Student s : students) {
                pw.println(s);
            }
            JOptionPane.showMessageDialog(this, "Exported to students.txt");
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Export failed: " + e.getMessage());
        }
    }

    private void saveData() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(students);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Save failed: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    private void loadData() {
        File file = new File(FILE_NAME);
        if (!file.exists()) return;
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
            students = (java.util.List<Student>) ois.readObject();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Load failed: " + e.getMessage());
        }
    }

    private void clearFields() {
        txtId.setText("");
        txtName.setText("");
        txtAge.setText("");
        txtCourse.setText("");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(StudentInfoSystemGUI::new);
    }
}