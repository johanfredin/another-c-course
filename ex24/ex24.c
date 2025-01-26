#include <stdio.h>

#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor { BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES } EyeColor;

const char *EYE_COLOR_NAMES[] = {"Blue", "Green", "Brown", "Black", "Other"};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

void get_input_str(const char *restrict message, char *str, const int len) {
    printf("%s", message);
    int n = 0;
    char c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (n < len - 1) {
            str[n++] = c;
        }
    }
    str[n] = '\0';
    log_info("str=%s, n=%d\n", str, n);
}   

int main(int argc, char *argv[]) {
	Person you = {.age = 0};
	int i = 0;

    get_input_str("What's your First Name? ", you.first_name, 5);
    get_input_str("What's your Last Name? ", you.last_name, 5);

	printf("How old are you? ");
	int rc = scanf("%d", &you.age);
	check(rc > 0, "You have to enter a number.");

	printf("What color are your eyes:\n");
	for (i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	check(rc > 0, "You have to enter a number.");

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	rc = fscanf(stdin, "%f", &you.income);
	check(rc > 0, "Enter a floating point number.");

	printf("----- RESULTS -----\n");

	printf("First Name: %s\n", you.first_name);
	printf("Last Name: %s\n", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	return 0;
error:

	return -1;
}
