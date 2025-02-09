#include <dirent.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "dbg.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("logfind [OPTION] ...PATERNS[FILES]");
		return 1;
	}

	int start = 1;
	unsigned char or_match = 0;
	if (strcmp(argv[start], "-o") == 0) {
		or_match = 1;
		start++;
	}

	// Iterate files in project dir
	DIR *dir = opendir(".");
	check(dir, "Could not open dir");

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		FILE *file = fopen(entry->d_name, "r");
		char buf[512];
		int match = 0;

		// Iterate file content
		while (fgets(buf, 512, file)) {
			// Look for match
			for (int i = start; i < argc; i++) {
				if (!strstr(buf, argv[i])) {
					if (or_match) {
						continue;
					}
					break;
				}
				match = 1;
			}
		}

		if (match) {
			puts(entry->d_name);
		}
	}

	return 0;
error:
	log_err("error");
	return 1;
}