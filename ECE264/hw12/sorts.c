#include "sorts.h"

List create_list(const int *array, int size){
	List newList;
	newList.head = NULL;
	newList.tail = NULL;
	for(int j = 0; j < size; j++){
		ListNode *newNode = malloc(sizeof(*newNode));
		newNode -> next = NULL;
		newNode -> value = array[j];
		if(j == 0){
			newList.head = newNode;
			newList.tail = newList.head;
		}
		else{
			newList.tail -> next = newNode;
			newList.tail = newList.tail -> next;
		}
	}
	return newList;
}

void _mergeSplit(ListNode *source, ListNode **frontRef, ListNode **backRef){
	ListNode *fast;
	ListNode *slow;
	if (source==NULL || source->next==NULL){
		*frontRef = source;
		*backRef = NULL;
	}
	else{
		slow = source;
		fast = source -> next;
		while(fast != NULL){
			fast = fast -> next;
			if(fast != NULL){
				slow = slow -> next;
				fast = fast -> next;
			}
		}
		*frontRef = source;
		*backRef = slow -> next;
		slow -> next = NULL;
	}
}

ListNode *_sortedMerge(ListNode *refNode1, ListNode *refNode2){
	ListNode *sortRes = NULL;
	if(refNode1 == NULL){
		return refNode2;
	}	
	else if(refNode2 == NULL){
		return refNode1;
	}

	if(refNode1 -> value <= refNode2 -> value){
		sortRes = refNode1;
		sortRes -> next = _sortedMerge(refNode1 -> next, refNode2);
	}
	else{
		sortRes = refNode2;
		sortRes -> next = _sortedMerge(refNode1, refNode2 -> next);
	}
	return sortRes;
}

void _mergeSort_list_wrap(ListNode **ref){
	ListNode *tHead = *ref;
	ListNode *refNode1;
	ListNode *refNode2;
	if((tHead == NULL) || (tHead -> next == NULL)){
		return;
	}
	_mergeSplit(tHead, &refNode1, &refNode2);
	_mergeSort_list_wrap(&refNode1);
	_mergeSort_list_wrap(&refNode2);
	*ref = _sortedMerge(refNode1, refNode2);
}

void merge_sort_list(List *list){
	ListNode *tHead = list -> head;
	_mergeSort_list_wrap(&tHead);
	list -> head = tHead;
}

void empty_list(List *list){
	while(list -> head != NULL){
		ListNode *delNode = list -> head -> next;
		free(list -> head);
		list -> head = delNode;
	}
}

void merge_sort_array(int *array, size_t size){
	if(size == 0){
		return;
	}
	List tList = create_list(array, size);
	merge_sort_list(&tList);
	ListNode *trav = tList.head;
	for(int j = 0; j < size; j++){
		array[j] = trav -> value;
		trav = trav -> next;
	}
	empty_list(&tList);
}

static BSTNode *_intNodeCreator(int val){
	BSTNode *newNode;
	newNode = malloc(sizeof(*newNode));
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> value = val;
	return newNode;
}

static BSTNode *_addBSTNode(BSTNode *node, int val){
	if(node == NULL){
		return _intNodeCreator(val);
	}

	if(val <= (node -> value)){
		node -> left = _addBSTNode(node -> left, val);
	}
	else{
		node -> right = _addBSTNode(node -> right, val);
	}
	return node;
}

BST create_bst(const int *array, int size){
	BST bst;
	if(size == 0){
		bst.root = NULL;
		return bst;
	}
	BSTNode *rootNode = NULL;
	BSTNode *traverser = NULL;
	for(int j = 0; j < size; j++){
		traverser = _addBSTNode(traverser, array[j]);
		if(j == 0){
			rootNode = traverser;
		}
	}
	bst.root = rootNode;
	return bst; 
}

void _destroy_bst_helper(BSTNode *rootNode){
	if(rootNode == NULL){
		return;
	}
	_destroy_bst_helper(rootNode -> left);
	_destroy_bst_helper(rootNode -> right);
	free(rootNode);
}

void empty_bst(BST *bst){
	_destroy_bst_helper(bst -> root);	
}

void _inorderReturn(BSTNode *node, int *array, int *count){
	if(node == NULL){
		return;
	}
	_inorderReturn(node -> left,array,count);
	array[*count] = node -> value;
	(*count)++;
	_inorderReturn(node -> right, array, count);
}

void tree_sort_array(int *array, size_t size){
	if(size == 0){
		return;
	}
	BST	nBst = create_bst(array, size);
	int counter = 0;
	_inorderReturn(nBst.root, array, &counter);
	empty_bst(&nBst);		
}

int compareInt(const void *arg1, const void *arg2){
	const int * ptr1 = (const int *) arg1; 
  	const int * ptr2 = (const int *) arg2;  
	int val1 = * ptr1; 
  	int val2 = * ptr2;
	if (val1 < val2)  { 
		return -1; 
	}
	if (val1 == val2) { 
		return 0; 
	}
	return 1;
}

void quick_sort_array(int *array, size_t size){
	qsort(&array[0], size, sizeof(int), compareInt);	
}
