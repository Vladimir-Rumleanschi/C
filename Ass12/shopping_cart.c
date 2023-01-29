#include "pointer_list.h"

typedef enum {
    C_FOOD,
    C_BOOK,
    C_ELECTRONICS,
} Category;

// Data definition for a shopping list item
typedef struct {
    String name;
    Category cat;
    // The price is given in cents
    // E.g.: a value of 1000 indicates a price of 10.00€
    int price;
} Item;

// String, Category (enum), int -> Item *
// Create an item (constructor).
Item * new_item(String name, Category cat, int price) {
    Item * item = xmalloc(sizeof(Item));

    *item = (Item) {
        .name = s_copy(name),
        .cat = cat,
        .price = price,
    };

    return item;
}

// Item * -> Item *
// Create a copy of an Item.
void * copy_item(void * x) {
    // TODO: implement
    return NULL;
}

// Item* -> String
// String representation of a shopping cart Item.
String item_to_string(void* x) {
    Item * item = (Item *) x;
    size_t n = 100 + s_length(item->name);
    String text = xmalloc(n);

    String cat_string = "unknown";
    switch(item->cat) {
    case C_FOOD:
        cat_string = "Food";
        break;
    case C_BOOK:
        cat_string = "Book";
        break;
    case C_ELECTRONICS:
        cat_string = "Electronics";
        break;
    }

    snprintf(text, n - 1, "\"%s\" (%s) %d.%d€", item->name, cat_string, item->price / 100, item->price % 100);
    return text;
}

// Item * -> void
// Releases memory of an Item.
void free_item(void * x) {
    // TODO
}

// Item * -> bool
// Returns true if the item is an electronic device.
bool is_electronics(void* element, int i, void* x) {
    return false;
}

// Item * -> String
// Maps an Item to its name.
void* item_name(void* element, int i, void* x) {
    return "";
}

// Item * -> bool
// Returns true if the price is less than *x.
bool price_less_than(void* element, int i, void* x) {
    // TODO: explain each line
    Item * item = (Item *)element;
    int a = *(int *)x;
    return item->price < a;
}

// Item *, int, double * -> Item *
// Creates a new Item with a reduced price. x is in range of [0, 1].
void * reduce_price(void* element, int i, void* x){
    // TODO: implement
    return new_item("", 0, 0);
}

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

typedef struct {
    int n;
    int price_sum;
} Item_stats;

// Item_stats**, Item*, int -> void
// Computes the sum of the prices of items.
void item_stats(void* state, void* element, int index) {
    // todo: explain each line
    Item_stats ** s = (Item_stats **)state;
    Item * i = (Item *)element;
    if(*s == NULL){
        *s = xmalloc(sizeof(Item_stats));
        (*s)->n = 0;
        (*s)->price_sum = 0;
    }
    (*s)->n++;
    (*s)->price_sum += i->price;
}

// int*, Item*, int -> void
// Adds an Item's price to sum.
void add_prices(void* state, void* element, int index) {
    // todo: explain each line
    int * sum = (int *)state;
    Item * i = (Item *)element;
    *sum += i->price;
}

// Item *, Item * -> { <0, 0, >0 }
// Returns =0 if x and y are equal, <0 if x smaller than y, >0 otherwise.
int cmp_item_price(void* x, void* y) {
    // todo: implement
    return 0;
}

int main(void) {
    report_memory_leaks(true);

    Item * i1 = new_item("Algorithms and Data Structures", C_BOOK, 7500);
    Item * i2 = new_item("Game Console", C_ELECTRONICS, 55000);
    Item * i3 = new_item("Potatoes", C_FOOD, 250);
    Item * i4 = new_item("Headphones", C_ELECTRONICS, 8000);

    printsln("= shopping cart =");
    Node* list = new_node(i1, new_node(i2, new_node(i3, new_node(i4, NULL))));
    println_list(list, item_to_string);

    printsln("= first electronics item =");
    Item * found_item = find_list(list, is_electronics, NULL);
    if (found_item != NULL) {
        String s = item_to_string(found_item);
        printsln(s);
        free(s);
    }

    printsln("= first item cheaper than 10€ =");
    // TODO: implement

    printsln("= item names =");
    Node * names = map_list(list, item_name, NULL);
    println_list(names, string_to_string);
    free_list(names, NULL);

    printsln("= reduce prices =");
    double factor = 0.13;
    Node * list2 = map_list(list, reduce_price, &factor);
    println_list(list2, item_to_string);
    free_list(list2, free_item);

    printsln("= items less than 79€ =");
    // TODO: implement

    printsln("= total price =");
    int total_price = 0;
    reduce_list(list, add_prices, &total_price);
    printf("%d.%d€\n", total_price / 100, total_price % 100);

    printsln("= average price =");
    Item_stats * stats = NULL;
    reduce_list(list, item_stats, &stats);
    if(stats != NULL) {
        int avg = stats->price_sum / stats->n;
        printf("%d.%d€\n", avg / 100, avg % 100);
        free(stats);
    }

    printsln("= sorted by price =");
    Node * sorted_list = NULL;
    for (Node * n = list; n != NULL; n = n->next) {
        sorted_list = insert_ordered(sorted_list, n->value, cmp_item_price);
    }
    if(sorted_list != NULL) {
        println_list(sorted_list, item_to_string);
        free_list(sorted_list, NULL);
    }

    free_list(list, free_item);

    return 0;
}
