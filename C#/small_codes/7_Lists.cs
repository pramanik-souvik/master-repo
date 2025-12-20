using System;
using System.Collections.Generic;

class Lists {
    static void Main() {
        List<int> nums = new List<int> { 1, 2, 3 };

        Console.WriteLine("Original list:");
        PrintList(nums);

        Console.Write("Enter a number to add to the list: ");
        int newNum = int.Parse(Console.ReadLine());
        nums.Add(newNum);

        Console.WriteLine("\nUpdated list:");
        PrintList(nums);

        Console.WriteLine($"\nSum of all numbers: {SumList(nums)}");
    }

    static void PrintList(List<int> list) {
        foreach (var item in list)
            Console.WriteLine(item);
    }

    static int SumList(List<int> list) {
        int sum = 0;
        foreach (var item in list)
            sum += item;
        return sum;
    }
}