#include<stdio.h>
#include "index.h"

void print_index(IndexBSTNode *rootNode){
	if(rootNode == NULL){
		return;
	}
	print_index(rootNode -> left);
	printf("Word - %s\n", rootNode -> word);
	printf("Files - \n");
	StringListNode *fileprinter = rootNode -> filenames;
	while(fileprinter != NULL){
		printf("	%s\n", fileprinter -> filename);
		fileprinter = fileprinter -> next;
	}
	print_index(rootNode -> right);
}

int main(int argc, char *argv[]){
	Index testIndex1 = create_index();
	put(&testIndex1,"code","a.txt");
	put(&testIndex1,"clean","b.txt");
	put(&testIndex1,"clean","d.txt");
	put(&testIndex1,"write","a.txt");
	print_index(testIndex1.root);
	
	int tc = 0;
	char *testWord[2] = {"code", "clean"};
	char **getRes = get(&testIndex1,&tc,testWord[0],testWord[1],NULL);
	printf("Files with words \n");
	for(int k = 0; k < 2; k++){
		printf(" \"%s\"\n", testWord[k]);	
	}

	for(int j = 0; j < tc;j++){
		printf("	%s\n", getRes[j]);
	}

	free(getRes);
	free_index(&testIndex1);

	return EXIT_SUCCESS;
}
