#include <stdio.h>

//Error: Missing & symbol
int main() {
    int number ;
    printf (" Enter a number : ");
    scanf ("%d", &number );
    printf ("You entered : %d\n", number );
    return 0;
}