using System;

class Loops {
    static void Main() {
        Console.Write("Enter a number to count up to: ");
        int n = int.Parse(Console.ReadLine());

        Console.WriteLine($"\nCounting from 0 to {n - 1}:");
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
                Console.WriteLine($"{i} is even");
            else
                Console.WriteLine($"{i} is odd");
        }

        Console.WriteLine("\nLoop finished!");
    }
}