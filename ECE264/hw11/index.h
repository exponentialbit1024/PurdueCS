// You may use/copy any/all code from this file.
#define HW11_BONUS_2
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct _StringListNode {
	struct _StringListNode* next;
	char*                   filename;
} StringListNode;

typedef struct _IndexBSTNode {
	char*                   word;
	StringListNode*         filenames;
	struct _IndexBSTNode*   left;
	struct _IndexBSTNode*   right;
} IndexBSTNode;

typedef struct {
	IndexBSTNode*           root;
	// You may add more fields to this, if you like.
} Index;

Index create_index();
void put(Index* index, char* word, char* filename);
char** get(Index* index, int* count, char* word, ...);
void free_index(Index* index);

char* strdup_(const char* s); // you may uncomment if you are using this

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
