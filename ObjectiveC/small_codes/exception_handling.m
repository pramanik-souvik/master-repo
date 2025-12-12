#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"=== Exception Handling Demo ===");

        // Array exception
        @try {
            NSArray *arr = @[@"Apple", @"Banana", @"Cherry"];
            NSLog(@"Accessing element 5: %@", arr[5]); // Out of bounds
        }
        @catch (NSException *e) {
            NSLog(@"Array Exception: %@", e.reason);
        }
        @finally {
            NSLog(@"Finished array check.\n");
        }

        // Dictionary exception
        @try {
            NSDictionary *dict = @{@"name": @"Alice", @"age": @25};
            NSLog(@"Accessing missing key: %@", dict[@"address"]); // nil value
            if (!dict[@"address"]) {
                @throw [NSException exceptionWithName:@"MissingKeyException"
                                               reason:@"Key 'address' not found in dictionary"
                                             userInfo:nil];
            }
        }
        @catch (NSException *e) {
            NSLog(@"Dictionary Exception: %@", e.reason);
        }
        @finally {
            NSLog(@"Finished dictionary check.\n");
        }

        NSLog(@"All checks complete.");
    }
    return 0;
}