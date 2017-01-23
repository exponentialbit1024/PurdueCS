/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct BSTofIntNode{
	struct BSTofIntNode *left;
	struct BSTofIntNode *right;
	int value;
} BSTofIntNode;

typedef struct BSTofStringsNode{
	struct BSTofStringsNode *left;
	struct BSTofStringsNode *right;
	char *value;
} BSTofStringsNode;

char* _strdup(const char* s) {  // helper function;  okay to use anywhere in this assignment
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

char string_compare(const char* s1, const char* s2) {
	int compareChecker = strcmp(s1, s2);
	if(compareChecker < 0){
		return '<';
	}
	else if(compareChecker > 0){
		return '>';
	}
	else{
		return '=';
	}
	return EXIT_FAILURE;
}

static BSTofIntNode *_intNodeCreator(int val){
	BSTofIntNode *newNode;
	newNode = malloc(sizeof(BSTofIntNode));
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> value = val;
	return newNode;
}

static BSTofIntNode *_add_int_to_bst(BSTofIntNode *node, int val){
	if(node == NULL){
		return _intNodeCreator(val);
	}
	
	if(val <= (node -> value)){
		node -> left = _add_int_to_bst(node -> left, val);
	}
	else{
		node -> right = _add_int_to_bst(node -> right, val);
	}
	return node;
}

BSTofIntNode* create_bst_of_int(int* array_of_ints, size_t count) {
	BSTofIntNode *rootNode = _intNodeCreator(array_of_ints[0]);
	BSTofIntNode *traverser = rootNode;
	for(int j = 1; j < count; j++){
		traverser = _add_int_to_bst(traverser, array_of_ints[j]);
	}
	return rootNode; 
}

static BSTofStringsNode *_stringNodeCreator(char *val){
	BSTofStringsNode *newNode;
	newNode = malloc(sizeof(BSTofStringsNode));
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> value = val;
	return newNode;
}

static BSTofStringsNode *_add_string_to_bst(BSTofStringsNode *node, char *val){
	if(node == NULL){
		return _stringNodeCreator(val);
	}
	char compareChar = string_compare(val, node -> value);
	if(compareChar == '>'){
		node -> right = _add_string_to_bst(node -> right, val); 
	}
	else{
		node -> left = _add_string_to_bst(node -> left, val);
	}
	return node;
}

BSTofStringsNode* create_bst_of_strings(char** array_of_strings, size_t count) {
	BSTofStringsNode *rootNode = _stringNodeCreator(array_of_strings[0]);
	BSTofStringsNode *traverser = rootNode;
	for(int j = 1; j < count; j++){
		traverser = _add_string_to_bst(traverser, array_of_strings[j]);
	}
	return rootNode;
}

void print_bst_of_int(BSTofIntNode* root) {
	if(root == NULL){
		return;
	}
	
	print_bst_of_int(root -> left);
	printf("%d\n", root -> value);
	print_bst_of_int(root -> right);
}

void print_bst_of_strings(BSTofStringsNode* root) {
	if(root == NULL){
		return;
	}

	print_bst_of_strings(root -> left);
	printf("%s\n", root -> value);
	print_bst_of_strings(root -> right);
}

bool search_bst_of_int(BSTofIntNode* root, int value) {
	if(root == NULL){
		return false;
	}
	if(value == (root -> value)){
		return true;
	}
	if(value < (root -> value)){
		return search_bst_of_int(root -> left, value);
	}
	return search_bst_of_int(root -> right, value);
}

bool search_bst_of_strings(BSTofStringsNode* root, char* value) {
	if(root == NULL){
		return false;
	}

	if(strcmp(value, root -> value) == 0){
		return true;
	}
	if(strcmp(value, root -> value) < 0){
		return search_bst_of_strings(root -> left, value);
	}
	return search_bst_of_strings(root -> right, value);
}

void destroy_bst_of_int(BSTofIntNode* root) {
	if(root == NULL){
		return;
	}
	destroy_bst_of_int(root -> left);
	destroy_bst_of_int(root -> right);
	free(root);
}

void destroy_bst_of_strings(BSTofStringsNode* root) {
	if(root == NULL){
		return;
	}
	destroy_bst_of_strings(root -> left);
	destroy_bst_of_strings(root -> right);
	free(root);
}

int main(int argc, char *argv[]) {
	if(argc == 4 && strcmp(argv[1], "wusc") == 0) {
		printf("%c\n", string_compare(argv[2], argv[3]));
	}
	else if(argc == 2 && strcmp(argv[1], "wubi") == 0) {

		// Values to be added to the BST of integers
		int integers[] = {9, 7, 0, 3, 1, 6, 6, 4};
		size_t num_ints = sizeof(integers) / sizeof(integers[0]);
		assert(num_ints == 8);

		// Create BST of integers
		BSTofIntNode* bst_of_int_root = create_bst_of_int(integers, num_ints);

		// Print BST of integers
		print_bst_of_int(bst_of_int_root);
		// Output:
		//   0
		//   1
		//   3
		//   4
		//   6
		//   6
		//   7
		//   9

		// Try searching for several integers, as a test.
		for(int value = 1; value <= 5; value++) {
			if(search_bst_of_int(bst_of_int_root, value)) {
				printf("%d\n", value);
			}
		}
		// Output:
		//   1
		//   3
		//   4

		// Free the memory held by this BST.
		destroy_bst_of_int(bst_of_int_root);
	}
	else if(argc == 2 && strcmp(argv[1], "wubs") == 0) {

		// Values to be added to the BST of strings
		char* strings[] = {"jam", "ham", "egg", "oat", "nut", "tea"};
		size_t num_strings = sizeof(strings) / sizeof(strings[0]);
		assert(num_strings == 6);

		// Create BST of strings
		BSTofStringsNode* bst_of_strings_root = create_bst_of_strings(strings, num_strings);
		
		// Print BST of strings in order
		print_bst_of_strings(bst_of_strings_root);
		// Output:
		//   egg
		//   ham
		//   jam
		//   nut
		//   oat
		//   tea

		// Try searching for several strings, as a test.
		char* strings_to_find[] = {"jam", "bun", "pie", "tea"};
		size_t num_strings_to_find = sizeof(strings_to_find) / sizeof(strings_to_find[0]);
		for(int i = 0; i < num_strings_to_find; i++) {
			if(search_bst_of_strings(bst_of_strings_root, strings_to_find[i])) {
				printf("%s\n", strings_to_find[i]);
			}
		}
		// Output:
		//   jam
		//   tea

		// Free the memory held by this BST (including the copied strings).
		destroy_bst_of_strings(bst_of_strings_root);
	}
	else {
		printf("Invalid arguments.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
