using System;

namespace ScientificCalculatorProject
{
    class ScientificCalculator
    {
        static void Main()
        {
            Console.Title = "Scientific Calculator";
            bool running = true;

            while (running)
            {
                ShowMenu();
                Console.Write("Choose an option: ");
                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1": BasicOperations("+"); break;
                    case "2": BasicOperations("-"); break;
                    case "3": BasicOperations("*"); break;
                    case "4": BasicOperations("/"); break;
                    case "5": BasicOperations("^"); break;
                    case "6": SquareRoot(); break;
                    case "7": Trigonometry(); break;
                    case "8": Logarithms(); break;
                    case "9": Factorial(); break;
                    case "10": Percentage(); break;
                    case "0": running = false; Console.WriteLine("Exiting..."); break;
                    default: Console.WriteLine("Invalid choice."); break;
                }

                if (running)
                {
                    Console.WriteLine("\nPress any key to continue...");
                    Console.ReadKey();
                    Console.Clear();
                }
            }
        }

        static void ShowMenu()
        {
            Console.WriteLine("========== SCIENTIFIC CALCULATOR ==========");
            Console.WriteLine("1. Addition");
            Console.WriteLine("2. Subtraction");
            Console.WriteLine("3. Multiplication");
            Console.WriteLine("4. Division");
            Console.WriteLine("5. Power");
            Console.WriteLine("6. Square Root");
            Console.WriteLine("7. Trigonometry (sin, cos, tan)");
            Console.WriteLine("8. Logarithms (ln, log10)");
            Console.WriteLine("9. Factorial");
            Console.WriteLine("10. Percentage");
            Console.WriteLine("0. Exit");
            Console.WriteLine("===========================================");
        }

        static double GetNumber(string prompt)
        {
            Console.Write(prompt);
            while (true)
            {
                if (double.TryParse(Console.ReadLine(), out double number))
                    return number;
                Console.Write("Invalid input. Try again: ");
            }
        }

        static void BasicOperations(string op)
        {
            double a = GetNumber("Enter first number: ");
            double b = GetNumber("Enter second number: ");
            double result = 0;

            switch (op)
            {
                case "+": result = a + b; break;
                case "-": result = a - b; break;
                case "*": result = a * b; break;
                case "/": result = b != 0 ? a / b : double.NaN; break;
                case "^": result = Math.Pow(a, b); break;
            }

            Console.WriteLine($"Result: {a} {op} {b} = {result}");
        }

        static void SquareRoot()
        {
            double a = GetNumber("Enter number: ");
            if (a < 0)
                Console.WriteLine("Cannot calculate square root of a negative number.");
            else
                Console.WriteLine($"√{a} = {Math.Sqrt(a)}");
        }

        static void Trigonometry()
        {
            Console.Write("Choose function (sin / cos / tan): ");
            string func = Console.ReadLine().ToLower();
            double angle = GetNumber("Enter angle in degrees: ");
            double radians = angle * (Math.PI / 180);
            double result = 0;

            switch (func)
            {
                case "sin": result = Math.Sin(radians); break;
                case "cos": result = Math.Cos(radians); break;
                case "tan": result = Math.Tan(radians); break;
                default: Console.WriteLine("Invalid trig function."); return;
            }

            Console.WriteLine($"{func}({angle}°) = {result}");
        }

        static void Logarithms()
        {
            double a = GetNumber("Enter positive number: ");
            if (a <= 0)
            {
                Console.WriteLine("Logarithm undefined for zero or negative values.");
                return;
            }

            Console.Write("Choose log type (ln / log10): ");
            string type = Console.ReadLine().ToLower();
            double result = 0;

            switch (type)
            {
                case "ln": result = Math.Log(a); break;
                case "log10": result = Math.Log10(a); break;
                default: Console.WriteLine("Invalid log type."); return;
            }

            Console.WriteLine($"{type}({a}) = {result}");
        }

        static void Factorial()
        {
            int n;
            while (true)
            {
                Console.Write("Enter a non-negative integer: ");
                if (int.TryParse(Console.ReadLine(), out n) && n >= 0) break;
                Console.WriteLine("Invalid input.");
            }

            long result = 1;
            for (int i = 1; i <= n; i++)
                result *= i;

            Console.WriteLine($"{n}! = {result}");
        }

        static void Percentage()
        {
            double total = GetNumber("Enter total value: ");
            double percent = GetNumber("Enter percentage: ");
            Console.WriteLine($"{percent}% of {total} = {(total * percent) / 100}");
        }
    }
}