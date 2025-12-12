#import <Foundation/Foundation.h>

// Category declaration
@interface NSString (Reverse)
- (NSString *)reverseString;
@end

// Category implementation
@implementation NSString (Reverse)
- (NSString *)reverseString {
    NSUInteger len = [self length];
    NSMutableString *reversed = [NSMutableString stringWithCapacity:len];
    while (len > 0) {
        [reversed appendFormat:@"%C", [self characterAtIndex:--len]];
    }
    return reversed;
}
@end

// Main function
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *original = @"ObjectiveC";
        NSString *reversed = [original reverseString];
        NSLog(@"Original: %@", original);
        NSLog(@"Reversed: %@", reversed);
    }
    return 0;
}