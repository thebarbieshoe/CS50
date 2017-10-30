/**
 * RECOVERS JPEGS! probably
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file name");
        return 1;
    }

    // STEP ONE. open input file
    FILE *inptr = fopen(argv[1], "r");

    // ensure file has data
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    unsigned char buffer[512] ={0};
    char filename[8];
    FILE *img=NULL;
    int i=0;

    // STEP TWO. repeat until end of the card. while each container = 512 byes
    while(fread(&buffer, 512, 1, inptr)!=0)
    {
        // STEP 1A. read 512 bytes into a buffer (read infile's)
        //fread(&buffer, 512, 1, inptr); DON"T NEED TO DO THIS TWICE!

        // STEP 2A start of a jpeg header? yes> no>
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)

            {
                // YES && YES: yes start of jpeg header and yes, already found a jpeg
                if (img!= NULL)
                {
                    printf("end of jpeg\n");
                    fclose(img);
                    i++;
                    // creates a new jpeg, open jpeg, write to jpeg
                    sprintf(filename, "%03i.jpg", i);
                    printf("%s\n", filename);
                    img = fopen(filename, "w");
                    fwrite(&buffer, 512, 1, img);
                }
                else // YES & NO; this is the very first jpeg of file
                {
                    printf("I'm the first jpeg!");
                    sprintf(filename, "%03i.jpg", i);
                    printf("%s\n", filename);

                    img = fopen(filename, "w");
                    fwrite(&buffer, 512, 1, img);
                }

            }

        else // NO && YESS- not header. already an image. continue writing the same jpeg
            {
                 if (img!= NULL)
                 {
                    fwrite(&buffer, 512, 1, img);
                    printf("1");
                 }
            }

        // NO AND NO- just start the loop over and continue reading

        // STEP THREE close any remaining files
        // close infile

    }
    printf("\n");
    printf("EOF %i jpegs detected\n", i+1);
    fclose(inptr);
    fclose(img);

    // close outfile
    //fclose(outptr);

    // success
    return 0;


}