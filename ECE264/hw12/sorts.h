#include <stdlib.h>

typedef struct ListNode{
	struct ListNode *next;
	int value;
}ListNode;

typedef struct List{
	ListNode *head;
	ListNode *tail;
	int size;
}List;

typedef struct BSTNode{
	struct BSTNode *left;
	struct BSTNode *right;
	int value;
}BSTNode;

typedef struct BST{
	BSTNode *root;
	int size;
}BST;

void merge_sort_array(int *array, size_t size);
void tree_sort_array(int *array, size_t size);
void quick_sort_array(int *array, size_t size);
List create_list(const int *array, int size);
void merge_sort_list(List *list);
void empty_list(List *list);
BST create_bst(const int *array, int size);
void empty_bst(BST* bst);
