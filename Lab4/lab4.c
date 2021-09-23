#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* sqrt */
#define maxStrSize 128

int sum( const int * const array, size_t n);
int is_prime( unsigned long num );


/* typedef struct list
{
	struct list* link;
	int value;
	
}list; */

typedef struct llist_t {
	int value;
	struct llist_t* next;
} llist_t;

/* typedef struct llist_t* llist_t_ptr; */

int main( int argc, char** argv ) {
	return 0;
}

 llist_t* list_create(){
	/* llist_t */ 
	return 0;
}
/*
list_add_front(){}
list_add_back(){}
list_get(){}
list_free(){}
list_length(){}
list_node_at(){}
list_sum(){} */