package main

import (
	"bufio"
	"crypto/md5"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"os"
	"strings"
)

const dataFile = "urls.json"

var urlStore = make(map[string]string) // shortURL -> originalURL

// Load URLs from JSON file
func loadURLs() {
	file, err := os.Open(dataFile)
	if err != nil {
		if os.IsNotExist(err) {
			return // No file yet, start fresh
		}
		fmt.Println("Error loading URLs:", err)
		return
	}
	defer file.Close()

	err = json.NewDecoder(file).Decode(&urlStore)
	if err != nil {
		fmt.Println("Error decoding URL data:", err)
	}
}

// Save URLs to JSON file
func saveURLs() {
	file, err := os.Create(dataFile)
	if err != nil {
		fmt.Println("Error saving URLs:", err)
		return
	}
	defer file.Close()

	err = json.NewEncoder(file).Encode(urlStore)
	if err != nil {
		fmt.Println("Error encoding URL data:", err)
	}
}

// Shorten a URL
func shortenURL(url string) string {
	hash := md5.Sum([]byte(url))
	return hex.EncodeToString(hash[:])[:8]
}

// Add a new URL
func addURL(reader *bufio.Reader) {
	fmt.Print("Enter the URL to shorten: ")
	url, _ := reader.ReadString('\n')
	url = strings.TrimSpace(url)
	if url == "" {
		fmt.Println("URL cannot be empty.")
		return
	}

	short := shortenURL(url)
	urlStore[short] = url
	saveURLs()
	fmt.Printf("Shortened URL: %s -> %s\n", short, url)
}

// Lookup original URL
func lookupURL(reader *bufio.Reader) {
	fmt.Print("Enter shortened URL: ")
	short, _ := reader.ReadString('\n')
	short = strings.TrimSpace(short)

	original, exists := urlStore[short]
	if exists {
		fmt.Printf("Original URL: %s\n", original)
	} else {
		fmt.Println("No URL found for this short code.")
	}
}

// View all stored URLs
func viewAll() {
	if len(urlStore) == 0 {
		fmt.Println("No URLs shortened yet.")
		return
	}
	fmt.Println("\nAll shortened URLs:")
	for short, original := range urlStore {
		fmt.Printf("%s -> %s\n", short, original)
	}
}

func main() {
	loadURLs()
	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("\n=== Persistent CLI URL Shortener ===")
		fmt.Println("1. Shorten a new URL")
		fmt.Println("2. Lookup original URL")
		fmt.Println("3. View all shortened URLs")
		fmt.Println("4. Exit")
		fmt.Print("Enter choice: ")

		choice, _ := reader.ReadString('\n')
		choice = strings.TrimSpace(choice)

		switch choice {
		case "1":
			addURL(reader)
		case "2":
			lookupURL(reader)
		case "3":
			viewAll()
		case "4":
			fmt.Println("Exiting... Goodbye!")
			return
		default:
			fmt.Println("Invalid choice. Try again.")
		}
	}
}