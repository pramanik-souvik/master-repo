package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func worker(id int, jobs <-chan int, results chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	for j := range jobs {
		fmt.Printf("[%s] Worker %d started job %d\n", time.Now().Format("15:04:05"), id, j)
		// Simulate variable processing time
		time.Sleep(time.Duration(rand.Intn(1000)+500) * time.Millisecond)
		fmt.Printf("[%s] Worker %d finished job %d\n", time.Now().Format("15:04:05"), id, j)
		results <- j * 2
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())
	jobs := make(chan int, 10)
	results := make(chan int, 10)

	var wg sync.WaitGroup
	numWorkers := 3
	numJobs := 7

	// Start workers
	for w := 1; w <= numWorkers; w++ {
		wg.Add(1)
		go worker(w, jobs, results, &wg)
	}

	// Send jobs
	for j := 1; j <= numJobs; j++ {
		jobs <- j
	}
	close(jobs)

	// Wait for all workers to finish
	go func() {
		wg.Wait()
		close(results)
	}()

	// Collect results
	fmt.Println("\nResults:")
	for res := range results {
		fmt.Println(res)
	}

	fmt.Println("\nAll jobs completed.")
}