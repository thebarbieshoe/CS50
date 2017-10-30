/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

    // TODO: implement a searching algorithm


//don't need a for loop. this while loop will continue until (sub)array=0
while (n > 0)
{
   //going to create a linear search first
   for (int m=0; m<n; m++)
   {
        if (values[m]==value)
        {
        return true;
        }
    return false;
   }
// while loop-if n is non positive
return 0;
}
return 0;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm

    //iterate over n-1 amount of times
    for (int i=0; i < n-1; i++)
    {
        int k;
        int min=values[i];

       //interate over each value, each time
       for (int j = i; j < n; j++)
       {

        if (values[j] < min)
        {
            min = values [j];
            k = j;
        }
       }
       //add min value to new array & swap 0 and j value
       int newvalues [n];
       newvalues[i]=min;

       //swap values
       int x = values [i];
       //change the smallest value to the first spot in array
       values [i] = min;
       //move initial value to the spot where the smallest value was
       values [k] =x;

        printf("the minimum number is: %i \n", values[i]);
    }
    return;
}
