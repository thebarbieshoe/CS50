#include <cs50.h>
#include <stdio.h>

int main(void)
{
int x;
do
    {
        //allows for user input and verifies that the number meets guidelines
        printf("Choose your height (1-23): ");
        x = get_int();
    }
while ((x > 23) || (x < 0));

//pyramid making time!

//do x number of times
for (int i=0; i < x; i++)
{
    int l=x-i;
    for (int j=l; j > 0; j--)
    {
        printf(".");
    }
    printf("A");
    printf("\n");
}

}