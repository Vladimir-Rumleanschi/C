#include "base.h"

typedef struct Node {
    int value;
    struct Node*next;
} Node;

Node*new_node(int value, Node*next) {
    Node*node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

Node*reverse_rec(Node*list, Node*result) {
    if (list == NULL) {
        return result;
    } else {
        return reverse_rec(list->next, new_node(list->value, result));
    }
}

Node*reverse(Node*list) {
    return reverse_rec(list, NULL);
}

void pos_neg_list(Node*list, Node**pos, Node**neg) {
    if (list == NULL){
        return;
    }
    for (Node* node = list; node ; node = node->next){
        if(node->value > 0){
            *pos = new_node(node->value,*pos);
        } else if (node->value < 0) {
            *neg = new_node(node->value,*neg);
        }
    }
    *pos = reverse(*pos);
    *neg = reverse(*neg);

}

void test(void) {
    Node*list,*pos,*neg;
    list = new_node(0, new_node(1, new_node(-1,new_node(34, new_node(-56, NULL)))));
    pos = NULL;
    neg = NULL;
    pos_neg_list(list, &pos, &neg);
    // pos: [34, 1] (Reihenfolge beliebig)
    // neg: [-56, -1] (Reihenfolge beliebig)
    list = new_node(0, NULL);
    pos = NULL;
    neg = NULL;
    pos_neg_list(list, &pos, &neg);
    // pos: []
    // neg: []
}


int main(void) {
    test();
    return 0;
}

