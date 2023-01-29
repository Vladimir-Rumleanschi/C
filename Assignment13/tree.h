#ifndef __TREE_H__
#define __TREE_H__

#include "base.h"
#include "dyn_queue.h"
#include "dyn_stack.h"

struct TNode;

typedef struct LNode {
    struct TNode* chapter;
    struct LNode* next;
} LNode;

typedef struct TNode {
    String name;
	int my_pages;
    LNode* subchapters;
} TNode;

TNode* new_TNode(String name, int my_pages, LNode* subchapters);

LNode* new_LNode(TNode* chapter, LNode* next);

void free_TNode(TNode* chapter);

void free_LNode(LNode* node);

void add_subchapter(TNode* chapter, String subchapters[], int pages[], int size);

TNode* init_TOC();






#endif