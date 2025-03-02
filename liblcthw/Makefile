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

# dynamically creates the SOURCES variable by doing a wildcard search for all *.c files in the src/ directory. 
# You have to give both src/**/*.c and src/*.c so that GNU make will include the files in src and the files below it.
# Once you have the list of source files, you can then use the patsubst to take the SOURCES list of *.c files 
# and make a new list of all the object files. You do this by telling patsubst to change all %.c extensions to %.o, 
# and then those extensions are assigned to OBJECTS.
SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

 # We're using the wildcard again to find all of the test source files for the unit tests. 
 # These are separate from the library's source files.
 # Then, we're using the same patsubst trick to dynamically get all the TEST targets. 
 # In this case, I'm stripping away the .c extension so that a full program will be made with the same name. 
 # Previously, I had replaced the .c with {.o} so an object file is created.
TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# Create liblcthw.a in local build directory.
# Create liblcthw.so in same directory turning the .a into a .so file
TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The target build
# When you run make, it ensures:
# ------------------------------
# The static library (.a) is built.
# The shared library (.so) is built.
# Tests are compiled or executed (depending on the tests rule).
all: $(TARGET) $(SO_TARGET) tests

# Here's another target for making "developer builds" that introduces a technique for changing options for just one target. 
# If I do a "dev build" I want the CFLAGS to include options like -Wextra that are useful for finding bugs. 
# If you place them on the target line as options like this, 
# then give another line that says the original target (in this case all), 
# then it will change the options you set. 
# I use this for setting different flags on different platforms that need it.
dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# $(TARGET): CFLAGS += -fPIC
# This line appends -fPIC (Position Independent Code) to CFLAGS for the specific target $(TARGET).
# 
#     -fPIC is necessary for generating position-independent code, which is often required when creating shared libraries.
#     The += operator adds -fPIC to the existing CFLAGS value without overwriting it.
# 
# $(TARGET): build $(OBJECTS)
# This ensures that $(TARGET) depends on two things:
# 
#     build: A directory or target that is presumably created before proceeding.
#     $(OBJECTS): The object files you want to include in the archive ($(TARGET)).
#     If build and $(OBJECTS) are out of date, this rule will trigger.
# 
# ar rcs $@ $(OBJECTS)
# The ar command creates an archive (.a file) from the object files:
# 
#     r → Replace existing files in the archive.
#     c → Create the archive if it doesn’t exist.
#     s → Add an index to the archive for faster linking.
#     $@ represents the target file ($(TARGET)), so this creates your static library.
# 
# ranlib $@
# ranlib generates an index for the archive, making it ready for linking. 
# This is typically done with static libraries (.a files) to allow for faster linking
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# This just makes the build/ or bin/ directories if they don't exist. 
# This is then referenced from line 19 when it gives the build target 
# to make sure the build/ directory is made.
build:
	@mkdir -p build
	@mkdir -p bin

# Unit tests
# ----------
# If you have a target that's not real, but there is a directory or file with that name, 
# then you need to tag the target with .PHONY: so make will ignore the file and always run.
.PHONY: tests
# use the same trick for modifying the CFLAGS variable to add the TARGET to the build so that each of the test 
# programs will be linked with the TARGET library. In this case, it will add build/libYOUR_LIBRARY.a to the linking.
tests: CFLAGS += $(TARGET)
# have the actual tests: target, which depends on all of the programs listed in the TESTS variable that we created 
# in the header. This one line actually says, 
# "Make, use what you know about building programs and the current CFLAGS settings to build each program in TESTS."
tests: $(TESTS)
	sh ./tests/runtests.sh


# Cleanup
# -------
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# Install
# -------
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
        |stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true