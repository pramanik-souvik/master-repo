#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"=== File Read/Write Demo ===");

        char inputBuffer[256];
        NSLog(@"Enter some text to write to file:");
        fgets(inputBuffer, 256, stdin);
        NSString *userText = [NSString stringWithUTF8String:inputBuffer];
        userText = [userText stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];

        // File path
        NSString *filePath = @"user_output.txt";

        // Ask if user wants to append or overwrite
        NSLog(@"Do you want to append to the file? (y/n):");
        fgets(inputBuffer, 10, stdin);
        NSString *choice = [NSString stringWithUTF8String:inputBuffer];
        choice = [choice stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];

        NSFileHandle *fileHandle = [NSFileHandle fileHandleForWritingAtPath:filePath];
        NSError *error = nil;

        if ([choice.lowercaseString isEqualToString:@"y"] && fileHandle) {
            [fileHandle seekToEndOfFile];
            [fileHandle writeData:[userText dataUsingEncoding:NSUTF8StringEncoding]];
            [fileHandle writeData:[@"\n" dataUsingEncoding:NSUTF8StringEncoding]];
            [fileHandle closeFile];
            NSLog(@"Text appended to %@", filePath);
        } else {
            [userText writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:&error];
            if (error) {
                NSLog(@"Error writing file: %@", error.localizedDescription);
            } else {
                NSLog(@"Text written to %@", filePath);
            }
        }

        // Read and display file contents
        NSString *readText = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:&error];
        if (error) {
            NSLog(@"Error reading file: %@", error.localizedDescription);
        } else {
            NSLog(@"=== File Contents ===\n%@", readText);
        }
    }
    return 0;
}