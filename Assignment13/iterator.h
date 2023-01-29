#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include "base.h"
#include "btree.h"
#include "tree.h"

typedef struct Iterator Iterator;

typedef bool (*Has_next_function) (void* state);
typedef void* (*Next_element_function) (void* state);
typedef void (*Free_function)(void* state);

typedef struct Iterator{
	void* state;
	Has_next_function has_next;
	Next_element_function next_element;
	Free_function free;
} Iterator;


bool has_next(Iterator* iterator);

void* next_element(Iterator* iterator);

void free_iterator(Iterator* iterator);



Iterator * get_iterator_pre_order_BT(BTNode* tree);

//todo:
Iterator * get_iterator_level_order_BT(BTNode* tree);
//todo:
Iterator * get_iterator_pre_order_T(TNode* tree);
//todo:
Iterator * get_iterator_level_order_T(TNode* tree);


//todo:
bool contains_tree(TNode* tree, String key);
//todo:
bool contains_Btree(BTNode* tree, int key);

#endif