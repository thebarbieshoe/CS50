#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//introduce argument count and argument value, which needs to be non-neg inter k
//convert argv to an integer later in code?
int main(int argc, string argv[])
{
   //argc must = 2
   if (argc==2)
   {
       
    string k = argv[1];
    //prompt user for MESSAGE
    printf("Tell me what to encrypt!\n");
    string message = get_string();
       
       //for loop-iterates over each character in the MESSAGE, strlen(MESSAGE amount of times)
       for (int i = 0, j = 0, n = strlen(message), s = strlen(k); i < n; i++, j++)
       {
            //if alphabetical char/preserve case/shift plaintext char by KEY amount
            if (isalpha(message[i]))
            {
            
                //creating SECRET ARRAY to save values after running through encription
                int secret[n];
            
                //if both message and key are uppercase SECRET = MESSAGE[i] + KEY[J]
                //converting each value to alphabetical order before adding.
                if ( (isupper(message[i])) && (isupper(k[j % s])) )
                {
                //convert ASCII value to alphabetical index--saved as SECRET (upper)
                secret[i] = (message[i] - 65) + ( (k[j % s]-65) );
                secret[i] = (secret[i]+65) %26;
                printf("%c", secret[i]);
                printf("%c", k[ j % s ]);
                printf("%i", j % s);
                printf("\n");
                }
                
                else if ( (islower(message[i])) && (islower(k[j % s])) )
                {
                secret[i] = ( (message[i] - 97) + ( (k[j % s]-97) ) % 26) + 97;
                printf("%c", secret[i]);
                }
                
                else if (islower(message[i]) && isupper(k[j % s]))
                {
                secret[i] = ( (message[i] - 97) + ((k[ j % s]-65) ) % 26) + 97;
                printf("%c", secret[i]);
                }
                
                else if (isupper(message[i]) && islower(k[j % s]))
                {
                 secret[i] = ( (message[i] - 65) + ((k[ j % s]-97) ) % 26) + 65;
                printf("%c", secret[i]);
                }
             
            }
          //if non alphabetical char, just print the char
          else 
          {
             printf("%c", message[i]);
             printf("\n");
             j= j-1;
          }
       }
      printf("\n");
      return 0;
   }
   //if argc does not mean requirements
   else 
   {
       printf("I'm sorry. You did not follow the rules.\n");
       return 1;
   }
}