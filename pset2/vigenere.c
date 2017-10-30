#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//introduce argument count and argument value, which needs to be non-neg inter k
//convert argv to an integer later in code?
int main(int argc, string argv[])
{
    string message;
    string key=argv[1];
    int len =strlen(key);
    int j;
    
    //convert key to alphabetical order values, 0, 1, 2, 3, etc + also makes sure that argv[1] is alphabetical
    for (j=0; j < len; j++)
    {
        if (isalpha(key[j]))
            {
                if (islower(key[j]))
                {
                key[j] = key[j] - 97;
                }
                else 
                {
                key[j] = key[j] - 65;    
                }
            }
        else
        {
            printf("You did not follow the rules, sir.\n");
            return 1;
        }
    }
    
   //argc must = 2
   if (argc==2)
   {
       //get message to encode
       printf("plaintext: ");
       message = get_string();
     int n =strlen(message);
     int new[n];
       printf("ciphertext: ");
       
       //do this action for each char in given message
       for (int i=0; i < n; i++)
       {
           //if alpha
           if (isalpha(message[i]) && islower(message[i]))
           {
               j=0;
               //convert to alphabetical order + vig equation + then back to ascii + print char
               new[i] = message[i] - 97;
               new[i] = (new [i] + key[j]) % 26;
               new[i] = new [i] + 97;
               printf("%c", new[i]);
               // if message is longer than key
             //  if (n > len)
              // {
              //     
             //  }
             //  else
             //  {
               j = j + 1;
             //  }
           }
           else if (isalpha(message[i]) && isupper(message[i]))
           {
               new[i] = message[i] - 65;
               new[i] = (new [i] + key[j]) % 26;
               new[i] = new [i] + 65;
               printf("%c", new[i]);
           }
           
           //if non-alphabetical
           else
           {
               printf("%c", message[i]);
           }
       }
       printf("\n");
       return 0;
   }
       
          //if non alphabetical char, just print the char
   //if argc does not mean requirements
   else
   {
       printf("You did not follow the rules, sir.\n");
       return 1;
   }

}