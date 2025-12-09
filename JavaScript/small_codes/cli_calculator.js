// Basic CLI Calculator in Node.js
const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

readline.question("Enter first number: ", num1 => {
  readline.question("Enter operator (+ - * /): ", op => {
    readline.question("Enter second number: ", num2 => {
      num1 = parseFloat(num1);
      num2 = parseFloat(num2);
      let result;
      switch(op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        default: result = "Invalid operator";
      }
      console.log(`Result: ${result}`);
      readline.close();
    });
  });
});