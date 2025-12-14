using System;

class Conditionals {
    static void Main() {
        Console.Write("Enter a number: ");
        int n = int.Parse(Console.ReadLine());

        if (n > 0 && n % 2 == 0)
            Console.WriteLine($"{n} is Positive and Even");
        else if (n > 0 && n % 2 != 0)
            Console.WriteLine($"{n} is Positive and Odd");
        else if (n < 0)
            Console.WriteLine($"{n} is Negative");
        else
            Console.WriteLine("The number is Zero");
    }
}