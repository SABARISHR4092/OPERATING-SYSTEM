#include <stdio.h>
#include <string.h>

#define MAX_USERS 5     // Maximum number of users
#define MAX_FILES 10    // Maximum files per user
#define NAME_LEN 50     // Maximum name length

typedef struct {
    char name[NAME_LEN];
    int in_use; // 1 if file exists, 0 otherwise
} File;

typedef struct {
    char username[NAME_LEN];
    File files[MAX_FILES]; // User's file directory
    int file_count; // Number of files created
} User;

User users[MAX_USERS]; // Array to store users
int user_count = 0; // Number of registered users

// Function to create a user directory
void createUser() {
    if (user_count >= MAX_USERS) {
        printf("Error: Maximum user limit reached!\n");
        return;
    }
    
    printf("Enter new username: ");
    scanf("%s", users[user_count].username);
    users[user_count].file_count = 0; // Initialize file count
    printf("User '%s' created successfully!\n", users[user_count].username);
    user_count++;
}

// Function to find user index by username
int findUser(char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1; // User not found
}

// Function to create a file in a user's directory
void createFile() {
    char username[NAME_LEN], filename[NAME_LEN];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    int userIndex = findUser(username);
    if (userIndex == -1) {
        printf("Error: User '%s' not found!\n", username);
        return;
    }
    
    if (users[userIndex].file_count >= MAX_FILES) {
        printf("Error: User '%s' has reached the maximum file limit!\n", username);
        return;
    }
    
    printf("Enter file name: ");
    scanf("%s", filename);
    
    // Check if file already exists
    for (int i = 0; i < users[userIndex].file_count; i++) {
        if (users[userIndex].files[i].in_use && strcmp(users[userIndex].files[i].name, filename) == 0) {
            printf("Error: File '%s' already exists for user '%s'!\n", filename, username);
            return;
        }
    }
    
    // Create file
    strcpy(users[userIndex].files[users[userIndex].file_count].name, filename);
    users[userIndex].files[users[userIndex].file_count].in_use = 1;
    users[userIndex].file_count++;
    
    printf("File '%s' created for user '%s'.\n", filename, username);
}

// Function to delete a file
void deleteFile() {
    char username[NAME_LEN], filename[NAME_LEN];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    int userIndex = findUser(username);
    if (userIndex == -1) {
        printf("Error: User '%s' not found!\n", username);
        return;
    }
    
    printf("Enter file name to delete: ");
    scanf("%s", filename);
    
    for (int i = 0; i < users[userIndex].file_count; i++) {
        if (users[userIndex].files[i].in_use && strcmp(users[userIndex].files[i].name, filename) == 0) {
            users[userIndex].files[i].in_use = 0;
            printf("File '%s' deleted for user '%s'.\n", filename, username);
            return;
        }
    }
    
    printf("Error: File '%s' not found for user '%s'.\n", filename, username);
}

// Function to search for a file in a user's directory
void searchFile() {
    char username[NAME_LEN], filename[NAME_LEN];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    int userIndex = findUser(username);
    if (userIndex == -1) {
        printf("Error: User '%s' not found!\n", username);
        return;
    }
    
    printf("Enter file name to search: ");
    scanf("%s", filename);
    
    for (int i = 0; i < users[userIndex].file_count; i++) {
        if (users[userIndex].files[i].in_use && strcmp(users[userIndex].files[i].name, filename) == 0) {
            printf("File '%s' found in user '%s' directory.\n", filename, username);
            return;
        }
    }
    
    printf("File '%s' not found for user '%s'.\n", filename, username);
}

// Function to display all files of a user
void displayFiles() {
    char username[NAME_LEN];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    int userIndex = findUser(username);
    if (userIndex == -1) {
        printf("Error: User '%s' not found!\n", username);
        return;
    }
    
    printf("Files in directory of user '%s':\n", username);
    int found = 0;
    
    for (int i = 0; i < users[userIndex].file_count; i++) {
        if (users[userIndex].files[i].in_use) {
            printf(" - %s\n", users[userIndex].files[i].name);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No files found!\n");
    }
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Two-Level Directory System ---\n");
        printf("1. Create User\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display Files\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createUser(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: displayFiles(); break;
            case 6: printf("Exiting program.\n"); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}
