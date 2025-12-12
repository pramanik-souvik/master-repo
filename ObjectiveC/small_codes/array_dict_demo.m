#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Array example
        NSArray *arr = @[@"Apple", @"Banana", @"Cherry"];
        NSLog(@"Array: %@", arr);
        
        // Dictionary example
        NSDictionary *dict = @{@"Name": @"Alice", @"Age": @25};
        NSLog(@"Dictionary: %@", dict);
    }
    return 0;
}