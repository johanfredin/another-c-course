#include <stdio.h>

void firstWay(char **names, int *ages, int count) {
	// first way using indexing
	puts("first way");
	puts("-------------");
	for (int i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");
}

void secondWay(char **names, int *ages, int count) {
    puts("second way");
	puts("-------------");
	// second way using pointers
	for (int i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(names + i), *(ages + i));
	}
	printf("---\n");
}

void thirdWay(char **names, int *ages, int count) {
	puts("third way");
	puts("-------------");
    // third way, pointers are just arrays
	int *cur_age = ages;
	char **cur_name = names;
    for (int i = 0; i < count; i++) {
		printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
	}
    printf("---\n");
}

void fourthWay(char **names, int *ages, int count) {
	puts("4th way");
	puts("-------------");
    // fourth way with pointers in a stupid complex way
	int *cur_age = ages;
	char **cur_name = names;
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++) {
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}
    printf("---\n");
}

int main(int argc, char *argv[]) {
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	firstWay(names, ages, count);
	secondWay(names, ages, count);
    thirdWay(names, ages, count);
    fourthWay(names, ages, count);


	return 0;
}
