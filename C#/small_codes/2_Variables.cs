using System;

class Variables {
    static void Main() {
        Console.Write("Enter an integer: ");
        int x = int.Parse(Console.ReadLine());
        Console.Write("Enter a decimal number: ");
        double y = double.Parse(Console.ReadLine());
        string language = "C#";

        double total = x + y;
        Console.WriteLine($"You entered {x} and {y}");
        Console.WriteLine($"Their sum is {total}");
        Console.WriteLine($"Keep learning {language}!");
    }
}