#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 10

struct User {
    char username[50];
    char password[50];
    int isAdmin;
};

struct User users[MAX_USERS] = {
    {"admin", "admin@123", 1},       // Admin user
    {"customer", "customer@123", 0}  // Customer user
};

int numUsers = 2;  // Number of predefined users
int authenticateUser() {
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return users[i].isAdmin;
        }
    }
    return -1;  // Invalid user
}

int main() {
    int isAdmin = authenticateUser();
    if (isAdmin == -1) {
        printf("Invalid credentials. Exiting.\n");
        exit(1);
    }
    int choice;
    do {
        displayMenu(isAdmin);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                updateItem();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                getTotalNumAndPriceWithGST();
                break;
            case 5:
                displayStock();
                break;
            case 6:
                if (!isAdmin) {
                    orderItem();
                } else {
                    printf("Admins cannot order items. Please choose a different option.\n");
                }
                break;
            case 7:
                if (isAdmin) {
                    deleteItems();
                } else {
                    printf("You do not have permission to delete items.\n");
                }
                break;
            case 8:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (1);
    return 0;
}