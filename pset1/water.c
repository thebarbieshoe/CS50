#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How many minutes do you spend in the shower?");
    int i = get_int();
    printf("You used the equivalent of %i bottles of drinking water!\n", i * 12);
}