#import <Foundation/Foundation.h>

@interface Calculator : NSObject
- (int)addInt:(int)a with:(int)b;
- (float)addFloat:(float)a with:(float)b;
- (NSString *)addString:(NSString *)a with:(NSString *)b;
@end

@implementation Calculator
- (int)addInt:(int)a with:(int)b {
    return a + b;
}

- (float)addFloat:(float)a with:(float)b {
    return a + b;
}

- (NSString *)addString:(NSString *)a with:(NSString *)b {
    return [a stringByAppendingString:b];
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        Calculator *calc = [[Calculator alloc] init];

        NSLog(@"Integer add: %d", [calc addInt:5 with:7]);
        NSLog(@"Float add: %.2f", [calc addFloat:3.5 with:2.7]);
        NSLog(@"String add: %@", [calc addString:@"Hello, " with:@"World!"]);
    }
    return 0;
}