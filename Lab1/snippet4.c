#include <stdio.h>

//Error: No & symbol needed, include max length for name.
int main() {
    char name[20];
    printf (" Enter your name: ");
    scanf ("%s", name);
    printf (" Hello %s!\n", name);
    return 0;
}