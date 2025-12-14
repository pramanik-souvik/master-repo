using System;

class Strings {
    static void Main() {
        Console.Write("Enter a string: ");
        string s = Console.ReadLine();

        Console.WriteLine($"Uppercase: {s.ToUpper()}");
        Console.WriteLine($"Lowercase: {s.ToLower()}");
        Console.WriteLine($"Length: {s.Length}");
        Console.WriteLine($"Reversed: {ReverseString(s)}");
    }

    static string ReverseString(string str) {
        char[] chars = str.ToCharArray();
        Array.Reverse(chars);
        return new string(chars);
    }
}