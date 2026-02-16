// Modify your program so that it saves the list to a file called "students.dat" 
// before exiting, and tries to load that file when it starts.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
#define NAME_LENGTH 50
#define BASE_10 10
#define FILE_NAME "students.dat"

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

int readQtyInput() {
	char inputBuffer[BUFFER_SIZE];
	char *endptr;
	int inputQty = 0;
	// Ask how many students
        printf("How many students do you want to input?\n");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
                printf("Error reading input.\n");
                return -1;
        }
	clearInputBuffer(inputBuffer);
        removeNewLine(inputBuffer);

        inputQty = (int) strtol(inputBuffer, &endptr, BASE_10);
        if (endptr == inputBuffer && *endptr != '\0') {
                printf("Invalid number input!\n");
        }

	return inputQty;
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

int main(){
	//Declare list
	struct Student *classroom;
	int inputQtd;
	char inputBuffer[BUFFER_SIZE];
	int counter = 0;

	// Load the students.dat file
	classroom = loadFromFile(&counter);

	// Ask how many students
	inputQtd = readQtyInput();

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
		inputQtd = readQtyInput();
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
	//Save students list to file
	saveToFile(classroom, counter);
	printf("Printing classroom's list. \n");
	//Print Students list
	printf("Classroom's students: \n");
	for (int i = 0; i < counter; i++) {
		printf("  ID: %d,\n  Name: %s,\n  GPA: %.2F\n", classroom[i].id, classroom[i].name, classroom[i].gpa);
		printf("------------------\n");
	}

	free(classroom);
	classroom = NULL;
	return 0;
}
