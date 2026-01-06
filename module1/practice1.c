//Write a program that declares an integer variable, let's call it my_data.

//Use malloc() to dynamically allocate enough memory on the heap to store an integer. Store the returned address in a pointer variable, let's call it p_data.

//Assign a value (e.g., 42) to the memory location pointed to by p_data using the dereference operator (*).

//Print the value using the pointer, and the address of the memory using the pointer.

//Use free() to release the allocated memory.
#include <stdio.h>
#include <stdlib.h>

int main() {
	int my_data;
	int *p_data = (int *)malloc(sizeof(int));

	my_data = 42;

	*p_data = my_data;
	printf("my_data: %d\n", my_data);
	printf("  address: %p\n", (void*) &my_data);	
	printf("p_data: %d\n", *p_data);
	printf("  address: %p\n", (void*) p_data);
	
	free(p_data);
	return 0;
}
