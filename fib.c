/**

	fib.c
	(c) Robert Maloy, 2018
	All rights reserved.
	
	**/

#include <stdio.h>
#include <stdlib.h>

int n1;
int n2;
int result;

int fib(int n) { 
	for (int i = 0; i <= n; i++) {
		if (i == 0) {
			n2 = i;
			printf("F(0): %d\n", n2);
		 }
		if (i == 1) {
			n1 = i;
			printf("F(1): %d\n", n1);
		}
		if (i >= 2) {
			result = n1 + n2;
			printf("F(%d): %d\n", i, result);
			n2 = n1;
			n1 = result;
		}
	}
	printf("\n");
	return result;
}

int main(int argc, char *argv[]) {

	if (!argv[1]) {
		printf("fib syntax: int value between 3 and 10\n");
		return -1;
	}

	int test = atoi(argv[1]);

	if (!test) {
		printf("Please enter an integer value between 3 and 30.\n");
		return 0;
	}
	if (test < 3 || test > 30) {
		printf("Please enter an integer value between 3 and 30.\n");
		return 0;
	}

	fib(test);

	return 0;
}