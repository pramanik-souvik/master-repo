#import <Foundation/Foundation.h>

NSString* reverseString(NSString *str) {
    NSUInteger len = [str length];
    NSMutableString *reversed = [NSMutableString stringWithCapacity:len];
    while (len > 0) {
        [reversed appendFormat:@"%C", [str characterAtIndex:--len]];
    }
    return reversed;
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char input[100];
        NSLog(@"Enter your name: ");
        fgets(input, sizeof(input), stdin);
        
        // Remove newline character
        NSString *name = [NSString stringWithUTF8String:input];
        name = [name stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];
        
        // String manipulations
        NSLog(@"Original: %@", name);
        NSLog(@"Uppercase: %@", [name uppercaseString]);
        NSLog(@"Lowercase: %@", [name lowercaseString]);
        NSLog(@"Reversed: %@", reverseString(name));
        NSLog(@"Length: %lu", (unsigned long)[name length]);
        NSLog(@"First character: %@", [name substringToIndex:1]);
        NSLog(@"Last character: %@", [name substringFromIndex:[name length]-1]);
    }
    return 0;
}