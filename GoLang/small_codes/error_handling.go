package main
import (
    "errors"
    "fmt"
)

func divide(a, b float64) (float64, error) {
    if b == 0 {
        return 0, errors.New("division by zero")
    }
    return a / b, nil
}

func main() {
    res, err := divide(10, 5)
    if err != nil {
        fmt.Println("Error:", err)
    } else {
        fmt.Println("Result:", res)
    }

    res1, err1 := divide(10, 0)
    if err1 != nil {
        fmt.Println("Error:", err1)
    } else {
        fmt.Println("Result:", res1)
    }
}