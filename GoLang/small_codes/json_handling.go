package main

import (
	"encoding/json"
	"fmt"
	"os"
	"strings"
)

type User struct {
	Name  string `json:"name"`
	Age   int    `json:"age"`
	Email string `json:"email"`
}

func main() {
	var u User

	fmt.Print("Enter name: ")
	fmt.Scanln(&u.Name)

	fmt.Print("Enter age: ")
	fmt.Scanln(&u.Age)

	fmt.Print("Enter email: ")
	fmt.Scanln(&u.Email)

	// Marshal with indentation for readability
	jsonData, err := json.MarshalIndent(u, "", "  ")
	if err != nil {
		fmt.Println("Error encoding JSON:", err)
		return
	}

	// Save JSON to a file
	err = os.WriteFile("user.json", jsonData, 0644)
	if err != nil {
		fmt.Println("Error writing file:", err)
		return
	}

	fmt.Println("\nJSON saved to user.json:")
	fmt.Println(string(jsonData))

	// Read JSON back
	data, _ := os.ReadFile("user.json")
	var u2 User
	json.Unmarshal(data, &u2)

	fmt.Println("\nDecoded from file:")
	fmt.Printf("Name: %s\nAge: %d\nEmail: %s\n", u2.Name, u2.Age, strings.ToLower(u2.Email))
}