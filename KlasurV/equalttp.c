/*
make nodes_equal_to_parent && ./nodes_equal_to_parent
*/

#include "base.h"

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *new_node(Node *left, int value, Node *right)
{
    Node *node = xmalloc(sizeof(Node));
    node->left = left;
    node->value = value;
    node->right = right;
    return node;
}

void free_node(Node *node)
{
    if (node)
    {
        free_node(node->left);
        free_node(node->right);
        node->left = NULL;
        node->right = NULL;
        free(node);
    }
}

void print_node(Node *node)
{
    if (node == NULL)
    {
        printf("E");
    }
    else
    {
        printf("Node(");
        print_node(node->left);
        printf(", %d, ", node->value);
        print_node(node->right);
        printf(")");
    }
}

// Purpose statement.
int number_of_nodes_that_are_equal_to_their_parent(Node *node)
{
    // todo: implement
    if(node == NULL)return 0;
    if(node->left == NULL && node->right == NULL)return 0;
    int count = 0;
    if( node->right != NULL && node->left != NULL && node->value == node->right->value && node->value == node->left->value)count +=2;
    else if(node->right != NULL && node->value == node->right->value )count++;
    else if(node->left != NULL && node->value == node->left->value )count++;
   
    count += number_of_nodes_that_are_equal_to_their_parent(node->right) + number_of_nodes_that_are_equal_to_their_parent(node->left);   
    return count;
}

void test()
{
    Node *t = NULL;
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
    free_node(t);

    t = new_node(NULL, 100, NULL);
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
    free_node(t);

    t = new_node(new_node(NULL, 99, NULL), 100, new_node(NULL, 100, NULL));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
    free_node(t);

    t = new_node(new_node(NULL, 100, NULL), 100, new_node(NULL, 100, NULL));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 2);
    free_node(t);

    t = new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 100, NULL));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
    free_node(t);

    t = new_node(new_node(new_node(NULL, 25, NULL), 50, new_node(NULL, 75, NULL)), 100, new_node(new_node(NULL, 125, NULL), 150, new_node(NULL, 175, NULL)));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
    free_node(t);

    t = new_node(new_node(new_node(NULL, 0, NULL), 0, new_node(NULL, 0, NULL)), 0, new_node(new_node(NULL, 0, NULL), 0, new_node(NULL, 0, NULL)));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 6);
    free_node(t);

    t = new_node(NULL, 100, new_node(NULL, 100, NULL));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
    free_node(t);

    t = new_node(NULL, 100, new_node(NULL, 99, NULL));
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 0);
    free_node(t);

    t = new_node(new_node(NULL, 100, NULL), 100, NULL);
    test_equal_i(number_of_nodes_that_are_equal_to_their_parent(t), 1);
    free_node(t);
}

int main(void)
{
    report_memory_leaks(true);
    test();
    return 0;
}