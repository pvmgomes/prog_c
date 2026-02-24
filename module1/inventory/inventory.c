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
