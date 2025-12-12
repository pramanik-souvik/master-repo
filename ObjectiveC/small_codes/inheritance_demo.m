#import <Foundation/Foundation.h>

@interface Animal : NSObject
@property (nonatomic, strong) NSString *name;
- (instancetype)initWithName:(NSString *)name;
- (void)speak;
@end

@implementation Animal
- (instancetype)initWithName:(NSString *)name {
    if (self = [super init]) {
        _name = name;
    }
    return self;
}
- (void)speak {
    NSLog(@"%@ makes a sound.", self.name);
}
@end

@interface Dog : Animal
@end
@implementation Dog
- (void)speak {
    NSLog(@"%@ barks!", self.name);
}
@end

@interface Cat : Animal
@end
@implementation Cat
- (void)speak {
    NSLog(@"%@ meows!", self.name);
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char inputName[50];
        NSLog(@"Enter the animal's name:");
        fgets(inputName, 50, stdin);
        NSString *name = [NSString stringWithUTF8String:inputName];
        name = [name stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];

        NSLog(@"Choose animal type (dog/cat/animal):");
        char typeInput[20];
        fgets(typeInput, 20, stdin);
        NSString *type = [[NSString stringWithUTF8String:typeInput] stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];

        Animal *pet;
        if ([type.lowercaseString isEqualToString:@"dog"]) {
            pet = [[Dog alloc] initWithName:name];
        } else if ([type.lowercaseString isEqualToString:@"cat"]) {
            pet = [[Cat alloc] initWithName:name];
        } else {
            pet = [[Animal alloc] initWithName:name];
        }

        [pet speak];
    }
    return 0;
}