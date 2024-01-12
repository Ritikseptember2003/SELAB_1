#ifndef INVENTORY_H
#define INVENTORY_H
#define MAX_ITEMS 100
#define FILENAME "inventory.txt"
struct Item {
    int id;
    char name[50];
    float price;
    int stock;
};

void displayMenu();
void addItem();
void updateItem();
void generateReport();
void getTotalNumAndPriceWithGST();
void displayStock();
void orderItem();
void deleteItems();
#endif