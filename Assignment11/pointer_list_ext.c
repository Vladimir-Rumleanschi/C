/*
Compile: make pointer_list_ext
Run: ./pointer_list_ext
make pointer_list_ext && ./pointer_list_ext
*/

#include "pointer_list.h"

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// String -> void
// Releases a string.
void free_string(void* x) {
    free(x);
}

// Create a list consisting of the first n nodes of list.
Node* take_list(Node* list, int n) {
    Node* takelist = NULL;
    for(int i = 0; i < n; i++){
        takelist = insert_list(takelist,i,list->value);
        list = list->next;
    }
    return takelist; // todo; implement (a)
}

// Create a list consisting of nodes of list, except the first n.
Node* drop_list(Node* list, int n) {
    // Node* droplist = reverse_list(list);
    // droplist = take_list(droplist,n-1);
    // droplist = reverse_list(droplist);
    Node* droplist = NULL;
    int a = 0;
    for(int i = 0; list !=  NULL; i++){
        if(i >= n ){
            droplist = insert_list(droplist,a,list->value);
            list = list->next;
            a++;
        } else {
            list = list->next;
        }
      //  printf("%d",i);

    }
    return droplist; // todo; implement (b)
}

// Take alternatingly from list1 and list2 until all data is collected in the result.
Node* interleave(Node* list1, Node* list2) {
    Node* interlist = NULL;
    int len = length_list(list1) + length_list(list2);
    for( int i = 0; i < len; i++){
        if ( i % 2 == 0 ) {
            interlist = insert_list(interlist,i,list1->value);
            list1 = list1->next;
        } else {
            interlist = insert_list(interlist,i,list2->value);
            list2 = list2->next;
        }
    }
    return interlist; // todo; implement (c)
}

// typedef bool (*EqualFun)(void* element1, void* element2);

bool group_by_length(void* element1, void* element2) {
    String s1 = element1;
    String s2 = element2;
    return s_length(s1) == s_length(s2);
}

// Group elements in list. Equivalent elements (for which equivalent is true) are put
// in the same group. The result is a list of groups. Each group is itself a list.
// Each group contains items that are equivalend.
Node* group_list(Node* list, EqualFun equivalent) {
    Node* glist = new_node(new_node(list->value,NULL),NULL);
    list = list->next;
    while(list  != NULL){
        Node* templist = glist;
        while (glist != NULL){
            if(contains_list(glist->value,list->value,equivalent)){
                glist->value = append_list( glist->value,list->value);
                break;
            } else {
               glist = glist->next; 
            }
        }
        if (glist == NULL){
            glist = new_node(new_node(list->value,NULL),templist); 
        
        } else {
            glist = templist;
        }        
        list = list->next;
    }
    return glist; // todo; implement (d)
}

void free_group(void* x) {
    Node* list = x;
    free_list(list, NULL);
}

int main(void) {
    report_memory_leaks(true);
    
    Node* list = new_node("a", new_node("bb", new_node("ccc", new_node("dd", new_node("e", NULL)))));
    println_list(list, string_to_string);

    prints("take_list: ");
    Node* list2 = take_list(list, 3);
    println_list(list2, string_to_string);

    prints("drop_list: ");
    Node* list3 = drop_list(list, 3);
    println_list(list3, string_to_string);
    

    prints("interleave: ");
    Node* list4 = interleave(list2, list3);
    println_list(list4, string_to_string);
    

    Node* groups = group_list(list, group_by_length);
    printf("%d groups:\n", length_list(groups));
    for (Node* n = groups; n != NULL; n = n->next) {
        if (n->value != NULL) {
           println_list(n->value, string_to_string);
        }
    }
    
    free_list(list, NULL);
    free_list(list2, NULL);
    free_list(list3, NULL);
    free_list(list4, NULL);
    free_list(groups, free_group);
    
    return 0;
}
