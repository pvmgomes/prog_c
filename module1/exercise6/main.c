#include "student.h"
#include <stdlib.h>
#include <string.h>

int main(){
        //Declare list
        struct Student *classroom;
        int inputQtd;
        char inputBuffer[BUFFER_SIZE];
        int counter = 0;
        int running = 1;
        int choice;
        int idToDel = -1;

        // Load the students.dat file
        classroom = loadFromFile(&counter);

        while(running) {
                printf("\n---Classroom Management---\n");
                printf("1. View students \n2. Add students \n3. Delete by ID \n4. Exit\n");

                choice = readInputInt(CHOICE_TXT);

                switch(choice) {
                        case 1:
                                //PRINT CLASSROOM
                                if(classroom != NULL) {
                                        printClassroom(classroom, counter);
                                } else {
                                        printf("Classroom is empty!\n");
                                }
                                break;
                        case 2:
				// ADD STUDENTS
                                // Ask how many students
                                inputQtd = readInputInt(INPUT_QTY_TXT);

                                if (classroom == NULL) {
                                        //Create list pointer
                                        classroom = (struct Student*) malloc(inputQtd * sizeof(struct Student));
                                        if (classroom == NULL) {
                                                printf("Memory allocation failed\n");
                                                return 1;
                                        }
                                } else {
                                        // realloc list loaded from file to accomodate new students.
                                        struct Student *temp = (struct Student*) realloc(classroom, (counter + inputQtd) * sizeof(struct Student));
                                        if (temp == NULL) {
                                                printf("Reallocation failed. \n");
                                                return 1;
                                        }
                                        classroom = temp;
                                }
                                //Create student's list via input prompt
                                addStudents(classroom, inputQtd, &counter);

                                //Ask if wants to add more students
                                printf("Would you like to add more students?(y/n)\n");
                                if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
                                        printf("Error reading input.\n");
                                        return 1;
                                }

                                clearInputBuffer(inputBuffer);
                                removeNewLine(inputBuffer);
				if (strcasecmp("yes", inputBuffer) == 0 || strcasecmp("y", inputBuffer) == 0) {
                                        inputQtd = readInputInt(INPUT_QTY_TXT);
                                        printf("Adding %d more students.\n", inputQtd);

                                        // realloc - increase list size by the number input.
                                        struct Student *temp = (struct Student*) realloc(classroom, (counter + inputQtd) * sizeof(struct Student));
                                        if (temp == NULL) {
                                                printf("Reallocation failed. \n");
                                                return 1;
                                        }
                                        classroom = temp;
                                        addStudents(classroom, inputQtd, &counter);
                                }

                                break;
                        case 3:
                                idToDel = readInputInt("Which student would you like to delete?(ID)\n");
                                classroom = deleteById(classroom, &counter, idToDel);
                                break;
                        case 4:
                                printf("Bye!\n");
                                running = 0;
                                break;
                        default:
                                printf("Invalid choice!\n");
                }
        }

        saveToFile(classroom, counter);

        free(classroom);
        classroom = NULL;
        return 0;
}

