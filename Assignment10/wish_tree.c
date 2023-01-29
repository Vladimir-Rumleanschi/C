/*
    make wish_tree
    ./wish_tree
    make wish_tree && ./wish_tree
*/

#include "base.h"


typedef struct Element Element;

void free_element(Element* element);


typedef struct Node{
    struct Node* next;
    char* value;
}Node;

/*
    Returns a pointer to a dynamically allocated node.
*/
Node* new_node(char* value, Node* next){
    Node* node = xmalloc(sizeof(Node));
    node->next = next;
    node->value = s_copy(value);
    return node;
}

/* 
    Releases the memory used by node. 
*/
Node* free_node(Node* node){
    Node* next = node->next;
    free(node->value);
    free(node);
    return next;
}

/*
    Returns the length of a list of nodes.
*/
int length(Node* node){
    int count = 0;
    while(node != NULL){
        count++;
        node = node->next;
    }
    return count;
}

/*
    Returns true if the list of nodes contains find.
*/
bool contains(Node* node, char* find){
    while(node != NULL){
        if(strcmp(node->value, find) == 0){
            return true;
        }
        node = node->next;
    }
    return false;
}


/* 
    A TreeNode has a left and right successor of type TreeNode. A successor TreeNode is a TreeNode or NULL
        
            TreeNode root
           /          \
          /            \
    TreeNode left      TreeNode right
    /       \       /           \
   ...      ...    ...          ...
*/

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    struct Element* element;
}TreeNode;

/*
    Returns a pointer to a dynamically allocated tree_node.
*/
TreeNode* new_tree_node(Element* element){
    TreeNode* bnode = xmalloc(sizeof(TreeNode));
    bnode->left = NULL;
    bnode->right = NULL;
    bnode->element = element;
    return bnode;
}

/*  todo: g)
    Releases the memory used by a tree_node and also frees the included element.
*/
void free_tree_node(TreeNode* tree){
    if (tree == NULL) {
        return;
    }
    if (tree->element != NULL) {
        free_element(tree->element);
    }
    free_tree_node(tree->left);
    free_tree_node(tree->right);
    free(tree);
}


//todo: b)
struct Element{
    char* wish;
    int  hkeit;
    Node* child;
};

//todo: b)
Element* new_element(char* wish, char* child){
    Element* element = xmalloc(sizeof(Element));
    element->wish = s_copy(wish);
    element->hkeit = 1; 
    element->child = new_node(child,NULL);
    return element;
}
//todo: g)
void free_element(Element* element){
    if (element != NULL) {
        free(element->wish);
    }
    while (element->child != NULL) {
        element->child = free_node(element->child);
    }
}
//todo: c)
TreeNode* add_wish(TreeNode* tree, char* wish, char* child){
    if (tree == NULL){
        tree = new_tree_node(new_element(wish,child));
        return tree;
    } else if (strcmp(tree->element->wish,wish) == 0){
        tree->element->hkeit++;
        tree->element->child = new_node(child,tree->element->child);
    } else if (strcmp(tree->element->wish,wish) < 0){
        if(tree->left == NULL){
            tree->left = new_tree_node(new_element(wish,child));
        } else {
            add_wish(tree->left,wish,child);
        }
    } else if (strcmp(tree->element->wish,wish) > 0){
        if(tree->right == NULL){
            tree->right = new_tree_node(new_element(wish,child));
        } else {
            add_wish(tree->right,wish,child);
        }
    }
    return tree;
}

typedef struct ElementNode{
    struct ElementNode* next;
    Element* element;
}ElementNode;

ElementNode* new_element_node(Element* element, ElementNode* next){
    ElementNode* en = xmalloc(sizeof(ElementNode));
    en->next = next;
    en->element = element;
    return en;
}
//todo: g)
void free_element_list(ElementNode* en){
    if(en == NULL) {
        return;
    }
    if(en->element != NULL) {
        free_element(en->element);
    }
    free_element_list(en->next);
    free(en);
}

void print_element_list(ElementNode* list, int n){
    printf("%55s\t%6s\n", "Wunsch", "Anzahl");
    while(n > 0 && list != NULL){
        //printf("%55s\t%6d\n", list->element->wish, list->element->count); 
        n--;
        list = list->next;
    }
}

//todo: e)
ElementNode* insert_ordered_by_count(ElementNode* result, TreeNode* tree){
    return NULL;
}

//todo: d)
void print_tree_as_list(TreeNode* tree){
    if (tree == NULL){
        return;
    } 
    print_tree_as_list(tree->left);
    
    int shift = 53 - strlen(tree->element->wish);
    for (int i=0; i < shift; i++) {
        printf(" ");
    }
    printf("%s\t", tree->element->wish);
    printf("%d \t", tree->element->hkeit);
    Node *templist = tree->element->child;
    for(int i = 0; i < tree->element->hkeit; i++){
        printf("%s ", templist->value);
        templist = templist->next; 
    }
    printf("\n");
    print_tree_as_list(tree->right);
}

// Skips the rest of the current line.
char* skip_line(char* s) {
    while (*s != '\n' && *s != '\0') s++;
    if (*s == '\n') s++;
    return s;
}

// Skips the current token.
char* skip_token(char* s) {
    while (*s != ',' && *s != '\n' && *s != '\0') s++;
    return s;
}
// Skips spaces.
char* skip_spaces_and_commas(char* s) {
    while (*s == ' ' || *s == ',') s++;
    return s;
}


// Create a new token from s (inclusive) to t (exclusive).
char* new_token(char* s, char* t) {
    char* token = xmalloc(t - s + 1);
    int i = 0;
    while (s < t) {
        token[i] = *s;
        i++;
        s++;
    }
    token[i]= '\0';
    return token;
}

// Returns a new token by first skipping spaces and commas and then reading the token. 
// Sets *s to the first character after the token.
char* next_token(/*INOUT*/char** s) {
    *s = skip_spaces_and_commas(*s);
    char* t = skip_token(*s);
    char* token = new_token(*s, t);
    *s = t; // set *s to the character after the token
    return token;
}


/* 
    This function reads in one line of the wish text file and adds the wishes of a child to tree.
*/
TreeNode* read_wish_list(char** s, TreeNode* tree){
    char* child = next_token(s);
    
    while(**s != '\0' && **s != '\n'){
        char* wish = next_token(s);
        *s = skip_spaces_and_commas(*s);
        tree = add_wish(tree, wish, child); 
        free(wish);
    }
    
    free(child);
    return tree;
}

/*  
    This function reads the whole file and uses the read_wish_list function to parse a single line.
*/
TreeNode* read_wishes(char* filename, TreeNode* tree){
    char* file = s_read_file(filename);
    char* s = file;
    s = skip_line(s);
    while(*s != '\0'){
        tree = read_wish_list(&s, tree);
        s = skip_line(s);
        
    }
    free(file);
    return tree;
}


int main(int argc, char** argv){
    report_memory_leaks(true);
   
    
    TreeNode* tree = read_wishes("wishes.txt", NULL);
    for (int i=0; i < 48; i++) {
        printf(" ");
    }
    printf("Wunsh   Anzahl  Kinder\n");
    print_tree_as_list(tree);
    
    //ElementNode* sorted_by_count = insert_ordered_by_count(NULL, tree);
    
    
    //print_element_list(sorted_by_count, 10);
    
    
    //todo: f)
    
    //todo: g)
    
    free_tree_node(tree);

    return 0;
}
