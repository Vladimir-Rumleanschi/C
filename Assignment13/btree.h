#ifndef __BTREE_H__
#define __BTREE_H__

#include "base.h"
#include "dyn_queue.h"
#include "dyn_stack.h"


struct BTNode;

typedef struct BTNode{
	int value;
	struct BTNode * left;
	struct BTNode * right;
}BTNode;

BTNode* new_BTNode(int value, BTNode* left, BTNode* right);

void free_Btree(BTNode* tree);

void* next_element_btree_s(void* state);

bool has_next_btree_s(void* state);


#endif