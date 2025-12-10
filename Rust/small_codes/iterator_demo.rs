// Iterator Demo - Advanced
fn main() {
    let numbers = vec![1, 2, 3, 4, 5, 6];

    // Double the numbers and sum only the even results
    let sum_even_doubles: i32 = numbers
        .iter()
        .map(|x| x * 2)
        .filter(|x| x % 4 == 0)
        .sum();
    println!("Sum of doubled even numbers divisible by 4: {}", sum_even_doubles);

    // Enumerate and display
    for (index, value) in numbers.iter().enumerate() {
        println!("Index {}: Value {}", index, value);
    }

    // Use fold to calculate product of all numbers
    let product: i32 = numbers.iter().fold(1, |acc, &x| acc * x);
    println!("Product of all numbers: {}", product);
}