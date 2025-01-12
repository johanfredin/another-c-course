#include <stdio.h>
#include <string.h>

// Did not know you could write functions like this
int kandr(a,b) 
	int a;
	int b;
	{
		return a + b;
	}

int main(int argc, char *argv[]) {
	char name[4] = {'j', 'a', 'f', '\0'};
	int i = 0;
	memcpy(&i, name, 4);

	// first, print them out raw
	char *crazy = (char *)&i;

	printf("k&r style=%d\n", kandr(1, 2));

	char first = (char) i;
	char second = (char) (i >> 8);
	printf("First letter=%c, second=%c\n", first, second);
	printf("name=%s\n", crazy);

	char yo[] = "hey";
	int *hoho = "crazy in love";
	printf("size hey=%lu, hoho=%lu, val=%s\n", sizeof(yo), sizeof(hoho), hoho);

	printf("int size on my machine=%ld\n", sizeof (size_t));
	return 0;
}


