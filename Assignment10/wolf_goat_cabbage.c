/*
Compile: make wolf_goat_cabbage
Run: ./wolf_goat_cabbage
make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"

// Represents a single list node. The value is dynamically allocated. The node 
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // todo: implement (Aufgabe 1)
    // (there will be memory leaks if this function is not yet implemented)
    if(list == NULL){
    return;
    } else { 
        if (list->next == NULL) {
            free(list->value);
            free(list);
        } else {
            free(list->value);
            Node *_list = list->next;
            while (_list != NULL) {
                Node *_temlist = _list;
                _list = _list->next;
                free(_temlist->value);
                free(_temlist);
            }
            free(list);
        }
    }      
}

bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}
// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}
// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // todo: implement (Aufgabe 1)
    bool Ergebniss;
  //  printf("%d %d\n",length_list(list1),length_list(list2));
    if (length_list(list1) > length_list(list2)){
        printf("Line %d: list1 is longer than list2.\n",line);
        Ergebniss = false;
    } else if (length_list(list1) < length_list(list2)){
        printf("Line %d: list1 is shorter than list2.\n",line);
        Ergebniss = false;
    } else if (length_list(list1) == length_list(list2)){
        if (length_list(list1) == 0) {
            printf("Line %d: The lists are equal.\n",line);
            Ergebniss = true;
        } else {
            for(int i = 0 ; list1 != NULL; i++ ){
              //  printf("%s %s \n", list1->value, list2->value);
                    char* string1 = list1->value;
                    char* string2 = list2->value;
                    if (*string1 == *string2){
                    list1 = list1->next;
                    list2 = list2->next;
                    } else {
                        printf("Line %d: The values at node %d differ: %s <-> %s.\n", line, i + 1 , list1->value, list2->value );
                        return false;
                    }
            }
                printf("Line %d: The lists are equal.\n",line);
                Ergebniss = true;

            }
        } 
    return Ergebniss;
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
    Node* list = NULL;
    test_equal_i(length_list(list), 0);
    list = new_node("hello", NULL);
    test_equal_i(length_list(list), 1);
    free_list(list);
    list = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_i(length_list(list), 3);
    free_list(list);
}

// Number of elements of the list.

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
    Node*list = new_node("first", new_node("second", new_node("third",new_node("third", NULL))));
    String string = "ciao";
    test_equal_i(index_list(list,string), -1);
    string = "first";
    test_equal_i(index_list(list,string), 0);
    string = "third";
    test_equal_i(index_list(list,string), 2);
    free_list(list);
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    // todo: implement (Aufgabe 1)
    require("String ist Null", s != NULL);
    char* string = s;
    //printf("%d\n",length_list(list));
    for(int i = 0 ; list != NULL; i++ ){
       // printf("%s\n",list->value);
        char* list_string = list->value;
        if (*list_string != *string){
        list = list->next;
        } else {
        return i;
        }
    }
    return -1;
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_lists(__LINE__, actual, expected);
    Node*list = new_node("first", new_node("second", new_node("zero",new_node("third", NULL))));
    Node*relist = new_node("first", new_node("second",new_node("third", NULL)));
    list = remove_list(list,2);
    test_equal_lists(220,list,relist);
    free_list(relist);
    free_list(list);
    Node*list2 = new_node("first", new_node("second", new_node("third", NULL)));
    Node*relist2 = new_node("first", new_node("second",new_node("third", NULL)));
    list2 = remove_list(list2,2);
    test_equal_lists(220,list2,relist2);
    free_list(relist2);
    free_list(list2);
    Node*list3 = new_node("first", new_node("second", new_node("zero", NULL)));
    Node*relist3 = new_node("first", new_node("second",new_node("zero", NULL)));
    relist3 = remove_list(relist3,2);
    test_equal_lists(220,list3,relist3);
    free_list(relist3);
    free_list(list3);
    Node*list4 = new_node("first", new_node("second", new_node("zero",new_node("third", NULL))));
    Node*relist4 = new_node("first", new_node("second",new_node("zero", NULL)));
    list3 = remove_list(list4,2);
    test_equal_lists(220,list4,relist4);
    free_list(relist4);
    free_list(list4);
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement (Aufgabe 1)
    require("Ungültige Index für remove", index >= 0 && index < length_list(list));
    require("Die Liste ist Leer", list != NULL);
    if( index == 0){
        
        Node* templist = list->next;
        free(list->value);
        free(list);
        return templist;
    } 
    int i = 0;
    for(Node* templist1 = list; templist1 != NULL; templist1=templist1->next){
        if(i  == index - 1){
            Node* relist = templist1->next; 
            if(relist == NULL){
                return list;
            }
            Node* templist2 = relist->next;
            free(relist->value);
            free(relist);
            templist1->next = templist2;   
            return list;
        }  
        i++;         
    }
    ensure("Ungültige Index für remove", length_list(list) != length_list(list) - 1 );
    return list;
}   

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank. 
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    Puzzle p = { new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT };
    return p;
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    Node* templeft;
    templeft =  p->left;
    printf("[");
    for(int i = 0; templeft != NULL; i++){
        printf(" %s ",templeft->value);
        templeft = templeft->next;
    }
    printf("] ");
    Node* tempboat;
    tempboat = p->boat;
    if(p->position == LEFT){
        printf("[");
        for(int i = 0; tempboat != NULL; i++){
            printf(" %s ",tempboat->value);
            tempboat = tempboat->next;
        }
        printf("] ");
        printf("\t\t[");
    } else {
        printf("\t\t[");
        for(int i = 0; tempboat != NULL; i++){
            printf(" %s ",tempboat->value);
            tempboat = tempboat->next;
        }
        printf("] ");
        printf("[");
    }
    Node* tempright;
    tempright = p->right;
    for(int i = 0; tempright != NULL; i++){
        printf(" %s ",tempright->value);
        tempright = tempright->next;
    }
    printf("] \n");
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    free_list(p->left);
    free_list(p->boat);
    free_list(p->right);
    exit(0);
}

void evaluate_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    if(length_list(p->right) == 3){
        printf("Die Aufgabe ist geloest.\n");
        finish_puzzle(p);
    } else {
       /* printf("hier");
        char* leftvalue = p->left->value;
        char* leftnextvalue = p->left->next->value;
        char* rightvalue = p->right->value;
        char* rightnextvalue = p->right->next->value;
        if ((leftvalue == wolf && leftnextvalue == ziege) || (leftvalue == ziege && leftnextvalue == wolf)){
            printf("Die Aufgabe ist durchgefallen: Wolf ist am linken Ufer allein mit der Ziege und frisst sie.\n");
            finish_puzzle(p);
        } else if ((rightvalue == wolf && rightnextvalue == ziege) || (rightvalue == wolf && rightnextvalue == ziege)){
            printf("Die Aufgabe ist durchgefallen: Wolf ist am rechten Ufer allein mit der Ziege und frisst sie.\n");
            finish_puzzle(p);
        } else if ((leftvalue == kohl && leftnextvalue == ziege) || (leftvalue == ziege && leftnextvalue == kohl)){
            printf("Die Aufgabe ist durchgefallen: Wolf ist am linken Ufer allein mit dem Kohl und frisst ihm.\n");
            finish_puzzle(p);
        } else if ((rightvalue == kohl && rightnextvalue == ziege) || (rightvalue == kohl && rightnextvalue == ziege)){
            printf("Die Aufgabe ist durchgefallen: Ziege ist am rechten Ufer allein mit dem Kohl und frisst ihm.\n");
            finish_puzzle(p);
        }*/
        if (((index_list(p->left,"Wolf") > -1 ) && (index_list(p->left,"Ziege") > -1 )) || ((index_list(p->left,"Ziege") > -1 ) && (index_list(p->left,"Wolf") > -1 ))){
            printf("Die Aufgabe ist durchgefallen: Wolf ist am linken Ufer allein mit der Ziege und frisst sie.\n");
            finish_puzzle(p);
        } else if(((index_list(p->right,"Wolf") > -1 ) && (index_list(p->right,"Ziege") > -1 )) || ((index_list(p->right,"Ziege") > -1 ) && (index_list(p->right,"Wolf") > -1 ))){
            printf("Die Aufgabe ist durchgefallen: Wolf ist am rechten Ufer allein mit der Ziege und frisst sie.\n");
            finish_puzzle(p);  
        } else if(((index_list(p->left,"Ziege") > -1 ) && (index_list(p->left,"Kohl") > -1 )) || ((index_list(p->left,"Kohl") > -1 ) && (index_list(p->left,"Ziege") > -1 ))){
            printf("Die Aufgabe ist durchgefallen: Ziege ist am linken Ufer allein mit dem Kohl und frisst ihm.\n");
            finish_puzzle(p);
        } else if(((index_list(p->right,"Ziege") > -1 ) && (index_list(p->right,"Kohl") > -1 )) || ((index_list(p->right,"Kohl") > -1 ) && (index_list(p->right,"Ziege") > -1 ))){
            printf("Die Aufgabe ist durchgefallen: Ziege ist am rechten Ufer allein mit dem Kohl und frisst ihm.\n");
            finish_puzzle(p);
        }
    }
}

void play_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    String quit = "q";
    String right = "r";
    String left = "l";
    print_puzzle(p);
    for(int i = 0; length_list(p->right) != 3 ; i++){
        String befehl = s_input(100);
        if (s_equals(befehl,quit)){
            s_free(befehl);
            finish_puzzle(p);
        } else {
            p->left = remove_list(p->left,index_list(p->left,befehl));
            p->boat = new_node(befehl,NULL);
            print_puzzle(p);
            s_free(befehl);
            befehl = s_input(100);
            if(s_equals(befehl,quit)){
                s_free(befehl);
                finish_puzzle(p);
            }else if (s_equals(befehl,right)){
                p->position = RIGHT;
                print_puzzle(p);
                s_free(befehl);
                evaluate_puzzle(p);
                befehl = s_input(100);
                if(s_equals(befehl,quit)){
                    s_free(befehl);
                    finish_puzzle(p);
                } else {
                    p->boat = remove_list(p->boat,index_list(p->boat,befehl));
                    p->right = new_node(befehl,p->right);
                    s_free(befehl);
                    print_puzzle(p);
                    befehl = s_input(100);
                 //   printf("hello");
                    if(s_equals(befehl,quit)){
                        s_free(befehl);
                        finish_puzzle(p);
                    } else if (s_equals(befehl,left)){
                        p->position = LEFT;
                        print_puzzle(p);
                        s_free(befehl);
                        evaluate_puzzle(p);
                    } else {
                        p->right = remove_list(p->right,index_list(p->right,befehl));
                        p->boat = new_node(befehl,NULL);
                        print_puzzle(p);
                        s_free(befehl);
                        befehl = s_input(100);
                        if(s_equals(befehl,quit)){
                            s_free(befehl);
                            finish_puzzle(p);
                        } else if (s_equals(befehl,left)){
                            p->position = LEFT;
                            print_puzzle(p);
                            s_free(befehl);
                            befehl = s_input(100);
                            if (s_equals(befehl,quit)){
                                s_free(befehl);
                                finish_puzzle(p);
                            } else {
                                p->boat = remove_list(p->boat,index_list(p->boat,befehl));
                                p->left = new_node(befehl,p->left);
                                print_puzzle(p);
                                s_free(befehl);
                            }    
                        }
                    }    
                }
            } 
        }    
    }
   
    // ...
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    report_memory_leaks(true);
    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();
    Puzzle p = make_puzzle();
    play_puzzle(&p);
    // Puzzle s = { new_node("Ziege", new_node("Kohl", NULL)), NULL, new_node("Wolf", NULL), RIGHT };
    //print_puzzle(&s);
    //evaluate_puzzle(&s);
    // Node* s =  new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL)));
    // print_list(s);
    // s = remove_list(s,2);
    // print_list(s);
    return 0;
}
