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
        //i'm so close!!
        //I need a variable that would change outside of my "reverse loop" i changes each time, so i used it to subtract from the x height
        int l=(x-2)-i;
        
        for (int j=l; j >= 0; j--)
            {
                printf(" ");
            }

        //loop for hashes
        printf("##");
            //first time prints nothing, then 1, 2, 3
            for (int j = 0; j < i; j++)
                {
                   printf("#");
                }
        //next line
        printf("\n");
    }
}