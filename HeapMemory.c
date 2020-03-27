#include "HeapMemory.h"

// Initializes the heap memory object
void hm_init(hm *hmem)
{
	const size_t initial_capacity = 10;
	hmem->arr = malloc(initial_capacity * sizeof(void *));
	hmem->size = 0;
	hmem->capacity = initial_capacity;
}

/* Allocates space on the heap for an element of specified number of bytes
 and sets it to a given value. */
int hm_set(hm *hmem, void **new_ptr, size_t size, void *value)
{
	if (hmem->arr == NULL) {
		// Heap memory object not initialized
		return 1;
	}
	// Allocate new element for the value
	void *ptr = malloc(size);
	if (ptr != NULL) {
		// Reached max capacity
		if (hmem->size == hmem->capacity) {
			size_t new_capacity = 2 * hmem->capacity;
			void *new_arr = realloc(hmem->arr,
				new_capacity * sizeof(void *));
			if (new_arr == NULL) {
				// Couldn't reallocate the array of pointers.
				// Error. Do nothing.
				free(ptr);
				return 1;
			} else {
				// Successfully reallocated the array
				hmem->arr = new_arr;
				hmem->capacity = new_capacity;
			}
		}
		(hmem->arr)[hmem->size] = ptr;
		memcpy(ptr, value, size);
		hmem->size++;
		// Copy the newly-allocated pointer to given variable
		if (new_ptr != NULL) {
			*new_ptr = ptr;
		}

		return 0;
	} else {
		// Couldn't allocate memory for new element
		return 1;
	}
}

// Frees the pointer and removes it from the HeapMemory's records.
// If the pointer isn't managed by HeapMemory, then it does nothing.
void hm_free_pointer(hm *hmem, void *p)
{
	void **a = hmem->arr;
	int c = hmem->size;
	for (int i = 0; i < c; ++i) {
		void *ptr = a[i];
		if (ptr == p) {
			// Free the pointer
			free(a[i]);
			/* Find the last element in collection 
			and put it into the freed pointer's place */
			a[i] = a[hmem->size - 1];
			a[hmem->size - 1] = NULL;
			hmem->size--;
			break;
		}
	}
}

// Frees all pointers allocated using the hm_set function
void hm_free(hm *hmem)
{
	// Free the pointers inside the struct
	int c = hmem->size;
	void **a = hmem->arr;
	for (int i = 0; i < c; ++i) {
		free(a[i]);
	}
	// Free the array holding the pointers
	free(hmem->arr);
}

// Allocates an integer in heap memory and returns a pointer to that integer.
// If there's a problem during allocation, returns null pointer.
int *hm_set_int(hm *hmem, int value)
{
	void *new_ptr;
	int status = hm_set(hmem, &new_ptr, sizeof(int), (void *) &value);
	if (status != 0) {
		// Couldn't set the integer
		return (int *) NULL;
	}
	return new_ptr;
}

// Allocates a double in heap memory and returns a pointer to that double.
// If there's a problem during allocation, returns null pointer.
double *hm_set_double(hm *hmem, double value)
{
	void *new_ptr;
	int status = hm_set(hmem, &new_ptr, sizeof(double), (void *) &value);
	if (status != 0) {
		// Couldn't set the double
		return (double *) NULL;
	}
	return new_ptr;
}

/* Allocates a string in heap memory and returns a pointer to that string.
  If there's a problem during allocation, returns null pointer.
  Important: it allocates only as much space as needed for the string and terminating null character.
    So don't use strcat on the string!
*/
char **hm_set_string(hm *hmem, char *value)
{
	void *new_ptr;
	size_t length = strlen(value) + 1; // One more char for the null character
	int status = hm_set(hmem, &new_ptr, sizeof(char)*length, (void *) &value);
	if (status != 0) {
		// Couldn't set the string
		return (char **) NULL;
	}
	return new_ptr;
}

