//Write a function that uses pointers to swap the values of two variables passed 
//to it. This demonstrates the power of "call by reference."

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	// printf("a is: %d\n", *a);	
}

int main() {

	int x = 5;
	int y = 10;

	printf("X is: %d\n", x);
	printf("Y is: %d\n", y);

	swap(&x, &y);

	printf("Swapped! \n");
	printf("X is: %d\n", x);
        printf("Y is: %d\n", y);

	return 0;
}
