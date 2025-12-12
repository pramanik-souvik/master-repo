// memory_management.m
#import <Foundation/Foundation.h>

// Demo class
@interface DemoObject : NSObject
@property (nonatomic, strong) NSString *name;
- (instancetype)initWithName:(NSString *)name;
@end

@implementation DemoObject
- (instancetype)initWithName:(NSString *)name {
    self = [super init];
    if (self) {
        _name = name;
        NSLog(@"DemoObject '%@' initialized", _name);
    }
    return self;
}

- (void)dealloc {
    NSLog(@"DemoObject '%@' deallocated", _name);
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"=== Memory Management Demo ===");
        
        // Strong reference
        DemoObject *strongObj = [[DemoObject alloc] initWithName:@"StrongObj"];
        
        // Weak reference
        __weak DemoObject *weakObj = strongObj;
        NSLog(@"Weak reference points to: %@", weakObj.name);
        
        // Releasing strong reference (ARC handles this automatically)
        strongObj = nil;
        
        if (!weakObj) {
            NSLog(@"Weak reference is now nil (object deallocated)");
        }
    }
    return 0;
}