#include <stdlib.h>
#include <stdio.h>

// Circular linked lists.  

typedef int Item; //Written this way to be more portable.
typedef struct node *my_link;
typedef struct node {Item item; my_link next;} node;
typedef struct linked_list {my_link head; my_link tail;} linked_list; // For circular linked lists, the tail will point to the head.
					  			// This makes it easier to add links onto the end.  
					   			// (They are equal when just initiated)

typedef struct linked_list *Linked_list; 

my_link init_link(Item n) // Initializes a node pointing to NULL with label n. Returns pointer to the node.
{
	my_link x;
	x = (my_link)malloc(sizeof(node));
	x->next = NULL;
	x->item = n;
	return x;
}

// Inserts the link t between x and x->next.  
void insert_next(my_link x, my_link t)
{t->next = x->next; x->next = t;}

// Deletes the node after x and returns it.
my_link delete_next(my_link x) 
{
	my_link t = x->next;
	x->next = t->next;
	return t;
}

linked_list* init_linked_list(Item n) // Initializes a circular linked list with head = tail and label n.
{	
	linked_list* l = (linked_list*)malloc(sizeof(my_link));
	my_link head, tail;
	head = (my_link)malloc(sizeof(node));
	tail = head;
	head->item = n; head->next = head; //This is the circular part.
	tail = head;
	l->head = head; l->tail = tail;
	return l; 
}

void add_linked_list_end_(linked_list* l, my_link x) // Adds the link x to the linked list x at the tail.
{
	insert_next(l->tail, x);
	l->tail = x;
}

void add_linked_list_end(linked_list* l, Item n) // Initializes a new link with item field n and adds to the tail of l.
{
	my_link x = init_link(n); 
	add_linked_list_end_(l,x);
}


void free_link(my_link x)
{free(x);}

void free_linked_list(linked_list* l) // Frees the linked list.
{
	if (l == NULL)
	{
		free(l);
	 	return;     
	}  
	my_link x = l->head;
	my_link y = x->next;
	while (y != l->head)
	{
		free_link(x);
		x = y;
		y = x->next;
	}
	free_link(x);
	free(l);
}

void print_linked_list(linked_list* l) // Prints the linked list.
{
	printf("%d ", l->head->item);
	my_link t = l->head->next;
	while (t != l->head)
	{
		printf("%d ",t->item);
		t = t->next;
	}
	printf("\n");

}

