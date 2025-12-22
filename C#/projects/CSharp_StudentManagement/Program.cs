using System;
using System.Collections.Generic;
using System.Linq;

namespace StudentManagementApp
{
    class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Age { get; set; }
        public string Department { get; set; }
        public double GPA { get; set; }
        public bool Active { get; set; } = true;
    }

    class Manager
    {
        static List<Student> students = new List<Student>();
        static int nextId = 1;

        static void Main()
        {
            Console.Title = "Student Management System";
            bool running = true;

            while (running)
            {
                ShowMenu();
                Console.Write("Choose an option: ");
                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1": AddStudent(); break;
                    case "2": ViewStudents(); break;
                    case "3": EditStudent(); break;
                    case "4": DeleteStudent(); break;
                    case "5": SearchStudent(); break;
                    case "6": SortStudents(); break;
                    case "7": FilterByDepartment(); break;
                    case "8": CalculateAverageGPA(); break;
                    case "9": DeactivateStudent(); break;
                    case "10": ShowActiveInactive(); break;
                    case "0": running = false; Console.WriteLine("Exiting..."); break;
                    default: Console.WriteLine("Invalid option."); break;
                }

                if (running)
                {
                    Console.WriteLine("\nPress any key to return to menu...");
                    Console.ReadKey();
                    Console.Clear();
                }
            }
        }

        static void ShowMenu()
        {
            Console.WriteLine("============ STUDENT MANAGEMENT ============");
            Console.WriteLine("1. Add Student");
            Console.WriteLine("2. View All Students");
            Console.WriteLine("3. Edit Student");
            Console.WriteLine("4. Delete Student");
            Console.WriteLine("5. Search Student");
            Console.WriteLine("6. Sort Students");
            Console.WriteLine("7. Filter by Department");
            Console.WriteLine("8. Calculate Average GPA");
            Console.WriteLine("9. Deactivate Student");
            Console.WriteLine("10. Show Active/Inactive Students");
            Console.WriteLine("0. Exit");
            Console.WriteLine("=============================================");
        }

        static void AddStudent()
        {
            Console.Write("Name: ");
            string name = Console.ReadLine();

            Console.Write("Age: ");
            int age = int.Parse(Console.ReadLine());

            Console.Write("Department: ");
            string dept = Console.ReadLine();

            Console.Write("GPA: ");
            double gpa = double.Parse(Console.ReadLine());

            students.Add(new Student
            {
                Id = nextId++,
                Name = name,
                Age = age,
                Department = dept,
                GPA = gpa,
                Active = true
            });

            Console.WriteLine("Student added successfully.");
        }

        static void ViewStudents()
        {
            if (students.Count == 0)
            {
                Console.WriteLine("No students found.");
                return;
            }

            Console.WriteLine("\n--- Student List ---");
            foreach (var s in students)
            {
                string status = s.Active ? "Active" : "Inactive";
                Console.WriteLine($"ID: {s.Id} | Name: {s.Name} | Age: {s.Age} | Dept: {s.Department} | GPA: {s.GPA:F2} | Status: {status}");
            }
        }

        static void EditStudent()
        {
            Console.Write("Enter Student ID to edit: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var s = students.FirstOrDefault(st => st.Id == id);
                if (s != null)
                {
                    Console.Write($"New name (leave blank to keep {s.Name}): ");
                    string name = Console.ReadLine();
                    if (!string.IsNullOrWhiteSpace(name)) s.Name = name;

                    Console.Write($"New age (current {s.Age}): ");
                    string ageInput = Console.ReadLine();
                    if (int.TryParse(ageInput, out int age)) s.Age = age;

                    Console.Write($"New department (leave blank to keep {s.Department}): ");
                    string dept = Console.ReadLine();
                    if (!string.IsNullOrWhiteSpace(dept)) s.Department = dept;

                    Console.Write($"New GPA (current {s.GPA}): ");
                    string gpaInput = Console.ReadLine();
                    if (double.TryParse(gpaInput, out double gpa)) s.GPA = gpa;

                    Console.WriteLine("Student information updated.");
                }
                else
                    Console.WriteLine("Student not found.");
            }
        }

        static void DeleteStudent()
        {
            Console.Write("Enter Student ID to delete: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var s = students.FirstOrDefault(st => st.Id == id);
                if (s != null)
                {
                    students.Remove(s);
                    Console.WriteLine("Student deleted.");
                }
                else
                    Console.WriteLine("Student not found.");
            }
        }

        static void SearchStudent()
        {
            Console.Write("Enter keyword to search (name or dept): ");
            string keyword = Console.ReadLine().ToLower();
            var results = students.Where(s => s.Name.ToLower().Contains(keyword) || s.Department.ToLower().Contains(keyword)).ToList();

            if (results.Count == 0)
            {
                Console.WriteLine("No matching students found.");
                return;
            }

            Console.WriteLine("\n--- Search Results ---");
            foreach (var s in results)
                Console.WriteLine($"ID: {s.Id} | Name: {s.Name} | Dept: {s.Department} | GPA: {s.GPA:F2}");
        }

        static void SortStudents()
        {
            Console.WriteLine("Sort by: 1. Name  2. GPA  3. Age");
            string option = Console.ReadLine();

            if (option == "1")
                students = students.OrderBy(s => s.Name).ToList();
            else if (option == "2")
                students = students.OrderByDescending(s => s.GPA).ToList();
            else if (option == "3")
                students = students.OrderBy(s => s.Age).ToList();
            else
                Console.WriteLine("Invalid option.");

            Console.WriteLine("Students sorted.");
        }

        static void FilterByDepartment()
        {
            Console.Write("Enter department to filter: ");
            string dept = Console.ReadLine().ToLower();

            var results = students.Where(s => s.Department.ToLower() == dept).ToList();

            if (results.Count == 0)
            {
                Console.WriteLine("No students found in this department.");
                return;
            }

            Console.WriteLine($"\n--- Students in {dept} ---");
            foreach (var s in results)
                Console.WriteLine($"ID: {s.Id} | {s.Name} | GPA: {s.GPA:F2}");
        }

        static void CalculateAverageGPA()
        {
            if (students.Count == 0)
            {
                Console.WriteLine("No students to calculate.");
                return;
            }

            double avg = students.Average(s => s.GPA);
            Console.WriteLine($"Average GPA of all students: {avg:F2}");
        }

        static void DeactivateStudent()
        {
            Console.Write("Enter Student ID to deactivate: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var s = students.FirstOrDefault(st => st.Id == id);
                if (s != null)
                {
                    s.Active = false;
                    Console.WriteLine("Student marked as inactive.");
                }
                else
                    Console.WriteLine("Student not found.");
            }
        }

        static void ShowActiveInactive()
        {
            int activeCount = students.Count(s => s.Active);
            int inactiveCount = students.Count(s => !s.Active);

            Console.WriteLine($"Active Students: {activeCount}");
            Console.WriteLine($"Inactive Students: {inactiveCount}");
        }
    }
}