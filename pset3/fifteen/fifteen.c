/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// blankspace!
int blankrow;
int blankcol;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// this one is mine!
void swap (int* a, int* b);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);

    blankrow=d-1;
    blankcol=d-1;

    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO INIT GAMEBOARD
int value=(d*d)-1;
    // nestled for loops
    // each row
    for (int i=0; i < d; i++)
    {
        // each column-last column switch if even
        for (int j=0; j< d; j++)
        {
            // if d is even, swap 2 and 1 values
            if (d % 2==0)
            {
                board [i][j]=value;
                value=value-1;
                // swap values! when board[i][j]==2 and board[i][j]
                if (board [i][j]==2)
                {
                    board[i][j]=1;
                }
                else if (board [i][j]==1)
                {
                    board[i][j]=2;
                }
            }
            // else d must be odd
            else
            {
                board [i][j]=value;
                value=value-1;
            }
        }
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO DRAW/PRINT GAMEBOARD
    // nestled loops
    for (int i=0; i < d; i++)
    {
        for (int j=0; j< d; j++)
        {
            if (board[i][j]==0)
            {
                printf("  _ ");
            }
            else
            {
            printf(" %2i ", board[i][j]);
            }

        }
        printf("\n");
        printf("\n");
    }

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */

bool move(int tile)
{
    // TODO
    // iterate to find each location from given tile value (highest value to lowest?)
    // each row
    for (int i=0; i < d; i++)
    {
        // each column
        for (int j=0; j < d; j++)
        {
        // going through each tile of array highest to lowest, until tile equals that value
        if (tile==board[i][j])
            {
            //save location?
            int a = i;
            int b = j;

            // check for legal move, up
            if (a==blankrow && b==blankcol-1)
            {
                //swap board[a][b] with blankspace
                swap (&board[a][b], &board[blankrow][blankcol]);
                //save new blankspace location!
                blankrow=a;
                blankcol=b;
                return true;
            }
            // down
            if ((a==blankrow && b==blankcol+1))
            {
                //swap board[a][b] with blankspace
                swap (&board[a][b], &board[blankrow][blankcol]);
                blankrow=a;
                blankcol=b;
                return true;
            }
            //  left
            if ((a==blankrow-1 && b==blankcol))
            {
                //swap board[a][b] with blankspace
                swap (&board[a][b], &board[blankrow][blankcol]);
                blankrow=a;
                blankcol=b;
                return true;
            }
            // right
            if ((a==blankrow+1 && b==blankcol))
            {
                //swap board[a][b] with blankspace
                swap (&board[a][b], &board[blankrow][blankcol]);
                blankrow=a;
                blankcol=b;
                return true;
            }
            return false;
            }
        }
    }
            return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
int winvalue=1;
//int max=d*d;
    // each row
    for (int i=0; i < d; i++)
    {
        // each column
        for (int j=0; j < d; j++)
        {
            if (i==d-1 && j==d-1)
            {
                if (board[i][j]!=0)
                {
                    return false;
                }
            }
            else
            {
                if (board[i][j]!=winvalue)
                {
                    return false;
                }
                else
                {
                    winvalue=winvalue+1;
                }
            }
         }
    }
    return true;
}

// again this one is mine!
void swap (int* p, int* q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
}
