package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Password struct {
	Site     string
	Username string
	Password string
}

var store []Password

func main() {
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Println("\n=== CLI Password Manager ===")
		fmt.Println("1. Add new credential")
		fmt.Println("2. View saved credentials")
		fmt.Println("3. Search credential by site")
		fmt.Println("4. Exit")
		fmt.Print("Enter choice: ")

		choice, _ := reader.ReadString('\n')
		choice = strings.TrimSpace(choice)

		switch choice {
		case "1":
			addCredential(reader)
		case "2":
			viewCredentials()
		case "3":
			searchCredential(reader)
		case "4":
			fmt.Println("Exiting... Goodbye!")
			return
		default:
			fmt.Println("Invalid choice. Try again.")
		}
	}
}

func addCredential(reader *bufio.Reader) {
	fmt.Print("Enter site name: ")
	site, _ := reader.ReadString('\n')
	site = strings.TrimSpace(site)

	fmt.Print("Enter username: ")
	username, _ := reader.ReadString('\n')
	username = strings.TrimSpace(username)

	fmt.Print("Enter password: ")
	password, _ := reader.ReadString('\n')
	password = strings.TrimSpace(password)

	store = append(store, Password{Site: site, Username: username, Password: password})
	fmt.Println("Credential added successfully!")
}

func viewCredentials() {
	if len(store) == 0 {
		fmt.Println("No credentials saved yet.")
		return
	}
	fmt.Println("\nSaved Credentials:")
	for i, p := range store {
		fmt.Printf("%d. Site: %s | Username: %s | Password: %s\n", i+1, p.Site, p.Username, p.Password)
	}
}

func searchCredential(reader *bufio.Reader) {
	fmt.Print("Enter site name to search: ")
	site, _ := reader.ReadString('\n')
	site = strings.TrimSpace(site)

	found := false
	for _, p := range store {
		if strings.EqualFold(p.Site, site) {
			fmt.Printf("Found: Site: %s | Username: %s | Password: %s\n", p.Site, p.Username, p.Password)
			found = true
		}
	}
	if !found {
		fmt.Println("No credentials found for that site.")
	}
}