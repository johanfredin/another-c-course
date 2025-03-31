#include <ctype.h>
#include <stdio.h>

int print_a_message(const char *msg) {
	printf("A STRING: %s\n", msg);
	return 0;
}

int uppercase(const char *msg) {
	for (int i = 0; msg[i] != '\0'; i++) {
		printf("%c", toupper(msg[i]));
	}
	puts("");
	return 0;
}

int lowercase(const char *msg) {
	for (int i = 0; msg[i] != '\0'; i++) {
		printf("%c", tolower(msg[i]));
	}
	puts("");
	return 0;
}

int tolowercase(char *msg) {
	for (int i = 0; msg[i] != '\0'; i++) {
		msg[i] = tolower(msg[i]);
	}
	return 0;
}

int fail_on_purpose() { return 1; }
