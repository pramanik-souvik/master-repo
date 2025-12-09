package main

import "fmt"

// Define a struct with methods
type Person struct {
	Name string
	Age  int
}

// Method to display formatted info
func (p Person) Introduce() {
	fmt.Printf("Hi, I'm %s and I'm %d years old.\n", p.Name, p.Age)
}

// Method to check if a person is an adult
func (p Person) IsAdult() bool {
	return p.Age >= 18
}

func main() {
	// Create multiple Person instances
	alice := Person{Name: "Souvik", Age: 23}
	bob := Person{Name: "Pramanik", Age: 14}


	// Display info using struct methods
	alice.Introduce()
	bob.Introduce()

	// Logic based on struct data
	if alice.IsAdult() {
		fmt.Printf("%s is an adult.\n", alice.Name)
	}
	if !bob.IsAdult() {
		fmt.Printf("%s is not an adult yet.\n", bob.Name)
	}

	// Anonymous struct for quick demo
	guest := struct {
		Name string
		Role string
	}{
		Name: "Charlie",
		Role: "Visitor",
	}
	fmt.Printf("Guest Info: %s (%s)\n", guest.Name, guest.Role)
}