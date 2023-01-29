#include "base.h"


typedef struct Node{
    char* value;
    struct Node* next;
} Node;

typedef struct Lkopf{
    int listn;
    char* fval;
    char* lval;
}Lkopf;

Node* new_node(char* val, Node* nnext){
    Node* node = xmalloc(sizeof(Node));
    node->value = val;
    node->next = nnext;
}
Lkopf new_listenkopf(int x , char* valf, char* vale){
    Lkopf* lk = xmaloc (sizeof(Lkopf));
    lk->listn = x;
    lk->fval = valf;
    lk->lval = vale; 
}

 void free_list(Node* node){
    Node* node_next = node->next;
    free(node->value);
    free(node);
    return free_list(node->next);
 }

Node* vor_list( Node* list, char* fele, Lkopf* lk){
    list = new_node(fele,list);
    lk->fval = fele;
    lk->listn = lk->listn + 1;
    return list;
}
Node* end_list( Node* list, char* eele, Lkopf* lk){
    if(list == NULL){
        lk->lval = eele;
        lk->listn = lk->listn + 1;
        return new_node(eele,NULL);
    }else {
        Node* n = list;
        while (n != NULL)n = n->next;
        n = new_node(eele,n);
        return list;   
    }
}
int lan_list( Node* list){
    int len ;
    for(Node* xlist = list; xlist != list; xlist = xlist->next){
        len++;
    }
    return len;
}
/* weil man Anzahl von lKOPF struct ablesen kann 
int lan_list(Lkopf* lk){
return lk->listn;
}
*/

Node* insert_list(Node* list, char* val,int x){
    require("die Liste ist kleiner als den Index", lan_list(list) <= x);
    Node* n = list;
    int i = 0;
    while ( i != x - 1)n = n->next;
    n->next = new_node(val,n->next);
    return list;
}

Node* remove_list(Node* list, int inx){
    require("die Liste ist kleiner als den Index", lan_list(list) <= inx);
    
    Node* n = list;
    int i = 0;
    while ( i != inx - 1)n = n->next;
    Node* templist = n;
    n->next = templist->next->next;
    free_list(templist);
    return list;

}

Node* insert_in_order( Node* list, char* val){
    int inx = 0;
    Node* temp = list;
    while(temp){
        if(temp->value[0] <= val[0]){
            insert_list(temp,val,inx);
            break;
        }else{
            inx++;
        }
    }
    return list;
}

bool equal_lists(Node* list1, Node* list2){
    if (lan_list(list1) < lan_list(list2))return false;
    if (lan_list(list1) > lan_list(list2))return false;
    while(list1 != NULL){
        if (s_compare(list1->value, list2->value) == 0){
            list1 = list1->next;
            list2 = list2->next;
        } else {
            return false;
        }
    return true;
    }  
} 

int sarch(Node* list, char* value){
    int inx = 0;
    while(list != NULL){
        if (s_compare(list->value, value) == 0){
            list = list->next;
            inx++;
        } else {
            return inx + 1;
        }
    }
}


