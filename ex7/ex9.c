#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = -10;
    while (i) {
        printf("%d\n", i);
        if (i == 10) {
            break;
        }
        i++;
    }

    return 0;
}
