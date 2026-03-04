#include "inventory.h"
#include <stdlib.h>
#include <string.h>

void removeNewLine(char *buffer) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void clearInputBuffer(char *str) {
    // If the string does NOT contain a newline, the buffer still has data
    if (strchr(str, '\n') == NULL && !feof(stdin)) {
        int c;
        // Keep reading characters until we hit a newline or end of file
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int readInputInt(char *inputMessage) {
    char inputBuffer[BUFFER_SIZE];
    char *endptr;
    int inputInt = -1;

    printf("%s", inputMessage);
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
        printf("Error reading input.\n");
        return -1;
    }
    clearInputBuffer(inputBuffer);
    removeNewLine(inputBuffer);

    inputInt = (int) strtol(inputBuffer, &endptr, BASE_10);
    if (endptr == inputBuffer && *endptr != '\0') {
        printf("Invalid number input!\n");
        return -1;
    }

    return inputInt;
}

int addItem(struct Item *items, int *capacity) {
    int count; // to count items and id generation
    char inputBuffer[BUFFER_SIZE];
    int running = 1;

    while(running) {
        //TODO check if items array needs realloc             
        if (count >= *capacity) {
            // increase capacity
            *capacity = *capacity + 2;
            //realloc for new capacity
            struct Item *temp = (struct Item*) realloc(items, *capacity * sizeof(struct Item));
            if (temp == NULL) {
                printf("Reallocation failed!\n");
                return 1;
            }
            items = temp;
        }

        // input name
        printf("Enter item's name:\n");
        char name[NAME_SIZE];
        if (fgets(name, sizeof(name), stdin) == NULL) {
            printf("Error reading name input!\n");
            break;
        }

        clearInputBuffer(name);
        removeNewLine(name);

        //input item's quantity
        int quantity = readInputInt("Enter item's quantity:\n");

        //input price
        printf("Enter item's price:\n");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Error reading price input!\n");
            break;
        }
        char *endptr;
        float price = strtof(inputBuffer, &endptr);
        if (endptr == inputBuffer) {
            printf("Invalid price input!\n");
            break;
        }
        //assemble item data at once
        items[count].sku = count + 1;
        strncpy(items[count].name, name, NAME_SIZE);
        items[count].quantity = quantity;
        items[count].price = price;

        printf("New item added!\n");

        printf("Would you like to add another item?\n");
        //TODO ask if user wants to add more items
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Error reading input.\n");
            return 1;
        }
 
        clearInputBuffer(inputBuffer);
        removeNewLine(inputBuffer);
        if (strcasecmp("yes", inputBuffer) == 0 || strcasecmp("y", inputBuffer) == 0) {
            // increment count for the next round
            count++;
            continue;
        } else {
            //Exit the loop and finish add item
            running = 0;
        }
    }

    return 0;
}
