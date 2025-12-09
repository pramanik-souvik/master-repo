package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"
)

func main() {
	fmt.Print("Enter a URL (default: https://example.com): ")
	var url string
	fmt.Scanln(&url)
	if strings.TrimSpace(url) == "" {
		url = "https://example.com"
	}

	resp, err := http.Get(url)
	if err != nil {
		fmt.Println("Error fetching URL:", err)
		os.Exit(1)
	}
	defer resp.Body.Close()

	body, _ := io.ReadAll(resp.Body)
	preview := string(body)
	if len(preview) > 200 {
		preview = preview[:200] + "..."
	}

	fmt.Println("\n=== HTTP GET Result ===")
	fmt.Println("URL:", url)
	fmt.Println("Status:", resp.Status)
	fmt.Println("Content-Type:", resp.Header.Get("Content-Type"))
	fmt.Println("Body Preview:\n", preview)
}