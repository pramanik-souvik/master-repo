package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func task(name string, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Printf("%s started\n", name)
	for i := 1; i <= 3; i++ {
		fmt.Printf("%s → step %d\n", name, i)
		time.Sleep(time.Duration(rand.Intn(500)+300) * time.Millisecond)
	}
	fmt.Printf("%s finished\n\n", name)
}

func main() {
	rand.Seed(time.Now().UnixNano())
	var wg sync.WaitGroup

	tasks := []string{"Download Data", "Process Image", "Send Email", "Save to Database"}

	fmt.Println("=== Concurrent Task Runner ===\n")

	for _, t := range tasks {
		wg.Add(1)
		go task(t, &wg)
	}

	wg.Wait()
	fmt.Println("All tasks completed successfully!")
}