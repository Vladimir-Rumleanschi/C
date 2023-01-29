/*
Compile: make integer_tree_test
Run: ./integer_tree_test
make integer_tree_test && ./integer_tree_test
*/

#include "integer_tree.h"

void get_odd_even_rec(BTNode* tree, Node** odd, Node** even){
	// (d) todo: implement
    // 
    if( tree  == NULL){
        return;
    } 
    if(tree->value % 2 == 0){
        *even = append_list(*even,tree->value);
    } else {
        *odd = append_list(*odd,tree->value);
    }
    get_odd_even_rec(tree->left, odd, even);
    get_odd_even_rec(tree->right, odd, even);
}

//Option type
typedef struct{
	bool valid;
	int value;
} Option_int; 

// Creates a new option int 
Option_int make_option_int(bool valid, int value){
	Option_int option_int;
	option_int.valid = valid;
	option_int.value = value;
	return option_int;
}

bool odd_or_even( int treevalue , void* x ){
        int* n = (int*)x;
        int erg = treevalue % 2;
        return erg == *n;
    }
bool is_sort2(BTNode* node, int reval,bool from_right){
    if(node == NULL) return true;
    bool temp = true;
    bool temp2 = true;
    if(node->left != NULL){
        if(node->value <= node->left->value ){
            return false;
        }else if (from_right && node->left->value <= reval){
            return false;
        }else temp = is_sort2(node->left,node->value,false);
    }
    if(node->right != NULL){
        if(node->value >= node->right->value){
            return false;
        }else if (!from_right && node->right->value >= reval){
            return false;
        }else temp2 = is_sort2(node->right,node->value,true);
    }
    return temp && temp2;
}

bool is_sorted(BTNode* node){
	// (f) todo: implement
	if(node == NULL) return true;
    bool temp = true;
    bool temp2 = true;
    if(node->left != NULL){
        if(node->value <= node->left->value) return false;
        else temp = is_sort2(node->left,node->value,false);
    }
    if(node->right != NULL){
        if(node->value >= node->right->value) return false;
        else temp2 = is_sort2(node->right,node->value,true);
    }
    return temp && temp2;
}


int main(void) {
    report_memory_leaks(true);

    int values[] = { 22, 44, 19, 8, 97, 36, 56, 33, 29 };
    int n = sizeof(values) / sizeof(int);
	
	printiln(n);
    
    // (a) todo: implement
    BTNode* t = NULL;
    for(int i = 0; i < n; i++){
        t = insert_ordered_tree( t,  values[i]);
    }
    println_tree(t); // Damit man die Inforamation eines Pointer übertragen kann,sonst geht die Information verloren. 

    BTNode* t2 = new_btnode(0, new_btnode(1, new_btnode(11, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, new_btnode(7, NULL, NULL)));
    println_tree(t2);
    free_tree(t2);
    
	// (c) todo: implement
    
    
    // (d) todo: implement
	Node* even = NULL;
	Node* odd = NULL;
	
	get_odd_even_rec(t, &odd, &even);
    printf("Even elements:\n");
	println_list(even);
    free_list(even);
	printf("Odd elements:\n");
	println_list(odd);
    free_list(odd);
	
    // (e) todo: implement
	Node* list = NULL;
    int x = 0;

    list =  filter_tree( t, odd_or_even, &x, list);
    println_list(list);
    free_list(list);
	
	
    // (f) todo: check:
	BTNode* t_sorted = NULL;
	
	printbln(is_sorted(NULL));
    test_equal_b(is_sorted(NULL), true);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, NULL, NULL);
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), true);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(55, NULL, NULL), 
                new_btnode(55, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(48, NULL, NULL), 
                new_btnode(55, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(1, NULL, NULL), 
                new_btnode(6, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
		t_sorted = new_btnode(48, 
				new_btnode(1, NULL, NULL), 
                new_btnode(57, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), true);
    free_tree(t_sorted);
	
	
    
    BTNode* t3 = new_btnode(48, 
        new_btnode(11, 
            new_btnode(5, 
                new_btnode(1, NULL, NULL), 
                new_btnode(6, NULL, NULL)), 
            new_btnode(30, 
                new_btnode(29, NULL, NULL), 
                NULL)), 
        new_btnode(57, 
            new_btnode(51, 
                new_btnode(50, NULL, NULL), 
                NULL), 
            new_btnode(99, 
                NULL, 
                new_btnode(100, NULL, NULL))));
    printbln(is_sorted(t3));
    test_equal_b(is_sorted(t3), true);
    free_tree(t3);

    BTNode* t4 = new_btnode(10, 
        new_btnode(11, 
            new_btnode(20, 
                new_btnode(21, NULL, NULL), 
                new_btnode(20, NULL, NULL)), 
            new_btnode(30, 
                new_btnode(31, NULL, NULL), 
                NULL)), 
        new_btnode(20, 
            new_btnode(40, 
                new_btnode(50, NULL, NULL), 
                NULL), 
            new_btnode(30, 
                NULL, 
                new_btnode(100, NULL, NULL))));
    printbln(is_sorted(t4));
    test_equal_b(is_sorted(t4), false);
    free_tree(t4);


    free_tree(t);

    return 0;
}
