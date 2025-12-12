// File Organizer - Objective-C
#import <Foundation/Foundation.h>

NSDictionary *fileCategories() {
    return @{
        @"Images": @[@"jpg", @"jpeg", @"png", @"gif", @"bmp", @"tiff"],
        @"Documents": @[@"txt", @"pdf", @"doc", @"docx", @"xls", @"xlsx", @"ppt", @"pptx"],
        @"Audio": @[@"mp3", @"wav", @"aac", @"flac"],
        @"Videos": @[@"mp4", @"mov", @"avi", @"mkv"],
        @"Archives": @[@"zip", @"rar", @"tar", @"gz", @"7z"]
    };
}

NSString *categoryForExtension(NSString *ext) {
    NSDictionary *categories = fileCategories();
    for (NSString *category in categories) {
        NSArray *exts = categories[category];
        if ([exts containsObject:[ext lowercaseString]]) return category;
    }
    return @"Others";
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSFileManager *fm = [NSFileManager defaultManager];
        NSString *currentDir = [fm currentDirectoryPath];
        
        NSError *error = nil;
        NSArray *files = [fm contentsOfDirectoryAtPath:currentDir error:&error];
        if (error) {
            NSLog(@"Error reading directory: %@", [error localizedDescription]);
            return 1;
        }
        
        NSLog(@"Organizing files in directory: %@", currentDir);
        
        for (NSString *file in files) {
            BOOL isDir = NO;
            [fm fileExistsAtPath:file isDirectory:&isDir];
            if (isDir) continue; // Skip directories
            
            NSString *ext = [[file pathExtension] lowercaseString];
            NSString *category = categoryForExtension(ext);
            NSString *destDir = [currentDir stringByAppendingPathComponent:category];
            
            if (![fm fileExistsAtPath:destDir]) {
                [fm createDirectoryAtPath:destDir withIntermediateDirectories:YES attributes:nil error:&error];
                if (error) {
                    NSLog(@"Error creating directory %@: %@", destDir, [error localizedDescription]);
                    continue;
                }
            }
            
            NSString *destPath = [destDir stringByAppendingPathComponent:file];
            if (![fm moveItemAtPath:file toPath:destPath error:&error]) {
                NSLog(@"Failed to move %@: %@", file, [error localizedDescription]);
            } else {
                NSLog(@"Moved %@ -> %@", file, destDir);
            }
        }
        
        NSLog(@"File organization completed.");
    }
    return 0;
}