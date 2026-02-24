#include "inventory.h"
#include <stdlib.h>

int main() {
    int running = 1;
    int choice = -1; //innitialize choice with an invalid option
    // Loop to keep the program running until user chooses to exit
    while(running) {
        printf("---- Inventory Management ----\n");
        printf("1. List all \n2. Add item \n3. Find by SKU \n4. Update quantity \n5. Exit\n");
        choice = readInputInt("Choice:\n");
        switch(choice) {
            case 1:
                printf("List all\n");
                break;
            case 2:
                printf("Add item\n");
                break;
            case 3:
                printf("Find by SKU\n");
                break;
            case 4:
                printf("Update quantity\n");
                break;
            case 5:
                printf("Exit\n");
                running = 0;
                break;
            default:
                printf("Invalid option!\n");

        }
        //running = 0;
    }
    return 0;
}
