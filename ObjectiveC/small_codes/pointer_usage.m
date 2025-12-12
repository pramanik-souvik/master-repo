#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Basic pointer
        int a = 10;
        int *ptr = &a;
        NSLog(@"Original value: %d, Address: %p", *ptr, ptr);
        
        // Modify value via pointer
        *ptr = 20;
        NSLog(@"Modified value via pointer: %d", a);
        
        // Pointer with array
        int arr[3] = {1, 2, 3};
        int *arrPtr = arr;
        for (int i = 0; i < 3; i++) {
            NSLog(@"arr[%d] = %d, Address: %p", i, *(arrPtr + i), (arrPtr + i));
        }
    }
    return 0;
}