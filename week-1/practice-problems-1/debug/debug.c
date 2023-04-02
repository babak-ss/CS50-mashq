#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

//decalring a default buffer size(1024 byte = 1 Megabyte) as a global variable to be able to use anywhere
const int BUFFER_SIZE = 1024;

void get_string(const char *prompt, char* string);

int main(void)
{
    //Ask for your name and where live
    char name[BUFFER_SIZE];
    get_string("What is your name? ", name);
    char location[BUFFER_SIZE];
    get_string("Where do you live? ", location);

    //Say hello
    printf("Hello, %s, from %s!", name, location);
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