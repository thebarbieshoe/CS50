#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


int main(void)
{
    //get user input
    //printf("State your name: ");
    string name = get_string();
    
    //print the first char as first initial
    printf("%c",toupper(name[0]));
    //for loop to go through every single letter of entered name. only print a letter after a space
    for (int i=1, n=strlen(name); i < n; i++)
        {
                if (name[i] == ' ')
                {
                printf("%c", toupper(name[i+1]));
                }
        }
        printf("\n");
}