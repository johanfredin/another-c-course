#include <stdio.h>
#include <malloc.h>

int *get_ages() {
    int *ages = (int *) calloc(5, sizeof(int));
    ages[0] = 23;
    ages[1] = 43;
    ages[2] = 12;
    ages[3] = 89;
    ages[4] = 2;
    return ages;
}

char **getNames() {
    char **names = (char**) calloc(5, sizeof(char*));
    names[0] = "Alan";
    names[1] = "Falnk";
    names[2] = "Frank";
    names[3] = "John";
    names[4] = "Lisa";
    return names;
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int *ages = get_ages();
    char **names = getNames(); 

    // safely get the size of ages
    int count = 5;
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointersgd
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    free(ages);
    free(names);
    return 0;
}
