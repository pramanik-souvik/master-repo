#import <Foundation/Foundation.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char input[100];
        double num1, num2, result = 0;
        int choice;

        NSLog(@"=== CLI Calculator ===");

        // Get first number
        NSLog(@"Enter first number: ");
        fgets(input, sizeof(input), stdin);
        num1 = atof(input);

        // Get second number
        NSLog(@"Enter second number: ");
        fgets(input, sizeof(input), stdin);
        num2 = atof(input);

        // Display menu
        NSLog(@"\nSelect operation:");
        NSLog(@"1. Addition (+)");
        NSLog(@"2. Subtraction (-)");
        NSLog(@"3. Multiplication (*)");
        NSLog(@"4. Division (/)");
        NSLog(@"5. Modulo (%%)");
        NSLog(@"6. Power (^)");
        NSLog(@"7. Percentage of first number (%%)");

        NSLog(@"\nEnter choice (1-7): ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1: result = num1 + num2; NSLog(@"Result: %.2f", result); break;
            case 2: result = num1 - num2; NSLog(@"Result: %.2f", result); break;
            case 3: result = num1 * num2; NSLog(@"Result: %.2f", result); break;
            case 4: 
                if (num2 != 0) result = num1 / num2; 
                else { NSLog(@"Error: Division by zero!"); return 1; }
                NSLog(@"Result: %.2f", result); 
                break;
            case 5: 
                if ((int)num2 != 0) result = (int)num1 % (int)num2; 
                else { NSLog(@"Error: Division by zero!"); return 1; }
                NSLog(@"Result: %.0f", result); 
                break;
            case 6: result = pow(num1, num2); NSLog(@"Result: %.2f", result); break;
            case 7: result = (num1 * num2) / 100; NSLog(@"Result: %.2f", result); break;
            default: NSLog(@"Invalid choice!"); break;
        }

        NSLog(@"Calculation complete.");
    }
    return 0;
}