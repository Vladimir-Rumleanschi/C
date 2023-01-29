#include "btree.h"


void* next_element_btree_s(void* state){
	Stack* stack = (Stack*) state;
	
	BTNode* btnode = (BTNode*) pop(stack);
	if(btnode->right){
		push(stack, btnode->right);
	}
	
	if(btnode->left){
		push(stack, btnode->left);
	}
	
	return &(btnode->value);
}

bool has_next_btree_s(void* state){
	Queue* queue = (Queue*) state;
	return !empty_queue(queue);	
}



//template
BTNode* new_BTNode(int value, BTNode* left, BTNode* right){
	BTNode* btnode = xmalloc(sizeof(BTNode));
	btnode->value = value;
	btnode->left = left;
	btnode->right = right;
	return btnode;
}

void free_Btree(BTNode* tree){
	if(tree){
		free_Btree(tree->left);
		free_Btree(tree->right);
		free(tree);
	}
}
//end template