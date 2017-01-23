#ifndef _MTAT_H_
#define _MTAT_H_
#include "bmp.h"
#include <pthread.h>
#include <string.h>
// Do not modify the declaration of binarize.
BMPImage* binarize(BMPImage* image, int radius, int num_threads, char** a_error);

// OK to add your own declarations BELOW here
typedef struct adaptiveThread{
	unsigned int **origData;
	unsigned char **newData;
	BMPHeader header;
	int tNum;
	int heightSnd;
	int heightEnd;
	int widthSnd;
	int widthEnd;
	int radius;
	int numThreads;
}adaptiveThreadStruct;

#endif /* mtat.h */
