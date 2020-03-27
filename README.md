# heap-memory
Manages variables allocated in heap memory

## Introduction
In C programming, it's often necessary to store data in heap memory instead of stack memory. For example, for large blocks of data with global scope. However, pointers to heap memory must be managed carefully. The pointers must be deallocated using `free` or else there will be memory leaks.

This library keeps track of pointers to heap memory so that they can be safely and conveniently allocated and deallocated.

This library helps avoid common pitfalls with pointers:
- forgetting to deallocate them
- `free`ing them multiple times

This library *does not* help with:
- dangling pointers (that is, a pointer to an object which has been destroyed).
    For example, this can happen if a pointer is copied before the pointer is deallocated.
- wild pointers (pointer to memory that hasn't been initialized).
   This library doesn't initialize the pointers. It only copies data to heap memory, initialized or not.
- accidentally dereferencing freed or null pointers
- pointers that it didn't allocate

Before using this library, please consider more established choices for your garbage collecting needs:
- Boehm garbage collector for C and C++
- C++ `unique_ptr`, `shared_ptr`, and Boost libraries
- Java, Python, and other languages with automatic garbage collection

## Install
It's a regular C header and implementation file.

## Use
Example file (`main.c`). No memory leaks as detected by valgrind.

```c
#include <stdio.h>

#include "HeapMemory.h"

int main()
{
	// Set up some space on the heap
	hm heap_mem;
	hm_init(&heap_mem);

	// Put an integer on the heap
	int *foo = hm_set_int(&heap_mem, 3);
	// We can play with the integer pointer
	(*foo)++;
	printf("%d\n", *foo);
	// Remove that pointer for now
	hm_free_pointer(&heap_mem, foo);

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
```

## Author, License
Copyright (C) 2020 Alan Tseng

Apache License, Version 2.0
