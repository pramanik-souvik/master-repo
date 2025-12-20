using System;

class Person
{
    public string Name;
    public int Age;

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void SayHi()
    {
        Console.WriteLine($"Hi, my name is {Name} and I am {Age} years old.");
    }

    public void CelebrateBirthday()
    {
        Age++;
        Console.WriteLine($"Happy Birthday, {Name}! You are now {Age} years old.");
    }

    static void Main()
    {
        Console.Write("Enter your name: ");
        string name = Console.ReadLine();

        Console.Write("Enter your age: ");
        int age = int.Parse(Console.ReadLine());

        Person p = new Person(name, age);
        p.SayHi();

        Console.Write("Do you want to celebrate a birthday? (y/n): ");
        string choice = Console.ReadLine().ToLower();
        if (choice == "y") p.CelebrateBirthday();
    }
}