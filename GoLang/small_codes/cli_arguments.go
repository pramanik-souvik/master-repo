package main

import (
    "fmt"
    "os"
    "strconv"
    "strings"
)

func main() {
    args := os.Args[1:]

    if len(args) == 0 {
        fmt.Println("Usage:")
        fmt.Println("  greet [name]          → Greets a user")
        fmt.Println("  add [a] [b]           → Adds two numbers")
        fmt.Println("  reverse [text]        → Reverses a string")
        fmt.Println("  shout [message]       → Prints message in uppercase")
        return
    }

    command := args[0]

    switch command {
    case "greet":
        if len(args) < 2 {
            fmt.Println("Please provide a name.")
            return
        }
        fmt.Printf("Hello, %s!\n", args[1])

    case "add":
        if len(args) < 3 {
            fmt.Println("Usage: add [num1] [num2]")
            return
        }
        a, _ := strconv.ParseFloat(args[1], 64)
        b, _ := strconv.ParseFloat(args[2], 64)
        fmt.Printf("Sum: %.2f\n", a+b)

    case "reverse":
        if len(args) < 2 {
            fmt.Println("Usage: reverse [text]")
            return
        }
        input := args[1]
        reversed := ""
        for _, r := range input {
            reversed = string(r) + reversed
        }
        fmt.Println("Reversed:", reversed)

    case "shout":
        if len(args) < 2 {
            fmt.Println("Usage: shout [message]")
            return
        }
        fmt.Println(strings.ToUpper(strings.Join(args[1:], " ")))

    default:
        fmt.Printf("Unknown command: '%s'\n", command)
    }
}