// Modify your program so that it has a menu interface and add the delete function.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
#define NAME_LENGTH 50
#define BASE_10 10
#define FILE_NAME "students.dat"
#define INPUT_QTY_TXT "How many students do you want to input?\n"
#define CHOICE_TXT "Choice: \n"

struct Student {
	char name[NAME_LENGTH];
	int id;
	float gpa;
};

void removeNewLine(char *buffer) {
	size_t len = strlen(buffer);
	if(len > 0 && buffer[len - 1] == '\n') {
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

int addStudents(struct Student *studentList, int inputQtd, int *counter) {
	char inputBuffer[BUFFER_SIZE];
	int count = 0;
	//Create student's list via input prompt
        while(count < inputQtd) {
                printf("Enter the student's name: \n");
                char name[NAME_LENGTH];
                if (fgets(name, sizeof(name), stdin) == NULL) {
                        printf("Error reading name input!\n");
                        break;
                }

		clearInputBuffer(name);
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
                studentList[*counter].id = *counter + 1;

                count++;
		*counter = *counter + 1;
        }

	return 0;
}

int readInputInt(char *message) {
	char inputBuffer[BUFFER_SIZE];
	char *endptr;
	int inputInt;

	printf("%s", message);
	if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
		printf("Error reading input.\n");
		return -1;
	}
	clearInputBuffer(inputBuffer);
	removeNewLine(inputBuffer);

	inputInt = (int) strtol(inputBuffer, &endptr, BASE_10);
	if (endptr == inputBuffer && *endptr != '\0') {
		printf("invalid number input!\n");
		return -1;
	}

	return inputInt;
}

void saveToFile(struct Student *students, int count) {
	FILE *fptr;
	
	fptr = fopen(FILE_NAME, "wb");
	if (fptr == NULL) {
		printf("Error opening the file.\n");
	}

	fwrite(&count, sizeof(int), 1, fptr);
	fwrite(students, sizeof(struct Student), count, fptr);
	fclose(fptr);
	fptr = NULL;
}

struct Student* loadFromFile(int *count) {
	FILE *fptr;
	struct Student *students;
	int fcount;

	fptr = fopen(FILE_NAME, "rb");
	if (fptr == NULL) {
		printf("Error opening the file. A new file will be created.\n");
		return NULL;
	}
	// Retrieve variable that stores list size
	fread(&fcount, sizeof(int), 1, fptr);
	if (fcount <= 0) {
		return NULL;
	}
	// Creates list pointer based on list size retieved
	students = (struct Student*) malloc(fcount * sizeof(struct Student));
	if (students == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}
	fread(students, sizeof(struct Student), fcount, fptr);

	fclose(fptr);
	fptr = NULL;
	
	*count = fcount;
	return students;
}

void printClassroom(struct Student *classroom, int counter) {
	//Print Students list
        printf("Classroom's students: \n");
        for (int i = 0; i < counter; i++) {
                printf("  ID: %d,\n  Name: %s,\n  GPA: %.2F\n", classroom[i].id, classroom[i].name, classroom[i].gpa);
                printf("------------------\n");
        }

}

struct Student* deleteById(struct Student *classroom, int *counter, int id) {
	int deleteIndex = -1;

	if(classroom != NULL) {
		for (int i = 0; i < *counter; i++) {
			if(classroom[i].id == id) {
				// element found
				deleteIndex = i;
				break;
			}
		}
		if(deleteIndex == -1) {
			printf("Student not found with ID: %d\n", id);
			return classroom;
		} else {
			//If it's the last element, delete by realloc.
			if (!((*counter -1) == deleteIndex)) {
				for (int i = deleteIndex; i < (*counter -1); i++) {
                        	       classroom[i] = classroom[i+1];
	                        }

			}
			*counter = *counter -1;
                        struct Student *temp = (struct Student *) realloc(classroom, ( *counter * sizeof(struct Student)));
                        
			printf("Deleted!\n");
			return (temp != NULL) ? temp : classroom;
		}
	}
	
}

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
