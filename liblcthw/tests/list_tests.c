#include <assert.h>

#include "../src/list.h"
#include "minunit.h"

List *list;

char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test2 data";

char *set_up() {
	list = List_create();
	mu_assert(list != NULL, "List is null");
	return NULL;
}

char *tear_down() {
	List_destroy(list);
	return NULL;
}

char *test_push_pop() {
	set_up();

	// Test push and count
	List_push(list, test1);
	List_push(list, test2);
	List_push(list, test3);
	mu_assert(List_first(list) == test1, "Wrong first value");
	mu_assert(List_last(list) == test3, "Wrong last value");
	mu_assert(List_count(list) == 3, "Wrong amount of entries in list, expected 3");

	// Test pop
	char *pop1 = (char *)List_pop(list);
	char *pop2 = (char *)List_pop(list);
	char *pop3 = (char *)List_pop(list);
	mu_assert(pop1 == test3, "Wrong value popped first, expected test3");
	mu_assert(pop2 == test2, "Wrong value popped second, expected test2");
	mu_assert(pop3 == test1, "Wrong value popped third, expected test1");
	mu_assert(List_is_empty(list), "List is not empty");

	return tear_down();
}

char *test_push_front() {
	set_up();

	List_push_front(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first value");
	List_push_front(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first value");
	List_push_front(list, test3);
	mu_assert(List_first(list) == test3, "Wrong first value");
	mu_assert(List_count(list) == 3, "Wrong amount in list");

	return tear_down();
}

char *test_pop_front() {
	// Set up
	set_up();
	List_push(list, test1);
	List_push(list, test2);
	List_push(list, test3);

	List_pop_front(list);
	mu_assert(List_first(list) == test2, "Wrong first value, expected test2");
	mu_assert(List_count(list) == 2, "Wrong count, expected 2");
	List_pop_front(list);
	mu_assert(List_first(list) == test3, "Wrong first value, expected test3");
	mu_assert(List_count(list) == 1, "Wrong count, expected 1");
	List_pop_front(list);
	mu_assert(List_first(list) == NULL, "Wrong first value, expected NULL");
	mu_assert(List_count(list) == 0, "Wrong count, expected 0");

	return tear_down();
}

char *test_remove() {
	set_up();

	List_push(list, test1);
	List_push(list, test2);
	List_push(list, test3);

	char *val = List_remove(list, list->first->next);
	mu_assert(val == test2, "Wrong removed element");
	mu_assert(List_count(list) == 2, "Wrong amount");
	mu_assert(List_first(list) == test1, "Wrong first element");
	mu_assert(List_last(list) == test3, "Wrong last element");

	return tear_down();
}

char *test_copy() {
	set_up();
	int v1 = 1;
	int v2 = 2;
	int v3 = 3;
	List_push(list, &v1);
	List_push(list, &v2);
	List_push(list, &v3);

	List *copy = List_copy(list, sizeof(int));

	mu_assert(List_count(copy) == 3, "Wrong amount in copy");

	int *cpv1 = (int*) (copy->first->value);
	int *cpv2 = (int*) (copy->first->next->value);
	int *cpv3 = (int*) (copy->last->value);
	
	// Verify values correct
	mu_assert(*cpv1 == v1, "Different first values");
	mu_assert(*cpv2 == v2, "Different second values");
	mu_assert(*cpv3 == v3, "Different third values");

	// Verify pointer adresses different, if not then its not a true copy
	mu_assert(cpv1 != &v1, "Same adress for v1");
	mu_assert(cpv2 != &v2, "Same adress for v2");
	mu_assert(cpv3 != &v3, "Same adress for v3");

	return tear_down();
}

char *test_join() {
	// Set up
	set_up();
	int v1 = 1;
	int v2 = 2;
	int v3 = 3;
	List_push(list, &v1);
	List_push(list, &v2);
	List_push(list, &v3);

	List *newList = List_create();
	int v4 = 4;
	int v5 = 5;
	int v6 = 6;
	List_push(newList, &v4);
	List_push(newList, &v5);
	List_push(newList, &v6);

	// Act
	List_join(list, newList);

	// Verify
	mu_assert(List_count(list) == 6, "Wrong amount");
	mu_assert(List_first(list) == &v1, "Wrong first value");
	mu_assert(List_last(list) == &v6, "Wrong last value");

	mu_assert(List_count(newList) == 3, "Count altered for newList");

	int val = 1;
	for(ListNode *cur = list->first; cur != NULL; cur = cur->next) {
		int *curVal = (int *) (cur->value);
		int expected = val++;
		mu_assert(*curVal == expected, "Wrong value");
	}

	return tear_down();
}

char *all_tests() {
	mu_suite_start();
	mu_run_test(test_push_front);
	mu_run_test(test_push_pop);
	mu_run_test(test_pop_front);
	mu_run_test(test_remove);
	mu_run_test(test_copy);
	mu_run_test(test_join);
	return NULL;
}

RUN_TESTS(all_tests);