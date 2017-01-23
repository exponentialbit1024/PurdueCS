#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

typedef struct { int x; int y; } Point;

char * read_file(const char *path, char **error){
	FILE *fptr;
	fptr = fopen(path,"r");
	if(fptr == NULL){
		*error = malloc(sizeof(*error) * 50);
		strcpy(*error,"Cannot open the file");
		return *error;
	}
	fseek(fptr, 0, SEEK_END);
	long fsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	char *output = malloc(fsize + 1);
	fread(output,fsize,1, fptr);
	fclose(fptr);
	return output;
}

void write_file(const char *path, const char *contents, char **error){
	FILE *fptr;
	fptr = fopen(path, "w");
	if(fptr == NULL){
		*error = malloc(sizeof(*error) * 50);
		strcpy(*error,"Cannot find/open the file");
		return;
	}
	fwrite(contents, 1, sizeof(contents), fptr);
	fclose(fptr);
}

void write_point(char *path, Point p, char **error){
	FILE *fptr;
	fptr = fopen(path,"w");
	if(fptr == NULL){
		*error = malloc(sizeof(*error) * 50);
		strcpy(*error,"Cannot open/find file");
		return;
	}
	fwrite(&p,1,sizeof(p),fptr);
	fclose(fptr);
}

Point read_point(const char *path, char **error){
	FILE *fptr;
	Point result;
	fptr = fopen(path,"r");
	if(fptr == NULL){
		*error = malloc(sizeof(*error) * 50);
		strcpy(*error,"Cannot open the file for reading Point");
		return result;
	}
	fseek(fptr, 0, SEEK_END);
	long fsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	fread(&result, fsize,1,fptr);		
	fclose(fptr);
	return result;
}

int main(int argc, char *argv[]){
	char *error; 
	char *error2 = read_file("./testext.txt", &error);
	printf("%s", error2);
	Point writePoint;
	writePoint.x = 10;
	writePoint.y = 20;
	write_point("./ptext.txt",writePoint,&error);
	Point readPoint = read_point("./ptext.txt",&error);
	printf("%d",readPoint.x);
	free(error);
	free(error2);
	return 0;
}
