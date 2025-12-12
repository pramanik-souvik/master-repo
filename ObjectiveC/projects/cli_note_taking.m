#import <Foundation/Foundation.h>

#define NOTES_FILE @"notes.json"

NSMutableArray *loadNotes() {
    if ([[NSFileManager defaultManager] fileExistsAtPath:NOTES_FILE]) {
        NSData *data = [NSData dataWithContentsOfFile:NOTES_FILE];
        NSError *error;
        NSArray *arr = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
        if (!error && arr) return [arr mutableCopy];
    }
    return [NSMutableArray array];
}

void saveNotes(NSMutableArray *notes) {
    NSError *error;
    NSData *data = [NSJSONSerialization dataWithJSONObject:notes options:NSJSONWritingPrettyPrinted error:&error];
    if (!error) [data writeToFile:NOTES_FILE atomically:YES];
}

void listNotes(NSMutableArray *notes) {
    if ([notes count] == 0) {
        NSLog(@"No notes available.");
        return;
    }
    NSLog(@"\n=== Notes List ===");
    [notes enumerateObjectsUsingBlock:^(NSString *note, NSUInteger idx, BOOL *stop) {
        NSLog(@"%lu: %@", idx+1, note);
    }];
}

void addNote(NSMutableArray *notes) {
    NSLog(@"Enter new note:");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);
    NSString *note = [[NSString stringWithUTF8String:buffer] stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    if ([note length] > 0) {
        [notes addObject:note];
        saveNotes(notes);
        NSLog(@"Note added!");
    } else {
        NSLog(@"Empty note not added.");
    }
}

void deleteNote(NSMutableArray *notes) {
    listNotes(notes);
    if ([notes count] == 0) return;
    
    NSLog(@"Enter note number to delete:");
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    NSInteger idx = atoi(buffer) - 1;
    if (idx >= 0 && idx < [notes count]) {
        NSLog(@"Deleting note: %@", notes[idx]);
        [notes removeObjectAtIndex:idx];
        saveNotes(notes);
        NSLog(@"Note deleted.");
    } else {
        NSLog(@"Invalid index.");
    }
}

void searchNotes(NSMutableArray *notes) {
    NSLog(@"Enter search keyword:");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stdin);
    NSString *keyword = [[NSString stringWithUTF8String:buffer] stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    if ([keyword length] == 0) return;
    
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF CONTAINS[cd] %@", keyword];
    NSArray *results = [notes filteredArrayUsingPredicate:predicate];
    
    if ([results count] == 0) {
        NSLog(@"No notes found with '%@'", keyword);
    } else {
        NSLog(@"=== Search Results ===");
        [results enumerateObjectsUsingBlock:^(NSString *note, NSUInteger idx, BOOL *stop) {
            NSLog(@"%lu: %@", idx+1, note);
        }];
    }
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray *notes = loadNotes();
        BOOL running = YES;
        while (running) {
            NSLog(@"\n=== CLI Note-Taking App ===");
            NSLog(@"1. List Notes\n2. Add Note\n3. Delete Note\n4. Search Notes\n5. Exit");
            NSLog(@"Enter your choice:");
            
            char input[10];
            fgets(input, sizeof(input), stdin);
            int choice = atoi(input);
            
            switch (choice) {
                case 1: listNotes(notes); break;
                case 2: addNote(notes); break;
                case 3: deleteNote(notes); break;
                case 4: searchNotes(notes); break;
                case 5: running = NO; NSLog(@"Exiting app."); break;
                default: NSLog(@"Invalid choice. Try again."); break;
            }
        }
    }
    return 0;
}