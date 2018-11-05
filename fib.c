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

/* declare fibonacci function for threading. */
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
			*(p + i) = result;
			n2 = n1;
			n1 = result;
		}
	}
	printf("\n"); //print newline to clean up
	return n;
}

int main(int argc, char *argv[]) {

	if (!argv[1]) {
		printf("fib syntax: int value between 3 and 30\n"); //we're arbitrarily definining a cap on how far you can go at 30. around f(50) or so we'd have to use a larger integer space, but I'd rather not fuss with that.
		return -1;
	}

	numPass = atoi(argv[1]);

	int arr[numPass];
	p = arr;

	if (!numPass) { //validation
		printf("Please enter an integer value between 3 and 30.\n");
		return 0;
	}
	if (numPass < 3 || numPass > 30) { //validation
		printf("Please enter an integer value between 3 and 30.\n");
		return 0;
	}


	/* The following code will:
		- Generate thread
		- Pass variable to thread and execute function void fib()
		- Join thread. 
		- (DEBUG) Print to indicate that the parent must execute after the child.
	
	*/
	pthread_t threadIdent;
	pthread_create(&threadIdent, NULL, fib, numPass);
	pthread_join(threadIdent, NULL);
	//printf("This should have happened after the thread is done executing.\n");

	for (int z = 0; z <= numPass; z++) {
		int arrayVal = *(p + z);
		printf("F(%d): %d\n", z, arrayVal);
	}

	exit(0);
}