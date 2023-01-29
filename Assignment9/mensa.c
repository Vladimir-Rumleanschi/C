/*
Compile: make mensa
Run: ./mensa
Compile & run: make mensa && ./mensa
*/

#include "base.h"



struct Node {
    String value;
    struct Node* next; 
};
typedef struct Node Node;



Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); 
    node->next = next;
    return node;
}

/**
Prints the components of the given list.
*/
// todo: implement
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %s", n->value);
        }
        printf("]");
    }
}

/**
Print list followed by a newline.
*/
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

/**
Return the number of elements in the list.
*/
// todo: implement
int length_list(Node* list) {
    int len;
    if(list == NULL){
        len = 0;
        } else {
            len = 1 + length_list(list->next);
    }
    return len;
}

/**
Return the element at position.
*/
// todo: implement
String get_list(Node* list, int position) {
    if(position < 0){
        return NULL;
    }
    int nr = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if(nr == position){
            return node->value;
        }
        nr++; 
    }
    return NULL;

}

/**
Free all nodes of the list, including the values it contains.
*/
void free_list(Node* list) {
// todo: implement
    if(list != NULL){
        free_list(list->next);
        free(list->value);
        free(list);
    }
   
}

/**
Adds an element to the end of the list. Modifies the existing list.
*/
Node* append_list(Node* list, String value) {
// todo: implement
    if(list == NULL){
        return new_node(value, NULL);
    }
    Node* ivar = new_node(value, NULL); 
    Node* i;
    for (i = list; i != NULL; i = i->next) 
        {
        if(i->next == NULL) {
            i->next = ivar;
    	    break;
        }  
    }

    return list;
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    if (list == NULL || index < 0) return list;
    if (index == 0) { // remove first element of non-empty list
        Node* n = list->next;
        free(list->value);
        free(list);
        return n;
    }
    // return second or later element of non-empty list
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if (i + 1 == index) {
            Node* to_remove = node->next;
            if (to_remove == NULL) return list;
            Node* n = to_remove->next;
            free(to_remove->value);
            free(to_remove);
            node->next = n;
            return list;
        }
        i++;
    }
    return list;
}

/**
Today's menu.
*/
const String menu[] = { "Currywurst", "Spaghetti", "Vegi", "Eintopf", "Salat" };

/**
The number of items on the menu.
*/
const int menu_count = sizeof(menu) / sizeof(char*);

/**
The list of completed food from the kitchen, waiting to be served. Each time a food item is served, the kitchen prepares a new food item randomly from the menu.
*/
Node* food; // List(String)

/**
The list of students standing in line and waiting for food. Each entry contains a string for the food that this student wants.
*/
Node* students; // List(String)

/**
The reputation of the mensa. The player is a staff member of the mensa. The goal of the player is to maximize the reputation of the mensa. Actually serving a dish that was asked for increases the reputation of the mensa by 1. Serving the wrong dish decreases the reputation by 1. If a student asks for a dish that is on the menu but not ready to be served, the reputation of the mensa decreases by 2.
*/
int reputation = 0;

/**
Example output:
fertige Essen: [Spaghetti, Vegi, Salat, Salat, Vegi]
nächster Essenswunsch: Currywurst (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 
*/
void print_situation(void) {
    // todo: implement
    printf("fertige Essen: ");
    println_list(food);
    printf("naechster Essenswunsch: %s (%d hungrige Studierende warten)\n", students->value, length_list(students));
    printf("Reputation der Mensa: %d\n", reputation);
}

/**
Print final message, release all dynamically allocated memory, and exit the program.
Fertig für heute. Die Mensa schließt.
Finale Reputation der Mensa: 3
*/
void finish(void) {
// todo: implement
    printf("Fertig fuer heute. Die Mensa schliesst.\n");
    printf("Finale Reputation der Mensa: %d\n", reputation);

    free_list(food);
    free_list(students);

    exit(0);
}

void add_random_food(){
    //menu[random] = { "Currywurst", "Spaghetti", "Vegi", "Eintopf", "Salat" }; --> Node* food;
       
    //generated random 
    int rindex = i_rnd(menu_count);//0 - menu_length-1
    String random_food = menu[rindex];
    food = append_list(food, random_food);
}

void add_random_student(){
    int rindex = i_rnd(menu_count);
    String rfood = menu[rindex];
    students = append_list(students, rfood);
}

/**
Run the mensa simulation.

The mensa person then enters the (0-based) index from the list of food. -1 stands for "not available". -2 ends the program. 

Here is an example dialog:

fertige Essen: [Salat, Vegi, Vegi, Spaghetti, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 3
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 1
> -1
Spaghetti ist nicht da? Schade.
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Salat (2 hungrige Studierende warten)
Reputation der Mensa: -1
> 0
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Eintopf (2 hungrige Studierende warten)
Reputation der Mensa: 0
> 1
Vegi möchte ich nicht! Ich möchte Eintopf! Dann hole ich mir halt einen Döner!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Currywurst (1 hungrige Studierende warten)
Reputation der Mensa: -1
> 1
Vegi möchte ich nicht! Ich möchte Currywurst! Dann hole ich mir halt einen Döner!
Fertig für heute. Die Mensa schließt.
Reputation der Mensa: -2
*/
void run_mensa(void) {
    // todo: implement
    for(int food = 0; food < 5; food++)
    {
        add_random_food();
    }
    for(int food_wish = 0; food_wish < 3; food_wish++)
    {
        add_random_student();
    }
    
    print_situation();
    
    int i;
    while ((i = i_input()) >= -1) {
        if(i == -1){
            printf("%s, ist nicht da? Schade.\n", get_list(students, 0));
            students = remove_list(students, 0);
            reputation -= 2;
        } else if(i < length_list(food)){
            String essengegeben = get_list(food, i);
            String essengewunscht = get_list(students, 0);
            if(s_equals(essengegeben, essengewunscht)){
                printf("Vielen Dank! Ich liebe die Mensa!\n");
                reputation += 1;

                food = remove_list(food, i);
                students = remove_list(students, 0);

                add_random_food();
                add_random_student();

            } else {
                printf("%s moechte ich nicht! Ich moechte %s!\n", essengegeben, essengewunscht);
                reputation = reputation - 1;

                food = remove_list(food, i);
                students = remove_list(students, 0);

                add_random_food();
            }
        } else {
            int esslen = length_list(food);
            printf("Die Essensliste ist nur %d lang. Benutze index 0-%d!\n", esslen, esslen-1);
        }

        if(length_list(students) == 0){
            break;
        } 
        
        print_situation();
    }
    finish();
}

void testing(){
    Node* list = new_node("a", new_node("b", new_node("c", new_node("d", new_node("e", NULL)))));
    test_equal_i(length_list(list), 5);
    test_equal_s(get_list(list, 1), "b");
    //void* mem = malloc(80);

    //append
    Node* list2 = NULL;
    list2 = append_list(list2, "test");
    println_list(list2);


    list = append_list(list, "f");
    println_list(list);
    free_list(list);
    
    list = new_node("g", new_node("t", new_node("j", new_node("r", new_node("k", NULL)))));
    println_list(list);

    //free
    free_list(list);
    free_list(list2);
}

int main(void) {
    //testing();
    report_memory_leaks(true);
    run_mensa();
    return 0;
}
