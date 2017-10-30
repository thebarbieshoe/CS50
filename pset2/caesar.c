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
       printf("plaintext: ");
       string message = get_string();
       
       printf("ciphertext: ");
       //for loop-iterates over each character in the MESSAGE
       for (int i=0, n = strlen(message); i < n; i++)
       {
          //if alphabetical char/preserve case/shift plaintext char by KEY amount
          if (isalpha(message[i]))
          {
            //convert argv to an integer
            int k = atoi(argv[1]);
            //creating NEWMESSAGE ARRAY to covert 'A' to alphabetical
            int secret[n];
            if (isupper(message[i]))
             {
               //convert ASCII value to alphabetical index--saved as SECRET (upper)
               secret [i] = ((((message[i]-65) + k) % 26) + 65);
               printf("%c", secret[i]);
             }
            else if (islower(message[i]))
            {
               //convert ASCII value to alphabetical index--saved as SECRET (lower)
               secret [i] = ((((message[i]-97) + k) % 26) + 97);
               printf("%c", secret[i]);
             }
             
          }
          //if non alphabetical char, just print the char
          else 
          {
             printf("%c", message[i]);
          }
       }
      printf("\n");
   }
   //if argc does not mean requirements
   else 
   {
       printf("I'm sorry. You did not follow the rules.\n");
       return 1;
   }
}