#include "dyn_list.h"

Node* new_node(void* value, Node* next) {
    Node* n = xcalloc(1, sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}
