#ifndef LIST_H
#define LIST_H

// Interface for a circular linked list (denoted "Linked_list") implementation.
#include "list.c"

Linked_list init_linked_list(Item);
void add_linked_list_end(Linked_list, Item);
void print_linked_list(Linked_list);
void free_linked_list(Linked_list);

#endif
