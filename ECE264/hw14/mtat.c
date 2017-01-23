#include "mtat.h"
#include "bmp.h"

void *adaptiveThread(void *sliceSt){
	adaptiveThreadStruct *sst = (adaptiveThreadStruct *) sliceSt;
	int widthIm = sst -> header.width_px * sst -> header.bits_per_pixel / 8;
	int sum = 0;
	int numPix = 0;
	for(int j = sst -> header.height_px - 1; j >= 0; j--){
		for(int k = 0; k < widthIm / 3; k++){
	//		printf("%d %d %d \n", sst -> origData[j][k], j, k);
			for(int y = j;  y >= j - sst -> radius && y >= 0; y--){
				for(int x = k; x <= k + sst -> radius && x < sst -> header.width_px; x++){
			//		printf(" %d %d %d \n", sst -> origData[y][x], y, x);
					sum += sst -> origData[y][x];
					numPix++;
				}
				for(int x = k - 1; x >= k - sst -> radius && x  >= 0; x--){
	//				printf(" %d %d %d \n", sst -> origData[y][x], y, x);
					sum += sst -> origData[y][x];
					numPix++;
				}
			}
			for(int y = j + 1; y <= j + sst -> radius && y < sst -> header.height_px; y++){
				for(int x = k; x <= k + sst -> radius && x < sst -> header.width_px; x++){
//					printf(" %d %d %d \n", sst -> origData[y][x], y, x);
					sum += sst -> origData[y][x];
					numPix++;
				}
				for(int x = k - 1; x >= k - sst -> radius && x >= 0; x--){
	//				printf(" %d %d %d \n", sst -> origData[y][x], y, x);
					sum += sst -> origData[y][x];
					numPix++;
				}
			}
			if((sst -> origData[j][k] * numPix) <= sum){
				sst -> newData[j][k] = 0; 
			}
			else{
				sst -> newData[j][k] = 255;
			}
			sum = 0;
			numPix = 0;
		}
	//	printf("\n");
	}
	return NULL;
}

unsigned char *_conv2D(unsigned char **twoDGG, int height, int width, int imsz){
	unsigned char *finalData = malloc(sizeof(finalData) * imsz);
	int looper = 0;
	for(int j = height - 1; j >= 0; j--){
		for(int k = 0; k < width / 3; k++){
			if(twoDGG[j][k] == 255){
				finalData[looper] = 255;
				finalData[looper + 1] = 255;
				finalData[looper + 2] = 255;
				looper += 3;
			}
			else{
				finalData[looper] = 0;
				finalData[looper + 1] = 0;
				finalData[looper + 2] = 0;
				looper += 3;
			}
		}
		for(int r = 0; r < width % 4; r++){
			finalData[looper] = 0;
			looper++;
		}
	}
	return finalData;
}

BMPImage *binarize(BMPImage *image, int radius, int num_threads, char **a_error){

	if(a_error == NULL){
		return NULL;
	}
	if(image == NULL){
		*a_error = _strdup("Image is empty");
		return NULL;
	}

	BMPHeader copyHeader = image -> header;
	BMPImage *output = malloc(sizeof(*output));
	output -> header = copyHeader;
	
	unsigned char **twoDG = _twoDGRet(image -> data, &image -> header);
	unsigned int **rgbs = malloc(sizeof(*rgbs) * output -> header.height_px);
	unsigned char **newData = malloc(sizeof(*newData) * output -> header.height_px);
	int widthIm = output -> header.width_px * output -> header.bits_per_pixel / 8;
	for(int y = output -> header.height_px - 1; y >= 0; y--){
		newData[y] = malloc(sizeof(*newData[y]) * output -> header.width_px);
	}

	pthread_t *threadAr = malloc(sizeof(pthread_t) * num_threads);

	int i = 0;
	for(int j = output -> header.height_px - 1; j >= 0; j--){
		rgbs[j] = malloc(sizeof(*rgbs[j]) * output -> header.width_px);
		for(int k = 0; k < widthIm; k++){
			rgbs[j][i] = twoDG[j][k] + twoDG[j][k+1] + twoDG[j][k+2];
			k += 2;
			i++;
		}
		i = 0;
	}
	
//	printf("\n");
//	for(int j = output -> header.height_px - 1; j >= 0; j--){
//		for(int k = 0; k < widthIm / 3; k++){
//			printf("%d ", rgbs[j][k]);
//		}
//		printf("\n");
//	}	

	int threadSuccess = 0;
	adaptiveThreadStruct tSlice;
	tSlice.origData = rgbs;
	tSlice.newData = newData;
	tSlice.tNum = 0;
	tSlice.radius = radius;
	tSlice.numThreads = num_threads;
	tSlice.header = output -> header;

	for(int a = 0; a < num_threads; a++){
		threadSuccess = pthread_create(&threadAr[a],NULL,adaptiveThread,&tSlice);
		if(threadSuccess != 0){
			*a_error = _strdup("Error creating a new thread!");
			return NULL;
		}
	}
	for(int b = 0; b < num_threads; b++){
		pthread_join(threadAr[b], NULL);
	}
	
//	printf("\n");
//	for(int j = output -> header.height_px - 1; j >= 0; j--){
//		for(int k = 0; k < output -> header.width_px; k++){
//			printf("%d ", tSlice.newData[j][k]);
//		}
//		printf("\n");
//	}

	output -> data = _conv2D(tSlice.newData, output -> header.height_px, widthIm, output -> header.image_size_bytes);
	free(threadAr);

	for(int t = 0; t < image -> header.height_px; t++){
		free(rgbs[t]);
		free(twoDG[t]);
		free(newData[t]);
	}
	free(twoDG);
	free(rgbs);
	free(newData);
	return output;
}
