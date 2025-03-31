#include <dlfcn.h>
#include <stdio.h>

#include "src/dbg.h"

/* I'll use this function pointer definition later to call functions in the library. */
typedef int (*lib_function)(const char *data);

int main(int argc, char *argv[]) {
	int rc = 0;
	check(argc == 4, "USAGE: ex29 libex29.so function data");

	char *lib_file = argv[1];
	char *func_to_run = argv[2];
	char *data = argv[3];

    /*
        I use the dlopen function to load up the library that's indicated by lib_file. 
        This function returns a handle that we use later, which works a lot like opening a file.
    */
	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());
    
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

    // Call function
    rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);
    
    // Close
    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s, return value=%d", lib_file, rc);

	return 0;
error:
	return 1;
}