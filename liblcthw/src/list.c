#include "list.h"

#include <stdlib.h>
#include <string.h>

#include "dbg.h"

List *List_create() { return calloc(1, sizeof(List)); }

void List_destroy(List *list) {
	LIST_FOREACH(list, first, next, cur) {
		if (cur->prev) {
			free(cur->prev);
		}
	}
	free(list->last);
	free(list);
}

void List_clear(List *list) {
	LIST_FOREACH(list, first, next, cur) { free(cur->value); }
}

void List_clear_destroy(List *list) {
	List_clear(list);
	List_destroy(list);
}

void List_push(List *list, void *value) {
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->last == NULL) {
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;

error:
	return;
}

void *List_pop(List *list) {
	ListNode *node = list->last;
	if (node != NULL) {
		return List_remove(list, node);
	}
	return NULL;
}

void List_push_front(List *list, void *value) {
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->first == NULL) {
		list->first = node;
		list->last = node;
	} else {
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}

	list->count++;

error:
	return;
}

void *List_pop_front(List *list) {
	ListNode *node = list->first;
	if (node != NULL) {
		List_remove(list, node);
	}
	return NULL;
}

void *List_remove(List *list, ListNode *node) {
	void *result = NULL;

	check(list->first && list->last, "List is empty");
	check(node, "node can't be NULL");

	if (node == list->first && node == list->last) {
		// If only one entry in list then both first and last need to be nulled
		list->first = NULL;
		list->last = NULL;
	} else if (node == list->first) {
		// If at first entry in list, set first to point to the next node and set prev to null
		list->first = node->next;
		check(list->first != NULL, "Invalid list, somehow got a first that is NULL");
		list->first->prev = NULL;
	} else if (node == list->last) {
		// If at last entry, set last to point to prev nod and set next to null
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
		list->last->next = NULL;
	} else {
		// When not first or last we need to rearrange the next entry to point to the curs previous
		// as well as previous entry to point to the curs next
		ListNode *next = node->next;
		ListNode *prev = node->prev;
		next->prev = prev;
		prev->next = next;
	}

	list->count--;
	result = node->value;
	free(node);

error:
	return result;
}

List *List_copy(List *list_to_copy, size_t value_size) {
	List *copy = List_create();
	copy->count = 0;
	LIST_FOREACH(list_to_copy, first, next, cur) {
		void *copy_value = malloc(value_size);
		check_mem(copy_value);
		memcpy(copy_value, cur->value, value_size);
		List_push(copy, copy_value);
	}

	return copy;

error:
	log_err("Could not copy list");
	return NULL;
}