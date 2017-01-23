#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/* TODO:  Create a worker function to go with zero_array(..) */

bool zero_array(int* array, int size, int num_threads, char** a_error) {
	/* Given an array, set every element to 0 using multiple threads.
	 *
	 * - If successful, return true and do not modify error at all.
	 *
	 * - In case of any failure, return false and, if a_error != NULL,
	 *   set *a_error to the address of an error message on the heap.
	 *   The caller will be responsible for freeing it.
	 */
	return true; /* TODO: finish this function and remove this stub */
}

int main(int argc, char *argv[]) {
	int array[16] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
	int size = sizeof(array)/sizeof(*array);
	for(int i=0; i<size; i++) {
		assert(array[i] == 2);
	}
	char* error = NULL;
	if( zero_array(array, sizeof(array)/sizeof(*array), 4, &error) ) {
		for(int i=0; i<size; i++) {
			assert(array[i] == 0);
		}
		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "%s\n", error);
		free(error);
		return EXIT_FAILURE;
	}
}

