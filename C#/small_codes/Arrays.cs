using System;

class Arrays {
    static void Main() {
        Console.Write("How many numbers do you want to enter? ");
        int n = int.Parse(Console.ReadLine());

        int[] arr = new int[n];

        for (int i = 0; i < n; i++) {
            Console.Write($"Enter number {i + 1}: ");
            arr[i] = int.Parse(Console.ReadLine());
        }

        Console.WriteLine("\nYour numbers are:");
        foreach (int num in arr)
            Console.WriteLine($"- {num}");

        Console.WriteLine($"\nSum of all numbers: {Sum(arr)}");
    }

    static int Sum(int[] numbers) {
        int total = 0;
        foreach (int num in numbers) total += num;
        return total;
    }
}
