#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
int coins = 0;
int penny = 0 ;
int quarter =0;
int nickel =0;
int dime = 0;
float change;
    do {
        printf("What change do you need?: ");
        change = get_float()*100;
        change = round(change);
        }
    while (change < 0);
   
float remainder = change;
    while (remainder >= 25 )
        {
            quarter = quarter + 1;
            coins = coins + 1;
            remainder = remainder -25;
        }
    while (remainder >= 10)
        {
            dime = dime +1;
            coins = coins + 1;
            remainder = remainder -10;
        }
    while (remainder >= 5)
        {
            nickel = nickel + 1;
            coins = coins + 1;
            remainder = remainder -5;
        }
    while (remainder >= 1)
        {
            penny = penny + 1;
            coins = coins + 1;
            remainder = remainder -1;
        }
        printf("%i Coins\n", coins);
        printf("%i quarters, %i dimes, %i nickels, and %i pennies\n", quarter, dime, nickel, penny);
   
}