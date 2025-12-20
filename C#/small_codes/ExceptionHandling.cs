using System;

class ExceptionDemo {
    static void Main() {
        try {
            Console.Write("Enter a number to divide 100 by: ");
            int divisor = int.Parse(Console.ReadLine());
            int result = 100 / divisor;
            Console.WriteLine($"100 ÷ {divisor} = {result}");
        }
        catch (DivideByZeroException) {
            Console.WriteLine("Error: Cannot divide by zero!");
        }
        catch (FormatException) {
            Console.WriteLine("Error: Please enter a valid integer.");
        }
        catch (Exception e) {
            Console.WriteLine($"Unexpected error: {e.Message}");
        }
        finally {
            Console.WriteLine("Operation completed.");
        }
    }
}
