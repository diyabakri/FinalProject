#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "types.h"

LinkedList* newLinkedList();

int LinkedList_getSize(LinkedList* list);

int LinkedList_append(LinkedList* list , void* data);

int LinkedList_prepend(LinkedList* list , void* data);

int LinkedList_insert(LinkedList* list , int index , void* data);

void* LinkedList_pop(LinkedList* list);

void* LinkedList_peak(LinkedList* list);

void* LinkedList_getAtIndex(LinkedList* list , int index);

void* LinkedList_remove(LinkedList* list , int index);

int LinkedList_find(LinkedList* list , void* data , int (*compareRoutine)(void* , void*));

void LinkedList_print(LinkedList* list , char* (*printRoutien)(void*));

void LinkedList_destroy(LinkedList* list , void (*dataDestroyRoutien)(void*));

#endif//LINKEDLIST_H_