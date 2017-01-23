#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct sliceStruct{
	int *slice;
	int startSlice;
	int endSlice;
	int arraySize;
	int tNum;
	int numThreads;
}sliceStruct;

void *worker(void *sliceSt){
	
	sliceStruct *slicePack = (sliceStruct *) sliceSt;
	slicePack -> tNum++;
	if(slicePack -> tNum == slicePack -> numThreads){
		slicePack -> endSlice = slicePack -> arraySize;
	}
	int j = 0;
	for(int k = slicePack -> startSlice; k < slicePack -> endSlice; k++){
		slicePack -> slice[k] = 0;
		j++;
	}
	slicePack -> startSlice = slicePack -> endSlice;
	slicePack -> endSlice = slicePack -> startSlice + j;
	return NULL;
}

char *_strdup(char *s){
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

bool zero_array(int* array, int size, int num_threads, char** a_error) {
	/* Given an array, set every element to 0 using multiple threads.
	 *
	 * - If successful, return true and do not modify error at all.
	 *
	 * - In case of any failure, return false and, if a_error != NULL,
	 *   set *a_error to the address of an error message on the heap.
	 *   The caller will be responsible for freeing it.
	 */
	if(size < 0){
		*a_error = _strdup("Size cannot be negative");
		return false;
	}
	if(array == NULL){
		*a_error = _strdup("Empty array");
		return false;
	}
	
	if(num_threads > size){
		num_threads = size;
	}

	pthread_t *threadAr = malloc(sizeof(pthread_t) * num_threads);
	
	sliceStruct tSlice;
	tSlice.slice = array;

	int sliceStart = 0;
	int sliceEnd = sliceStart + size / num_threads;
	tSlice.startSlice = sliceStart;
	tSlice.endSlice = sliceEnd;
	tSlice.tNum = 0;	
	tSlice.numThreads = num_threads;
	tSlice.arraySize = size;
	int threadSuccess;
	for(int j = 0; j < num_threads; j++){
		threadSuccess = pthread_create(&threadAr[j], NULL, worker, &tSlice);
		if(threadSuccess != 0){
			*a_error = _strdup("Error creating a thread!");
			return false;
		}
	}
	
	for(int j = 0; j < num_threads;j++){
		pthread_join(threadAr[j], NULL);
	}
	free(threadAr);
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

