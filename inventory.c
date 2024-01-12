// inventory.c
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
void displayMenu(){

    printf("\n--- E-Commerce App Menu ---\n");
    printf("1. Add Item\n");
    printf("2. Update Item\n");
    printf("3. Generate Report/Bill\n");
    printf("4. Total Number and Price with GST\n");
    printf("5. Display Stock\n");
    printf("6. Order Items\n");
    printf("7. Delete Items\n");
    printf("8. Exit\n");
}

void addItem()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    struct Item newItem;
    printf("Enter Item ID: ");
    scanf("%d", &newItem.id);
    // Check if the entered item ID already exists
    struct Item existingItem;
    int idExists = 0;
    while (fscanf(file, "%d %s %f %d", &existingItem.id, existingItem.name, &existingItem.price, &existingItem.stock) != EOF)
    {
        if (existingItem.id == newItem.id)
        {
            idExists = 1;
            break;
        }
    }
    fclose(file);
    if (idExists)
    {
        printf("Item with ID %d already exists. Please choose a different ID.\n", newItem.id);
    }
    else
    {
        file = fopen(FILENAME, "a");
        if (file == NULL)
        {
            perror("Error opening file");
            exit(1);
        }
        printf("Enter Item Name: ");
        scanf("%s", newItem.name);
        printf("Enter Item Price: ");
        scanf("%f", &newItem.price);
        printf("Enter Item Stock: ");
        scanf("%d", &newItem.stock);
        fprintf(file, "%d %s %.2f %d\n", newItem.id, newItem.name, newItem.price, newItem.stock);
        fclose(file);
        printf("Item added successfully!\n");
    }
}

void updateItem()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    int targetId;
    printf("Enter Item ID to update: ");
    scanf("%d", &targetId);
    // Check if the item with the specified ID exists
    struct Item item;
    int idExists = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            idExists = 1;
            break;
        }
    }
    fclose(file);
    if (!idExists)
    {
        printf("Item with ID %d not found.\n", targetId);
        return; // Exit the function if item ID doesn't exist
    }
    // Proceed to update the item
    file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(1);
    }
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            // Update information if item is found
            printf("Enter new Item Name: ");
            scanf("%s", item.name);
            printf("Enter new Item Price: ");
            scanf("%f", &item.price);
            printf("Enter new Item Stock: ");
            scanf("%d", &item.stock);
        }
        fprintf(tempFile, "%d %s %.2f %d\n", item.id, item.name, item.price, item.stock);
    }
    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    printf("Item updated successfully!\n");
}

void generateReport()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    struct Item item;
    printf("\n--- Report/Bill ---\n");
    printf("ID\tName\t\tPrice\tStock\n");
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        printf("%d\t%s\t\t%.2f\t%d\n", item.id, item.name, item.price, item.stock);
    }
    fclose(file);
}

void getTotalNumAndPriceWithGST()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    struct Item item;
    int totalNum = 0;
    float totalPrice = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        totalNum += item.stock;
        totalPrice += item.price * item.stock;
    }
    // Assuming GST is 18%

    float totalWithGST = totalPrice + (totalPrice * 0.18);
    printf("Total Number of Items: %d\n", totalNum);
    printf("Total Price without GST: %.2f\n", totalPrice);
    printf("Total Price with GST (18%%): %.2f\n", totalWithGST);
    fclose(file);
}

void displayStock()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    struct Item item;
    printf("\n--- Stock Information ---\n");
    printf("ID\tName\t\tPrice\tStock\n");
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        printf("%d\t%s\t\t%.2f\t%d\n", item.id, item.name, item.price, item.stock);
    }
    fclose(file);
}

void orderItem()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    int targetId, quantity;
    printf("Enter Item ID to order: ");
    scanf("%d", &targetId);
    printf("Enter quantity to order: ");
    scanf("%d", &quantity);
    struct Item item;
    int idExists = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            idExists = 1;
            break;
        }
    }
    fclose(file);
    if (!idExists)
    {
        printf("Item with ID %d not found.\n", targetId);
        return; 
    }

    file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(1);
    }
    int ordered = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            item.stock -= quantity;
            ordered = 1;
        }
        fprintf(tempFile, "%d %s %.2f %d\n", item.id, item.name, item.price, item.stock);
    }
    fclose(file);
    fclose(tempFile);
    if (!ordered)
    {
        printf("Item with ID %d not found.\n", targetId);
        remove("temp.txt");
    }
    else
    {
        printf("Item ordered successfully!\n");
        // Replace the original file with the updated temporary file
        remove(FILENAME);
        rename("temp.txt", FILENAME);
    }
}

void deleteItems()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    int targetId;
    printf("Enter Item ID to delete: ");
    scanf("%d", &targetId);
    struct Item item;
    int idExists = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            idExists = 1;
            break;
        }
    }
    fclose(file);
    if (!idExists)
    {
        printf("Item with ID %d not found.\n", targetId);
        return; 
    }
    file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(1);
    }
    int deleted = 0;
    while (fscanf(file, "%d %s %f %d", &item.id, item.name, &item.price, &item.stock) != EOF)
    {
        if (item.id == targetId)
        {
            deleted = 1;
            continue;
        }
        fprintf(tempFile, "%d %s %.2f %d\n", item.id, item.name, item.price, item.stock);
    }
    fclose(file);
    fclose(tempFile);
    if (!deleted)
    {
        printf("Item with ID %d not found.\n", targetId);
        remove("temp.txt"); 
    }
    else
    {
        printf("Item deleted successfully!\n");
        remove(FILENAME);
        rename("temp.txt", FILENAME);
    }
}