#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>

#define BUFFER_SIZE 10
#define BASE_10 10
#define NAME_SIZE 40
#define FILE_NAME "warehouse.bin"

struct Item {
    int sku; //id
    char name[NAME_SIZE];
    int quantity;
    float price;
};

void removeNewLine(char *buffer);
void clearInputBuffer(char *str);
int readInputInt(char *message);
int addItem(struct Item *items, int *capacity);

#endif
