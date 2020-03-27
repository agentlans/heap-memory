#include <stdio.h>

#include "HeapMemory.h"

int main()
{
	// Set up some space on the heap
	hm heap_mem;
	hm_init(&heap_mem);

	// Put an integer on the heap
	int *foo = hm_set_int(&heap_mem, 3);
	(*foo)++;
	printf("%d\n", *foo);
	// Remove that pointer for now
	hm_free_pointer(&heap_mem, foo);
	foo = NULL;

	// Put many integers on the heap
	for (int i = 0; i < 1000; ++i) {
		hm_set_int(&heap_mem, 3);
	}

	// Put a double on the heap
	double *pi = hm_set_double(&heap_mem, 3.14159);

	// Write a string to the heap
	char **msg = hm_set_string(&heap_mem, "Hello world!");
	printf("%s\n", *msg);

	// Free all the aforementioned stuff on the heap
	hm_free(&heap_mem);

	return 0;
}

