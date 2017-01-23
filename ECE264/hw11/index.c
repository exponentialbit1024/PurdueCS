#include<stdio.h>
#include "index.h"

Index create_index(){
	Index blankIndex;
	blankIndex.root = NULL;
	return blankIndex;
}

char *strdup_(const char *s){
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

static int llSearch(IndexBSTNode *rootNode, char *filename){
	StringListNode *traverser = rootNode -> filenames;
	while(traverser != NULL){
		if(strcmp(traverser -> filename, filename) == 0){
			return true;
		}
		traverser = traverser -> next;
	}
	return false;
}

static StringListNode *_subLLNodeCreator(char *filename){
	StringListNode *newFileNode = malloc(sizeof(StringListNode));
	newFileNode -> next = NULL;
	newFileNode -> filename = strdup_(filename);
	return newFileNode;
}

static IndexBSTNode *_indexNodeCreator(IndexBSTNode *rootNode, char *word, char *filename){
	IndexBSTNode *newNode;
	newNode = malloc(sizeof(IndexBSTNode));
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> word = strdup_(word);
	newNode -> filenames = _subLLNodeCreator(filename);
	return newNode;
}

static StringListNode *_llAppender(IndexBSTNode *rootNode, char *filename){
	StringListNode *thead = rootNode -> filenames;
	while(rootNode -> filenames -> next != NULL){
		 rootNode -> filenames = rootNode -> filenames -> next;
	}
	rootNode -> filenames -> next = _subLLNodeCreator(filename);
	rootNode -> filenames = thead;
	return rootNode -> filenames;
}

static IndexBSTNode *_insertNode(IndexBSTNode *rootNode, char *word, char *filename){
	if(rootNode == NULL){
		return _indexNodeCreator(rootNode, word, filename);
	}
	int strCompInt = strcmp(word, rootNode -> word);
	if(strCompInt == 0){
		bool isPresent = llSearch(rootNode, filename);
		if(!isPresent){
			rootNode -> filenames = _llAppender(rootNode, filename);
		}
		return rootNode;
	}
	if(strCompInt < 0){
		rootNode -> left = _insertNode(rootNode -> left, word, filename);
	}
	else if(strCompInt >0){
		rootNode -> right = _insertNode(rootNode -> right, word, filename);
	}
	return rootNode;
}

void put(Index *index, char *word, char *filename){
	index -> root = _insertNode(index -> root, word, filename);
}

static IndexBSTNode *_searchNode(IndexBSTNode *rootNode, char *word){
	if(rootNode == NULL){
		return NULL;
	}
	int strCompInt = strcmp(word, rootNode -> word);
	if(strCompInt == 0){
		return rootNode;
	}
	if(strCompInt < 0){
		return _searchNode(rootNode -> left, word);
	}
	return _searchNode(rootNode -> right, word);
}

static int _array_checker(char ** fileList, int count, char *filename){
	for(int j = 0; j < count; j++){
		if(strcmp(fileList[j], filename) == 0){
			return true;
		}
	}
	return false;
}

char **get(Index *index, int *count, char *word, ...){
	if(index -> root == NULL){
		return NULL;
	}
	va_list multiList, copyMultiList;
	va_start(multiList, word);
	va_copy(copyMultiList, multiList);
	char *currWord = word;

	StringListNode *fileCol;
	StringListNode *traverser;
	int c = 0;
	while(currWord != NULL){
		fileCol = _searchNode(index -> root, currWord) -> filenames;
		traverser = fileCol;
		while(traverser != NULL){
			c++;
			traverser = traverser -> next;
		}
		currWord = va_arg(multiList, char *);
	}
	(*count) = c;
	char **fileList = malloc(sizeof(*fileList) * c);
	currWord = word;
	int k = 0;
	while(currWord != NULL){
		fileCol = _searchNode(index -> root, currWord) -> filenames;
		traverser = fileCol;
		while(traverser != NULL){
			if(!_array_checker(fileList, k, traverser -> filename)){
				fileList[k] = traverser -> filename;
			}
			traverser = traverser -> next;
			k++;
		}
		currWord = va_arg(copyMultiList, char *);
	}

	va_end(multiList);
	va_end(copyMultiList);
	return fileList;
}

static void indexDestroy(IndexBSTNode *dnode){
	if(dnode == NULL){
		return;
	}
	indexDestroy(dnode -> left);
	indexDestroy(dnode -> right);
	
	//destroy linkedList
	while(dnode -> filenames != NULL){
		StringListNode *delNode = dnode -> filenames -> next;
		free(dnode -> filenames -> filename);
		free(dnode -> filenames);
		dnode -> filenames = delNode;
	}
	free(dnode -> word);
	free(dnode);
}

void free_index(Index *index){
	indexDestroy(index -> root);
}
