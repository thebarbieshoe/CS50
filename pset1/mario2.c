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

//pyramid making time

// 1st for loop prints correct number of rows in pyramid
for (int i = 0; i < x; i++)
    {
            for (int j = 0; j < i+1; j++)
                {
                   printf("#");
                }
        for (int j = 9; j > 0; j--) 
            {
                printf(" ");
            }

        printf("\n");
    }
}