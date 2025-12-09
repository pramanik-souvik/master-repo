package main

import (
	"fmt"
	"sort"
)

func main() {
	// --- Map Demo ---
	fmt.Println("📘 Student Marks Record:")
	marks := map[string]int{
		"Souvik": 90,
		"Bob":   82,
		"Pramanik": 95,
	}
	marks["Riaz"] = 88 // Add new entry
	delete(marks, "Bob") // Remove one

	for name, mark := range marks {
		fmt.Printf("%s → %d\n", name, mark)
	}

	// Sorting keys
	keys := make([]string, 0, len(marks))
	for k := range marks {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	fmt.Println("\nSorted Names:")
	for _, k := range keys {
		fmt.Printf("%s : %d\n", k, marks[k])
	}

	// --- Slice Demo ---
	fmt.Println("\nProgramming Languages List:")
	langs := []string{"Go", "Python", "Rust"}
	langs = append(langs, "C++", "JavaScript")

	for i, lang := range langs {
		fmt.Printf("%d. %s\n", i+1, lang)
	}

	fmt.Printf("\nTotal languages: %d\n", len(langs))
	fmt.Println("Top 3:", langs[:3])
}