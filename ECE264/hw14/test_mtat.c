#include "mtat.h"
#include "bmp.h"

int main(int argc, char *argv[]){
	FILE *fptr = fopen("img1_6x6_color.bmp","r");
	char *error = NULL;
	BMPImage *input = read_bmp(fptr,&error);
	BMPImage *gray = binarize(input,2,1,&error);
	
	FILE *fptr1 = fopen("./temp.bmp","w");
	write_bmp(fptr1, gray, &error);

	free(error);
	free_bmp(input);
	free_bmp(gray);
	fclose(fptr);
	fclose(fptr1);
	return 0;
}
