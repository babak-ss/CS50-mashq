#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

//decalring a default buffer size(1024 byte = 1 Megabyte) as a global variable to be able to use anywhere
const int BUFFER_SIZE = 1024;

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char word);
void get_string(const char *prompt, char* string);

int main(void)
{
    // Get input words from both players
    char word1, word2;

    get_string("Player 2: ", word1);
    get_string("Player 1: ", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
}

int compute_score(char word)
{
    // TODO: Compute and return score for string
}

void get_string(const char* prompt, char* string)
{
    //loop forever until user enters a valid number
    while (1)
    {
        char buffer[BUFFER_SIZE];

        //prompt user for input
        //fputs is a function that outputs a string on a desired file
        // here we have "stdout" as our output file which is the 
        // "standard output stream" which itself is the text console
        fputs(prompt, stdout);

        //get one line of input from input stream
        // fgets works like this, it reads a line from the specified stream(stdin)
        // and it stops under 3 conditions: 1. reaches end-of-line character(\n) 
        // 2. reaches end-of-file 3. when n - 1 characters are reached(in bellow code it is (size of buffer) - 1 = 1023)
        if (fgets(buffer, sizeof buffer, stdin) == NULL)
        {
            //fprintf is the same as print of but it is used to output to a file
            // which in below code is "stderr"
            fprintf(stderr, "Unrecoverable input error!\n");
            //exits from the function(get_string) immediately
            exit(EXIT_FAILURE);
        }

        //make sure that entire line was read in (i.e. that the buffer was not too small)
        // strchr searches for \n in the buffer and feof checks whether end-of-file has reached
        if (strchr(buffer, '\n') == NULL && !feof(stdin))
        {
            int c;

            printf("Line input was too long!\n");

            //discard remainder of line
            do
            {
                c = getchar();

                if (c == EOF)// EOF stands for End Of File
                {
                    fprintf(stderr, "Unrecoverable error reading from input!\n");
                    //exits from the function(get_int) immediately
                    exit(EXIT_FAILURE);
                }

            } while (c != '\n');

            //continue commands skips the remainder of the while loop and starts from the begining
            continue;
        }

        //declare the terminating zero 
        buffer[BUFFER_SIZE - 1] = '\0';

        //removes the end of line
        buffer[strcspn(buffer, "\n")] = 0;

        //copy the generated string local variable to the given string
        strncpy(string, buffer, BUFFER_SIZE - 1);

        //return empty to get out of the infinit loop and function at the same time
        return;
    }
}