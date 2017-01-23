#include "bmp.h"
#include<assert.h>

int main(int argc, char *argv[]){
	
	//Stage 00 : Checking NULL File for reading
	char *error0 = NULL;
	BMPImage *t0i = read_bmp(NULL,&error0);
	free(error0);
	free_bmp(t0i);
	
	//Stage 01: Correct file for reading 
	FILE *fptr = fopen("./6x6_24bit.bmp","r");
	char *error1 = NULL;
	BMPImage *t1i = read_bmp(fptr,  &error1);
	assert(t1i != NULL);
	free(error1);

	//Stage 02: Null File for Writing
	char *error2 = NULL;
	bool writeCheck = write_bmp(NULL, t1i,&error2);
	assert(error2 != NULL);
	assert(writeCheck == false);
	free(error2);
	
	//Stage 03: Corrupt File read
	FILE *fptr2 = fopen("./corrupt_carw.bmp","r");
	char *error3 = NULL;
	BMPImage *t3i = read_bmp(fptr2,&error3);
	assert(t3i == NULL);
	assert(error3 != NULL);
	free(error3);
	free_bmp(t3i);

	//Stage 04: Correct writing file
	FILE *fptr3 = fopen("./testim.bmp","w");
	char *error4 = NULL;
	bool corrWrite = write_bmp(fptr3,t1i,&error4);
	assert(corrWrite == true);
	assert(error4 == NULL);
	free(error4);
	
	//Stage 05: Reading and writing file
	FILE *fptr4 = fopen("./car.bmp","r");
	char *error5 = NULL;
	BMPImage *t4i = read_bmp(fptr4, &error5);
	FILE *fptr5 = fopen("./temp.bmp","w");
	bool writeC = write_bmp(fptr5,t4i,&error5);
	assert(writeC == true);
	free_bmp(t4i);

	//Stage 06: cropping regular image 
	char *error6 = NULL;
	BMPImage *crp = crop_bmp(t1i,0,0,3,4,&error6);
	assert(crp != NULL);
	assert(error6 == NULL);
	free(error6);
	free_bmp(crp);
	
	//Stage 07: cropping corrupt image
	char *error7 = NULL;
	BMPImage *crp2 = crop_bmp(NULL,0,0,1,1,&error7);
	assert(crp2 == NULL);
	assert(error7 != NULL);
	free(error7);

	//Stage 08: Invalid cropping parameters
	char *error8 = NULL;
	BMPImage *crp3 = crop_bmp(t1i,0,0,10,10,&error8);
	assert(crp3 == NULL);
	assert(error8 != NULL);
	free(error8);

	//Stage 09: Reading and writing corrupt files
	FILE *fptr6 = fopen("./corrupt_airplanei.bmp","r");
	char *error9 = NULL;
	BMPImage *t5i = read_bmp(fptr6,&error9);
	free(error9);
	FILE *fptr7 = fopen("./temp.bmp","w");
	bool checkfailwr = write_bmp(fptr7,t5i,&error9);
	assert(t5i == NULL);
	assert(checkfailwr == false);
	assert(error9 != NULL);
	free(error9);

	//Stage 10: Read, write and crop
	FILE *fptr8 = fopen("./car.bmp","r");
	char *error10 = NULL;
	BMPImage *t6i = read_bmp(fptr8,&error10);
	free(error10);
	FILE *fptr9 = fopen("./temp.bmp","w");
	bool checkWriter = write_bmp(fptr9,t6i,&error10);
	assert(checkWriter == true);
	free(error10);
	fclose(fptr9);
	FILE *fptr10 = fopen("./temp.bmp","r");
	BMPImage *t7i = read_bmp(fptr10,&error10);
	free(error10);
	BMPImage *crpW = crop_bmp(t7i,1,1,7,100,&error10);
	assert(error10 == NULL);
	assert(crpW != NULL);
	free(error10);
	free_bmp(t6i);
	free_bmp(t7i);
	free_bmp(crpW);

	//Stage 11: Read, write and crop corrupt files
	FILE *fptr11 = fopen("./corrupt_carw.bmp","r");
	char *error11 = NULL;
	BMPImage *t8i = read_bmp(fptr11,&error11);
	free(error11);
	FILE *fptr12 = fopen("./temp.bmp","w");
	bool checkWriter2 = write_bmp(fptr12,t8i,&error11);
	assert(checkWriter2 == false);
	free(error11);
	fclose(fptr12);
	FILE *fptr13 = fopen("./temp.bmp","r");
	BMPImage *t9i = read_bmp(fptr13,&error11);
	free(error11);
	BMPImage *crpC = crop_bmp(t9i,1,1,7,100,&error11);
	assert(error11 != NULL);
	assert(crpC == NULL);
	free(error11);
	free_bmp(t8i);
	free_bmp(t9i);
	free_bmp(crpC);

	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);
	fclose(fptr5);
	fclose(fptr6);
	fclose(fptr7);
	fclose(fptr8);
	fclose(fptr10);
	fclose(fptr11);
	fclose(fptr13);
	free_bmp(t1i);
	return EXIT_SUCCESS;
}
