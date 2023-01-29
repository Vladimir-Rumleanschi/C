#include "TOC.h"


//template
// Adds an element to the end of the list. Modifies the existing list.
Node* append_list(Node* list, TNode* value) {
    if (list == NULL) { // empty list
        return new_node(value, NULL);
    } else { // non-empty list
        Node* n = list;
        while (n->next != NULL) n = n->next; // find last element
        // assert: n != NULL && n->next == NULL
        n->next = new_node(value, NULL);
        return list;
    }
}

void add_subchapter(TNode* chapter, String subchapters[], int my_pages[], int size){
	if (chapter == NULL)
		return;
	for(int i = 0; i < size; i++){
		chapter->subchapters = append_list(chapter->subchapters, new_TNode(subchapters[i], my_pages[i], NULL));
	}
}

TNode* init_TOC(){
/* My Bachelor thesis
		1 Introduction
		1.1	Motivation
		1.2 Research Questions
		1.3 Goals
		2 Basics
		2.1 Mathematical Basics
		2.2 Related Work
		2.3 Interaction Techniques
		3 Concept
		3.1 Old System
		3.1.1 Structure
		3.1.2 Functions
		3.2 New System
		3.2.1 Functions
		3.2.2 Structure
		3.3 Changes
		3.3.1 Hardware Changes
		3.3.2 Software Changes
		4 Prototype
		4.1 Hardware
		4.2 Software
		5 Studies
		5.1 Study One
		5.1.1	Participants
		5.1.2	Setup
		5.1.3	Procedure
		5.2 Study Two
		5.2.1 	Setup
		5.2.2	Procedure
		5.2.3	Participants
		6 Evaluation
		6.1	Methods
		6.2 Results
		6.3	User Group
		7 Conclusion
		8 Literature
		9 Appendix
*/

	String title = "My Bachelor thesis";
	TNode* my_bachelor_thesis = new_TNode(title, 0, NULL);
	//				1, 2, 3, 4, 5, 6, 7, 8, 9
	int pages[] = { 1, 1, 1, 1, 1, 1, 2, 3, 25};
	String chapters[] = {"Introduction", "Basics", "Concept", "Prototype", "Studies", "Evaluation", "Conclusion", "Literature", "Appendix"};
	//                   1.1 1.2 1.3
	int pages_chap1[] = {2, 1, 3};
	String subchapters_chapt1[] = {"Motivation", "Research Questions", "Goals"};
	
	//                   2.1 2.2 2.3
	int pages_chap2[] = {3, 10, 5};
	String subchapters_chapt2[] = {"Mathematical Basics", "Related Work", "Interaction Techniques"};
	
	//                   3.1 3.2 3.3
	int pages_chap3[] = {4, 6, 3};
	String subchapters_chapt3[] = {"Old System", "New System", "Changes"};
	
	//                   3.1.1 3.1.2
	int pages_sub1chap3[] = {2, 2};
	String subchapters_sub1chapt3[] = {"Structure", "Functions"};
	
	//                   3.2.1 3.2.2
	int pages_sub2chap3[] = {2, 2};
	String subchapters_sub2chapt3[] = {"Functions", "Structure"};
	
	//                   3.3.1 3.3.2
	int pages_sub3chap3[] = {2, 2};
	String subchapters_sub3chapt3[] = {"Hardware Changes", "Software Changes"};
	
	//                   4.1 4.2
	int pages_chap4[] = {12, 8};
	String subchapters_chapt4[] = {"Hardware", "Software"};
	
	//                   5.1 5.2
	int pages_chap5[] = {1, 1};
	String subchapters_chapt5[] = {"Study One", "Study Two"};
	
	//                   5.1.1 5.1.2
	int pages_sub1chap5[] = {1, 3, 4};
	String subchapters_sub1chapt5[] = {"Participants", "Setup", "Procedure"};
	
	//                   5.2.1 5.2.2
	int pages_sub2chap5[] = {2, 2, 2};
	String subchapters_sub2chapt5[] = {"Setup", "Procedure", "Participants"};
	
	//                   6.1 6.2 6.3
	int pages_chap6[] = {4, 2, 4};
	String subchapters_chapt6[] = {"Methods", "Results", "User Group"};
	
	add_subchapter(my_bachelor_thesis, chapters, pages, 9);
	Node * n = my_bachelor_thesis->subchapters;
	
	add_subchapter(n->chapter, subchapters_chapt1, pages_chap1, 3);
	n = n->next;
	add_subchapter(n->chapter, subchapters_chapt2, pages_chap2, 3);
	n = n->next;
	add_subchapter(n->chapter, subchapters_chapt3, pages_chap3, 3);
	
	Node * nsub = n->chapter->subchapters;
	add_subchapter(nsub->chapter, subchapters_sub1chapt3, pages_sub1chap3, 2);
	nsub = nsub->next;
	add_subchapter(nsub->chapter, subchapters_sub2chapt3, pages_sub2chap3, 2);
	nsub = nsub->next;
	add_subchapter(nsub->chapter, subchapters_sub3chapt3, pages_sub3chap3, 2);
	
	n = n->next;
	add_subchapter(n->chapter, subchapters_chapt4, pages_chap4, 2);
	n = n->next;
	add_subchapter(n->chapter, subchapters_chapt5, pages_chap5, 2);
	
	nsub = n->chapter->subchapters;
	add_subchapter(nsub->chapter, subchapters_sub1chapt5, pages_sub1chap5, 3);
	nsub = nsub->next;
	add_subchapter(nsub->chapter, subchapters_sub2chapt5, pages_sub2chap5, 3);
	
	n = n->next;
	add_subchapter(n->chapter, subchapters_chapt6, pages_chap6, 3);
	
	return my_bachelor_thesis;
}

//end template

TNode * new_TNode(String name, int my_pages, Node* subchapters){
	//todo
	TNode* tnode = xmalloc(sizeof(TNode));
	tnode->my_pages = my_pages;
	tnode->name = s_copy(name);
	tnode->subchapters = subchapters;
	return tnode;
}

Node* new_node(TNode* chapter, Node* next){
	//todo
	Node* node = xmalloc( sizeof(Node));
    node->chapter = chapter;
    node->next = next;
    return node;
}

void free_TNode(TNode* chapter){
	//todo
	if(chapter == NULL){
		return;
	} else {
		free(chapter->name);
		free_Nodes(chapter->subchapters);
		free(chapter);
	}
}


void free_Nodes(Node* node){
	//todo
	while( node != NULL){
		if(node->chapter != NULL){
			free_TNode(node->chapter);
			Node* tempnode = node;
			node = node->next;
			free(tempnode);
		}
	}
}

void print_rec(TNode* toc, int* pages, int layer, String index){
	if(toc == NULL)return;
	printf("%s %s ",index,toc->name );
	if(strlen(toc->name) % 2 == 1){
		printf(" ");
	}
	for (int i = 0; i < (40 - strlen(toc->name)) / 2 + 11 - layer ; i++){
		printf(" .");
	}
	String nr = s_of_int(*pages);
	for(int e = 0; e < 4 - strlen(nr);e++){
		printf(" ");
	}
	free(nr);
	printf("%d\n", *pages);
	Node* tempnode = toc->subchapters;
	int ind = 1;
	String nr2 = s_concat(index,".");
	while(tempnode != NULL){
		String nr2_5 = s_of_int(ind);
		String nr3 =  s_concat(nr2, nr2_5);
		print_rec(tempnode->chapter,pages,layer + 1,nr3);
		free(nr3);
		free(nr2_5);
		*pages = *pages + tempnode->chapter->my_pages;
		ind++;
		tempnode = tempnode->next;
	}
	free(nr2);
}

void print_TOC(TNode* toc){
	//todo
	printf("%s \n",toc->name);
	Node* tempnode = toc->subchapters;
	int pag = 0;
	int* pages = &pag;
	int index = 1;
	while(tempnode != NULL){
		String nr = s_of_int(index);
		print_rec(tempnode->chapter,pages,0,nr);
		free(nr);
		*pages = *pages + tempnode->chapter->my_pages;
		index++;
		tempnode = tempnode->next;
	}
	//int i = 1;
	//int pages = 0;
	// Node* tempnode = toc->subchapters;
	// TNode* temptnode = tempnode->chapter;
	// while(tempnode != NULL){
	// 	int b = 1;
	// 	printf("%d %s ",i ,temptnode->name );
	// 	if(strlen(temptnode->name) % 2 == 1){
	// 		printf(" ");
	// 	}
	// 	for (int i = 0; i < (12 - strlen(temptnode->name)) / 2 + 29; i++){
	// 		printf(" .");
	// 	}
	// 	printf(" %d",pages);
	// 	printf("\n");
	// 	pages = pages + temptnode->my_pages;
	// 	Node* tempnode2 = temptnode->subchapters;
	// 	TNode* temptnode2 = tempnode2->chapter;
	// 	while(tempnode2 != NULL){
	// 		printf("%d.%d %s ",i,b,temptnode2->name );
	// 		if(strlen(temptnode2->name) % 2 == 1){
	// 			printf(" ");
	// 		}
	// 		for (int e = 0; e < (22 - strlen(temptnode2->name)) / 2 + 23; e++){
	// 			printf(" .");
	// 		}
	// 		printf(" %d",pages);
	// 		printf("\n");
	// 		pages = pages + temptnode2->my_pages;
	// 		tempnode2 = tempnode2->next;
	// 		printf("+\n");
	// 		temptnode2 = tempnode2->chapter;
	// 		printf("+\n");
	// 		b++;
	// 	}
	// 	tempnode = tempnode->next;
	// 	temptnode = tempnode->chapter;
	// 	i++;
	// }

}


int calculate_pages(TNode* toc){
	//todo
	int i = 0;
	for(Node* tempnode = toc->subchapters; tempnode != NULL ; tempnode = tempnode->next){
		i = i + calculate_pages(tempnode->chapter);
	}
	return i + toc->my_pages;
}



int main (void){
	report_memory_leaks(true);
	
	//Uncomment the lines, after the necessary functions are implemented.

	//init the TOC, need constructor functions from a)
	TNode* my_bachelor_thesis = init_TOC();
	
	// c) calculate the sum of pages.
	int pages = calculate_pages(my_bachelor_thesis);
	printf("The thesis has: %d pages.\n", pages);
	
	// d) print the TOC
	print_TOC(my_bachelor_thesis);
	
	
	// b) free the TOC
	free_TNode(my_bachelor_thesis);
	
	return 0;
}