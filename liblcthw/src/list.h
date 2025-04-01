#ifndef lcthw_List_h
#define lcthw_List_h

// struct ListNode;

#include <stdio.h>
typedef struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
	void *value;
} ListNode;

typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);
void List_push(List *list, void *value);
void *List_pop(List *list);

/*
* Adds element value to first index in list, other values gets pushed back
*/
void List_push_front(List *list, void *value);

void *List_pop_front(List *list);
void *List_remove(List *list, ListNode *node);

/*
 * Create a new copy of the passed in list
*/
List *List_copy(List *list_to_copy, size_t s);

/*
 * Merge additional into base
 */
void List_join(List *base, List *additional);

#define List_count(L) ((L)->count)
#define List_is_empty(L) (List_count(L) == 0)
#define List_first(L) ((L)->first != NULL ? (L)->first->value : NULL)
#define List_last(L) ((L)->last != NULL ? (L)->last->value : NULL)

#define LIST_FOREACH(LIST, FIRST, NEXT, CURR) \
	ListNode *_node = NULL;      \
	ListNode *CURR = NULL;          \
	for (CURR = _node = LIST->FIRST; _node != NULL; CURR = _node = _node->NEXT)


#endif