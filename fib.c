/**

	fib.c
	(c) Robert Maloy, 2018
	All rights reserved.
	
	**/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 

/* pre-program declarations of values for use in our fibonacci function. */
int n1;
int n2;
int result;
int numPass;
double *p;

/* This function performs the fibonacci sequencing. */
/* First, it declares the value of "integer n" from the value passed to the function through pthread.
 Once this is done, it declares the constants we know of in the fibonacci sequence--0 and 1. Once that is done, it iterates up to the value of n and performs the required fibonacci calculations therein. */

void *fib(void *vargp) {
	int n = (int *)vargp; //set value of n to argument passed from main.
	for (int i = 0; i <= n; i++) { //from i=0 to i=n, iterate.
		if (i == 0) {
			n2 = i; //F(0) = 0
			*(p + i) = n2;
		 }
		if (i == 1) {
			n1 = i; // F(1) = 1
			*(p + i) = n1;
		}
		if (i >= 2) {
			result = n1 + n2; //now calculate F(2) to F(n).
			*(p + i) = result; //push this value to the array.
			n2 = n1; /* Here, we're moving everything down a spell. */
			n1 = result;
		}
	}
	printf("\n"); //print newline. This keeps the output clean.
    return n; //return the n value back to the main function.
}

int main(int argc, char *argv[]) {

	if (!argv[1]) {
		printf("fib syntax: int value between 3 and 46\n");
        /*
            This is being arbitrarily capped to 46, because trying to create a system
         that allows for fibonacci sequences which exceed 32-bit integer values is not something
         I wish to relive. I've already done this before, and it took more than the time allotted to me
         by this assignment. For the sake of performing threading, 46 positions is more than enough to demonstrate the sequencing. */
         
		return -1;
	}

	numPass = atoi(argv[1]);

	double arr[numPass]; //this declares our array
	p = arr; //this tells the pointer to point to arr[0]. This is how we're going to access it from all threads.

	if (!numPass) { //validation
		printf("Please enter an integer value between 3 and 46.\n");
		return 0;
	}
	if (numPass < 3 || numPass > 46) { //validation
		printf("Please enter an integer value between 3 and 46.\n");
		return 0;
	}


	/* The following code will:
		- Generate thread identifier
		- Pass variable to thread and execute function void fib() within a new thread,
		- Join thread (so to execute the fibonacci sequencing),
		- (DEBUG) Print to indicate that the parent must execute after the child.
        - Iterate through the double array to print all the fibonacci numbers we have in sequence.
        - Exit program gracefully.
	*/
    
	pthread_t threadIdent;
	pthread_create(&threadIdent, NULL, fib, numPass);
	pthread_join(threadIdent, NULL);

	for (int z = 0; z <= numPass; z++) {
		int arrayVal = *(p + z);
		printf("F(%d): %d\n", z, arrayVal);
	}
	exit(0); //exit program.
}
