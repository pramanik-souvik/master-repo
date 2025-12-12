#import <Foundation/Foundation.h>

@interface Hello : NSObject
- (void)sayHelloTo:(NSString *)name;
@end

@implementation Hello
- (void)sayHelloTo:(NSString *)name {
    NSLog(@"Hello, %@! Welcome to Objective-C.", name);
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char input[100];
        NSLog(@"Enter your name:");
        fgets(input, 100, stdin);
        NSString *name = [NSString stringWithUTF8String:input];
        name = [name stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];

        Hello *greeting = [[Hello alloc] init];
        [greeting sayHelloTo:name];
    }
    return 0;
}