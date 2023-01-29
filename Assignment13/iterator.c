#include "iterator.h"

//template
bool has_next(Iterator* iterator){
	return iterator->has_next(iterator->state);	
}

void* next_element(Iterator* iterator){
	return iterator->next_element(iterator->state);	
}

void free_iterator(Iterator* iterator){
	iterator->free(iterator->state);
	free(iterator);
}
//end template


void free_stack_based_iterator(void* state){
	free_stack((Stack*) state);
}


Iterator * get_iterator_pre_order_BT(BTNode* tree){
	Iterator* iter = xmalloc(sizeof(Iterator));
	Stack* stack = new_stack();
	if(tree){
		push(stack, tree);
	}	
	iter->state = stack;
	iter->has_next = has_next_btree_s;
	iter->next_element = next_element_btree_s;
	iter->free = free_stack_based_iterator;
	return iter;
}

Iterator * get_iterator_level_order_BT(BTNode* tree){
	//todo
	return NULL;
}

Iterator * get_iterator_pre_order_T(TNode* tree){
	//todo
	return NULL;
}

Iterator * get_iterator_level_order_T(TNode* tree){
	//todo;
	return NULL;
}


bool contains_tree(TNode* tree, String key){
	//todo
	return false;
}

bool contains_Btree(BTNode* tree, int key){
	//todo
	return false;
}


int main (void){
	report_memory_leaks(true);
	BTNode* t = new_BTNode(4, new_BTNode(3, new_BTNode(2, NULL, NULL), NULL), new_BTNode(36, new_BTNode(18, NULL, NULL), new_BTNode(40, NULL, NULL)));
	/*tree structure
					  4
				/			\
				3				36
			/		\		/		\
			2		N		18		40
	*/
	
	
	
	printf("\nWalk over elements in level order:\n[");
	Iterator * iter = get_iterator_level_order_BT(t);
	while(iter && has_next(iter)){
		BTNode* element = next_element(iter);
		printf("%d ", element->value);
	}
	printf("]\n"); //should be: [4 3 36 2 18 40 ]
	
	if(iter)
		free_iterator(iter);
	
	printf("\nWalk over elements in pre order:\n[");
	iter = get_iterator_pre_order_BT(t);
	while(iter && has_next(iter)){
		BTNode* element = next_element(iter);
		printf("%d ", element->value);
	}
	printf("]\n"); //should be: [4 3 2 36 18 40 ]
	
	if(iter)
		free_iterator(iter);

	
	
	TNode* toc = init_TOC();
	printf("\nWalk over elements in level order:\n[");
	iter = get_iterator_level_order_T(toc);
	while(iter && has_next(iter)){
		TNode* element = next_element(iter);
		printf("\"%s\" ", element);
	}
	printf("]\n");
	//should be: ["My Bachelorthesis" "Introduction" "Basics" "Concept" "Prototype" "Studies" "Evaluation" "Conclusion" "Literature" "Apendix" "Motivation" "Research Questions" "Goals" "Mathematical Basics" "Related Work" "Interaction Techniques" "Old System" "New System" "Changes" "Hardware" "Software" "Study One" "Study Two" "Methods" "Results" "User Group" "Structure" "Functions" "Functions" "Structure" "Hardware Changes" "Software Changes" "Participants" "Setup" "Procedure" "Setup" "Procedure" "Participants" "Setup" "Procedure" "Participants" ]
	if(iter)
		free_iterator(iter);
	
	printf("\nWalk over elements in pre order:\n[");
	iter = get_iterator_pre_order_T(toc);
	while(iter && has_next(iter)){
		TNode* element = next_element(iter);
		printf("\"%s\" ", element);
	}
	printf("]\n");
	//should be: ["My Bachelorthesis" "Introduction" "Motivation" "Research Questions" "Goals" "Basics" "Mathematical Basics" "Related Work" "Interaction Techniques" "Concept" "Old System" "Structure" "Functions" "New System" "Functions" "Structure" "Changes" "Hardware Changes" "Software Changes" "Prototype" "Hardware" "Software" "Studies" "Study One" "Participants" "Setup" "Procedure" "Study Two" "Setup" "Setup" "Procedure" "Participants" "Procedure" "Participants" "Evaluation" "Methods" "Results" "User Group" "Conclusion" "Literature" "Apendix" ]
	if(iter)
		free_iterator(iter);
	
	
	printf("Find values...\n");
	
	test_equal_b(contains_Btree(t, 2), true);
	test_equal_b(contains_Btree(t, 3), true);
	test_equal_b(contains_Btree(t, 4), true);
	test_equal_b(contains_Btree(t, 5), false);
	test_equal_b(contains_Btree(t, 6), false);
	test_equal_b(contains_Btree(t, 36), true);
	test_equal_b(contains_Btree(t, 18), true);
	
	test_equal_b(contains_tree(toc, "My Bachelorthesis"), true);
	test_equal_b(contains_tree(toc, "Introduction"), true);
	test_equal_b(contains_tree(toc, "Prototype"), true);
	test_equal_b(contains_tree(toc, "Subchapter"), false);
	test_equal_b(contains_tree(toc, "test"), false);
	test_equal_b(contains_tree(toc, "Study Two"), true);
	test_equal_b(contains_tree(toc, "Evaluation"), true);
	
	
	free_Btree(t);
	free_TNode(toc);
	return 0;
}