/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }

    // save n
    int n = atoi(argv[1]);

    if (n > 100 || n <= 0)
        {
            fprintf(stderr, "Usage: n must be positive integer less than or equal to 100\n");
        }


    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // copy headers
    BITMAPFILEHEADER outbf = bf;
    BITMAPINFOHEADER outbi = bi;

    // enlarge width, height file size, and image size
    if (n > 1)
    {
    outbi.biWidth = bi.biWidth * n;
    outbi.biHeight = bi.biHeight *n;

    // determine (new) padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding =  (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // newbi.biSizeImg = (width * height * sizeofRGB) + (padding * abs (height) * sizeof(padding))
    outbi.biSizeImage = (sizeof(RGBTRIPLE)*outbi.biWidth * abs(outbi.biHeight) ) + (newpadding * abs (outbi.biHeight));
    outbf.bfSize = outbi.biSizeImage + 54 ; // equivalent to sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // iterate over infile's scanlines (rows first)
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            int onerow = bi.biWidth*sizeof(RGBTRIPLE)+(padding);

            // to resize vertically, rewrite each column n-1 times
            for (int vert=0; vert < n ; vert++)
            {
                // restart at appropriate line of code in infile
                fseek(inptr, (sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+onerow*i), SEEK_SET);

                //if (i==0 && vert==n) // skip last row of first vert iteration
               // {
               //   fseek(inptr, (sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+onerow), SEEK_SET);
               // }
              //  else
              //  {
                    // iterate over pixels in scanline (columns)
                    for (int j = 0; j < bi.biWidth; j++)
                    {
                        // temporary storage
                        RGBTRIPLE triple;

                        // read RGB triple from infile. only reading 1 at a time
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        // write RGB triple to outfile (resizes horizontally)
                        for (int horiz=0; horiz < n; horiz++)
                            {
                            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                            }
                    }
                    // add New Padding if necessary, for each row
                        for (int k = 0; k < newpadding; k++)
                        {
                            fputc(0x00, outptr);
                        }
                    //submit50 cs50/2017/x/resize/less}
                // skip over padding in INFILE, if any, so we can continue reading from the next line of infile
                fseek(inptr, padding, SEEK_CUR);
           }

        }
    }
    else
    {
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    } //else

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
