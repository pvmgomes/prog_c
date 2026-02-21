#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

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

void removeNewLine(char *buffer);
void clearInputBuffer(char *str);
int readInputInt(char *message);
int addStudents(struct Student *studentList, int inputQtd, int *counter);
void saveToFile(struct Student *students, int count);
struct Student* loadFromFile(int *count);
void printClassroom(struct Student *classroom, int counter);
struct Student* deleteById(struct Student *classroom, int *counter, int id);

#endif
