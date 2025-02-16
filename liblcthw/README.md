# -g → Include debugging symbols (useful for gdb, even with optimizations).
# -O2 → Optimize for speed while maintaining reasonable compile time.
# -Wall → Enable common warnings.
# -Wextra → Enable extra warnings (good practice).
# -Isrc → Add src/ as an additional include directory.
# -rdynamic → Keep function symbols in the binary for dynamic symbol resolution (useful for debugging or dlsym() in dlfcn.h).
# -DNDEBUG → Define NDEBUG, which disables assert() (typically for release builds).
# $(OPTFLAGS) → Placeholder for additional user-defined optimizations.
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

# -ldl → Links against the dynamic linking library (libdl). This is required if you're using functions like dlopen(), dlsym(), dlclose(), etc., from dlfcn.h.
# $(OPTLIBS) → Placeholder for additional libraries you may need.
LIBS=-ldl $(OPTLIBS)

# PREFIX?= → This means the variable PREFIX will default to /usr/local unless it's overridden by an environment 
# variable or command-line argument (e.g., make PREFIX=/custom/path).
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))