using System;
using System.IO;

class FileDemo {
    static void Main() {
        string fileName = "demo.txt";

        Console.WriteLine("=== Simple File I/O Demo ===");

        // Writing to the file
        Console.Write("Enter some text to save in the file: ");
        string content = Console.ReadLine();
        File.WriteAllText(fileName, content);
        Console.WriteLine($"Text saved to {fileName}.");

        // Reading from the file
        Console.WriteLine("\nReading from the file:");
        string readContent = File.ReadAllText(fileName);
        Console.WriteLine(readContent);

        // Appending to the file
        Console.Write("\nEnter more text to append: ");
        string appendText = Console.ReadLine();
        File.AppendAllText(fileName, "\n" + appendText);
        Console.WriteLine("Text appended.");

        // Reading updated content
        Console.WriteLine("\nUpdated file content:");
        Console.WriteLine(File.ReadAllText(fileName));

        // Optional: Delete the file
        Console.Write("\nDo you want to delete the file? (y/n): ");
        string deleteChoice = Console.ReadLine().ToLower();
        if (deleteChoice == "y") {
            File.Delete(fileName);
            Console.WriteLine("File deleted.");
        } else {
            Console.WriteLine("File kept.");
        }
    }
}
