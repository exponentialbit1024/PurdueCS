/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

// indexer.c
//
// You may use/copy any/all of this code for use in hw10
//
// To compile:
// 	gcc -o index indexer.c index.c
//
// To run:
// 	./index <word> <filename>[, <filename>[, ...]]

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "index.h"

bool _is_word_char(char ch) {
	return (ch >= 'a' && ch <= 'z') ||
	       (ch >= 'A' && ch <= 'Z') ||
		   (ch >= '0' && ch <= '9') ||
		   ch == '\'' || ch == '_' || ch == '-';
}

void _add_file_to_index(Index* index, char* filename) {

	struct stat stat_info;
	int stat_return_code = stat(filename, &stat_info);
	if(stat_return_code != 0) {
		fprintf(stderr, "Failed to examine file %s\n", filename);
		exit(1);
	}
	off_t fsize = stat_info.st_size;

	if(!S_ISREG(stat_info.st_mode)){
		fprintf(stderr, "Not a regular file: %s\n", filename);
		exit(1);
	}

	FILE* file = fopen(filename, "r");
	if(file == NULL){
		fprintf(stderr, "Failed to open file %s\n", filename);
		exit(1);
	}
	char* buf  = malloc(sizeof(char) + (fsize + 1));
	size_t num_bytes_read = fread(buf, sizeof(char), fsize, file);
	fclose(file);

	assert(fsize == num_bytes_read);
	buf[num_bytes_read] = '\0';

	char* word = malloc(sizeof(char) + (fsize + 1));
	off_t start = 0, end = 0;
	bool usable = true;
	while(true) {
		while(start < fsize && !_is_word_char(buf[start])) {
			start++;
		}
		end = start;
		while(end + 1 < fsize && _is_word_char(buf[end + 1])) {
			end++;
			char ch = buf[end];
			usable = usable && ch <= 127 && ch >= 32;
		}
		
		if(start >= fsize || end >= fsize) {
			break;
		}

		if(usable) {
			size_t word_len = end - start + 1;
			memcpy(word, buf + start, word_len);
			word[word_len] = '\0';

			put(index, word, filename);

			start = end + 1;
		}
	}

	free(buf);
	free(word);
}

int main(int argc, char *argv[]) {
	if(argc <= 2) {
		fprintf(stderr, "\nUsage:  indexer <word> <filename>[, <filename>[, ...]]\n");
		exit(1);
	}

	char* search_word = argv[1];
	Index index = create_index();

	for(int i = 2; i < argc; i++) {
		char* filename = argv[i];
		_add_file_to_index(&index, filename);
	}

	int count = 0;
	char** file_list = get(&index, &count, search_word); 

	printf("%d files contain \"%s\"\n", count, search_word);
	
	for(int j = 0; j < count; j++){
		printf("- %s\n", file_list[j]);
	}

	free(file_list);
	
	free_index(&index);

	return 0;
}
