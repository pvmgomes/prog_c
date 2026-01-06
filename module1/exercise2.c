//Create and manage a simple struct, and write a function 
//that takes a pointer to it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
	char name[50];
	int id;
	float gpa;
};

void print_student(struct Student *student) {
	printf("Student info:\n");
	printf("  Id: %d\n", student->id);
	printf("  Name: %s\n", student->name);
	printf("  GPA: %.2f\n", student->gpa);
}

int main() {
	struct Student *student;

	student = (struct Student*) malloc(sizeof(struct Student));

	if(student == NULL) {
                printf("Memory allocation failed!\n");
		return 1;
	}

	//Input student information
	student->id = 1;
	//Read name from imput promt
	printf("Enter the student's name: \n");
	if (fgets(student->name, sizeof(student->name), stdin) != NULL) {
		student->name[strcspn(student->name, "\n")] = '\0';
	}	

	//Read GPA from input prompt
	char strBuffer[50];
	printf("Enter the student's GPA: \n");
	if (fgets(strBuffer, sizeof(strBuffer), stdin) != NULL) {
		char *endptr;
		float val = strtof(strBuffer, &endptr);

		//Simple float check
		if (endptr == strBuffer) {
			printf("Invalid input! GPA will be set to 0.0\n");
			student->gpa = 0.0;
		} else {
			student->gpa = val;
		}
	}

	print_student(student);
	free(student);
	student = NULL;
}
