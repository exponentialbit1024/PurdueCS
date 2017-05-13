#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define READABLE_FILE "file_to_read.txt" /* File to be read during read operations */
#define BYTES_TO_READ_WRITE 819200 /* 800 KB */
#define MAX_BUFFER  1048576 /* 1 MB*/

/* Function for write without buffer */
void mywritec(char);

/* Functions for write with buffer */
void mywritebufsetup(int);
void myputc(char);
void mywriteflush(void);

/* Function for read without buffer */
int myreadc(void);

/* Functions for read with buffer */
void myreadbufsetup(int);
int mygetc(void);

/* Declare global variables for write operations here */
int fd_write = 1;
char write_buf[MAX_BUFFER];
char *wp;
int write_buf_size;


/* Declare global variables for read operations here */
int fd_read;
char read_buf[MAX_BUFFER];
char *rp;
int read_buf_size;
int read_count;

/* Main function starts */
int main()
{
    clock_t begin, end;
    int option, n, temp;
    const char *a="Writing byte by byte\n";
    const char *b="Writing using buffers\n";
    unsigned long i, bytes_to_write = BYTES_TO_READ_WRITE, bytes_to_read = BYTES_TO_READ_WRITE;
    char ch;

    while(1)
    {
        printf("\n 1 - Write without buffering \n 2 - Write with buffering");
        printf("\n 3 - Read without buffering \n 4 - Read with buffering");
        printf(("\n 5 - Exit \n Enter the option: "));
        scanf("%d", &option);
        switch(option)
        {
            case 1: /* Write without buffer */
                begin = clock();
                for (i=0;i<bytes_to_write;i++)
                {
                    ch = a[i%strlen(a)];
                    mywritec(ch);
                }
                end = clock();
                printf("\n Time to write without buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 2:  /* Write with buffer */
                printf("\n Enter the buffer size in bytes: ");
                scanf("%d", &n);
                mywritebufsetup(n);
                begin = clock();
                for (i=0;i<bytes_to_write;i++)
                {
                    ch = b[i%strlen(b)];
                    myputc(ch);
                }
                mywriteflush();
                end = clock();
                printf("\n Time to write with buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 3:  /* Read without buffer */
                fd_read = open(READABLE_FILE, O_RDONLY);
                if(fd_read < 0)
                {
                    printf("\n Error opening the readable file \n");
                    return 1;
                }
                begin = clock();
                for (i=0;i<bytes_to_read;i++)
                {  /* you may need to modify this slightly to print the character received and also check for end of file */
					int newC = myreadc();
                    if(newC == -1)
                    {
                        printf("\n End of file \n");
                        break;
                    }
					printf("%c", newC);
                }
                end = clock();
                if(close(fd_read))
                {
                    printf("\n Error while closing the file \n ");
                }
                printf("\n Time to read without buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 4:  /* Read with buffer */
                printf("\n Enter the buffer size in bytes: ");
                scanf("%d", &n);
                myreadbufsetup(n);
                fd_read = open(READABLE_FILE, O_RDONLY);
                if(fd_read < 0)
                {
                    printf("\n Error opening the readable file \n");
                    return 1;
                }
                begin = clock();
                for (i=0;i<bytes_to_read;i++)
                { /* you may need to modify this slightly to print the character received and also check for end of file */
					int newC = mygetc();
                    if(newC == -1)
                    {
                        printf("\n End of file \n");
                        break;
                    }
					printf("%c", newC);
                }
                end = clock();
                if(close(fd_read))
                {
                    printf("\n Error while closing the file \n ");
                }
                printf("\n Time to read with buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            default:
                return 0;
        }
    }
}

void mywritec(char ch){
	char *bufStr = malloc(sizeof(ch) + 1);
	bufStr[0] = ch;
	bufStr[1] = '\0';
	write(1, bufStr, 4);	
}

void mywritebufsetup(int n){
	if(n > MAX_BUFFER){
		return;
	}
	write_buf_size = n;
	wp = &write_buf[0];
}

void myputc(char ch){
	*wp = ch;
	wp++;
	if(wp == &write_buf[write_buf_size]){
		write(1, write_buf, write_buf_size);
		wp = &write_buf[0];
	}
}

void mywriteflush(void){
	write(1, write_buf, write_buf_size);
}

int myreadc(void){
	int *bufStr = malloc(sizeof(char));
	int readD = read(fd_read, bufStr, sizeof(char));
	if(readD == 0){
		return -1;
	}
	return bufStr[0];
}

void myreadbufsetup(int n){
	if(n < 0 || n > MAX_BUFFER){
		return;
	}
	read_buf_size = n;
	read_count = 0;
}

int mygetc(){
	if(read_count <= 0){
		read_count = read(fd_read, read_buf, read_buf_size);
		rp = &read_buf[0];
		if(read_count == 0){
			return -1;
		}
	}
	char ch = *rp;
	rp++;
	read_count--;
	return ch;
}
