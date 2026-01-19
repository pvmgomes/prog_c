// Write a program that allows the user to decide how many students they want to
// store, allocates exactly that much memory, and then prints the whole list.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
	char name[50];
	int id;
	float gpa;
};

char removeNewLine(char *buffer) {
	size_t len = strlen(buffer);
	if(len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
        }
	return *buffer;
}

int addStudents(struct Student *studentList, int inputQtd, int *counter) {
	char inputBuffer[10];
	int count = 0;
	//Create student's list via input prompt
        while(count < inputQtd) {
                printf("Enter the student's name: \n");
                //TODO: create constant for name size;
                char name[50];
                if (fgets(name, sizeof(name), stdin) == NULL) {
                        printf("Error reading name input!\n");
                        break;
                }

                removeNewLine(name);
                strncpy(studentList[*counter].name, name, 50);

		printf("Enter %s's GPA: \n", name);
                if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
                        printf("Error reading GPA input!\n");
                        break;
                }
                char *endptrF;
                float gpa = strtof(inputBuffer, &endptrF);
                if (endptrF == inputBuffer) {
                        printf("Invalid input! GPA will be set to 0.0\n");
                        gpa = 0.0;
                }
                studentList[*counter].gpa = gpa;
                studentList[*counter].id = *counter;

                count++;
		*counter = *counter + 1;
        }

	return 0;
}

int main(){
	//Declare list
	struct Student *studentList;
	int inputQtd;
	int listSize;
	char inputBuffer[10];
	char *endptr;
	// Ask how many students
	printf("How many students do you want to input?\n");
	if (fgets(inputBuffer, sizeof(int), stdin) == NULL) {
		printf("Error reading input.\n");
		return 1;
	}
	
	removeNewLine(inputBuffer);

	inputQtd = (int) strtol(inputBuffer, &endptr, 10);
	if (endptr == inputBuffer && *endptr != '\0') {
		printf("Invalid number input!\n");
	}

	//Create list pointer
	studentList = (struct Student*) malloc(inputQtd * sizeof(struct Student));
	if (studentList == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}
	//Create student's list via input prompt
	int counter = 0;
	addStudents(studentList, inputQtd, &counter);
	listSize = counter;
	
	//Ask if wants to add 1 more student
	printf("Would you like to add more students?(y/n)\n");
	if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
		printf("Error reading input.\n");
		return 1;
	}
	
	removeNewLine(inputBuffer);
	if (strcasecmp("yes", inputBuffer) == 0 || strcasecmp("y", inputBuffer) == 0) {
		printf("How many students?\n");
		if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
			printf("Error reading input.\n");
			return 1;
		}
		
	        removeNewLine(inputBuffer);
		inputQtd = (int) strtol(inputBuffer, &endptr, 10);
		printf("Adding %d more students.\n", inputQtd);
		// update listSize
		listSize = listSize + inputQtd;
		// realloc - increase list size by the number input.
		struct Student *temp = (struct Student*) realloc(studentList, (counter + inputQtd) * sizeof(struct Student));
		if (temp == NULL) {
			printf("Reallocation failed. \n");
			return 1;
		}
		studentList = temp;
		addStudents(studentList, inputQtd, &counter);

	}
	printf("Printing students' list. \n");
	//Print Students list
	printf("Students' list: \n");
	for (int i = 0; i < counter; i++) {
		printf("  ID: %d,\n  Name: %s,\n  GPA: %.2F\n", studentList[i].id, studentList[i].name, studentList[i].gpa);
		printf("------------------\n");
	}
	free(studentList);
	studentList = NULL;
	return 0;
}
