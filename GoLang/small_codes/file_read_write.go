package main

import (
	"bufio"
	"fmt"
	"os"
	"time"
)

func main() {
	filename := "notes.txt"
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("=== Simple Go File Writer ===")
	fmt.Print("Enter a line to save: ")
	text, _ := reader.ReadString('\n')

	// Append mode, create if missing
	f, err := os.OpenFile(filename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer f.Close()

	if _, err := f.WriteString(time.Now().Format("2006-01-02 15:04:05") + " - " + text); err != nil {
		fmt.Println("Error writing to file:", err)
		return
	}

	fmt.Println("\nNote saved successfully!\n")

	// Display file details
	info, _ := os.Stat(filename)
	fmt.Printf("File: %s\nSize: %d bytes\nLast Modified: %s\n\n",
		info.Name(), info.Size(), info.ModTime().Format("Jan 2, 2006 15:04:05"))

	// Read entire file content
	data, _ := os.ReadFile(filename)
	fmt.Println("=== File Contents ===")
	fmt.Println(string(data))
}
