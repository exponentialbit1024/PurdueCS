#include <stdio.h>
#include "sorts.h"

int main(int argc, char *argv[]){
	int a[6] = {2,6,3,4,5,1};
	int b[6];
	int c[6];
	for(int q = 0; q < 6;q++){
		b[q] = a[q];
		c[q] = a[q];
	}
	List nList = create_list(a,6);
	merge_sort_list(&nList);
	ListNode *trav = nList.head;
	while(trav != NULL){
		printf("%d", trav -> value);
		trav = trav -> next;
	}
	empty_list(&nList);
	BST nBst = create_bst(b,6);
	tree_sort_array(b,6);
	printf("\n");
	for(int k = 0; k < 6; k++){
		printf("%d", b[k]);
	}
	empty_bst(&nBst);	
	quick_sort_array(c,6);
	printf("\n");
	for(int k = 0; k < 6;k++){
		printf("%d", c[k]);
	}
	return EXIT_SUCCESS;
}
