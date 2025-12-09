// Array utilities demo
const numbers = [1, 2, 3, 4, 5];

const doubled = numbers.map(n => n * 2);         // multiply array elements with 2
const evens   = numbers.filter(n => n % 2 === 0); // keep only even
const sum     = numbers.reduce((a, b) => a + b); // summation of the array elements

console.log("Original:", numbers);
console.log("Doubled :", doubled);
console.log("Evens   :", evens);
console.log("Sum     :", sum);