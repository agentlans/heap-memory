#ifndef _HEAPMEMORY
#define _HEAPMEMORY

#include <stdlib.h>
#include <string.h>

// Array of pointers to heap memory
typedef struct hm_heapmemory
{
	void **arr;
	size_t size; // Number of pointers it has
	size_t capacity; // Number of pointers it can hold
} hm;

// Initializes the heap memory object
void hm_init(hm *hmem);

/* Allocates space on the heap for an element of specified number of bytes
 and sets it to a given value. */
int hm_set(hm *hmem, void **new_ptr, size_t size, void *value);

// Frees the pointer and removes it from the HeapMemory's records.
// If the pointer isn't managed by HeapMemory, then it does nothing.
void hm_free_pointer(hm *hmem, void *p);

// Frees all pointers allocated using the hm_set function
void hm_free(hm *hmem);

/* Allocates a variable in heap memory and returns a pointer to that variable.
  If there's a problem during allocation, returns null pointer.
  Note: Don't use strcat on a string allocated with hm_set_string! */
int *hm_set_int(hm *hmem, int value);
double *hm_set_double(hm *hmem, double value);
char **hm_set_string(hm *hmem, char *value);

#endif

