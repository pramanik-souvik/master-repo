package main
import (
    "fmt"
    "time"
)

func main() {
    ch := make(chan string)

    // Start multiple goroutines sending messages
    for i := 1; i <= 3; i++ {
        go func(id int) {
            time.Sleep(time.Duration(id) * 500 * time.Millisecond)
            ch <- fmt.Sprintf("Message %d from Goroutine %d", id, id)
        }(i)
    }

    // Receive messages
    for i := 1; i <= 3; i++ {
        fmt.Println(<-ch)
    }

    fmt.Println("All goroutines have sent their messages!")
}