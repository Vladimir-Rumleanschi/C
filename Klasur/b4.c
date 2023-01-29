#include "base.h"

typedef  struct Treenode{
    char* str;
    struct Treenode* left;
    struct Treenode* right;
}Treenode; 


typedef struct Tree{
    int count;
    int depth;
    Treenode* root;
}Tree;


Treenode* new_node(char* str, Treenode* left, Treenode* right){
    Treenode* tree = xmalloc(sizeof(Treenode));
    tree->str = str;
    tree->left = left;
    tree->right = right;
    return tree;
}

Tree* new_tree(char* str, Treenode* left, Treenode* right){
    Tree* tree = xmalloc(sizeof(Tree));
    tree->count = 0;
    tree->depth = 0;
    tree->root = new_node(str,left,right);
    return tree;
}

Treenode* insert_in_node(Treenode* tr, char* str){
    if (tr == NULL){
        tr == new_node(str,NULL,NULL);
        return tr;
    }
    if (s_compare(str,tr->str) < 0){
        insert_in_node(tr->left,str);
    }
    if (s_compare(str,tr->str) > 0){
        insert_in_node(tr->right,str);
    }
    return tr;
}
int maxDepth(struct Treenode* node)
{
    if (node == NULL)
        return -1;
    else {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
 
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}
 

Tree* insert(char* str , Tree* tree){
    tree->root = insert_in_node(tree->root, str);
    tree->count++;
    tree->depth = maxDepth(tree->root);
    return tree;
}

bool dege(Tree* tree){
    if(log2(tree->count) + 1 < tree->depth)return true;
    else return false;
}

void print (Treenode* tr, int depth){
    
}