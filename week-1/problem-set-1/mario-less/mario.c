#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int get_int( const char *prompt );

int main(void) 
{
    // we always initialize when creating a variable
    int input = 0;
    do
    {
        //we keep getting input until the intput is between 1 and 8 (inclusive)
        input = get_int("Height: ");
    } while (input < 1 || input > 8);

    //we do a for loop for each line
    for (int i = 0; i < input; i++)
    {
        //we do a for loop for each character in one line
        for (int j = 0; j < input; j++)
        {
            //in each line sum of spaces and # should be equal to (input - 1)
            // if total if i and j is less than (input - 1) it means that we should print space
            if (j + i < input - 1)
            {
                printf(" ");
            }
            //if the total of i and j is equal or bigger than (input - 1) it means we should print #
            else
            {
                printf("#");
            }
        }
        //when we're done with one line we go to the next line by printing "\n"
        printf("\n");
    }
    
}

int get_int(const char *prompt)
{
    //loop forever until user enters a valid number
    while (1)
    {
        char buffer[1024], *p;
        long l;

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
            // fprintf(stderr, "Unrecoverable input error!\n");
            // exits from the function(get_int) immediately
            exit(EXIT_FAILURE);
        }

        //make sure that entire line was read in (i.e. that the buffer was not too small)
        // strchr searches for \n in the buffer and feof checks whether end-of-file has reached
        if (strchr(buffer, '\n') == NULL && !feof(stdin))
        {
            int c;

            // printf("Line input was too long!\n");

            //discard remainder of line
            do
            {
                c = getchar();

                if (c == EOF)// EOF stands for End Of File
                {
                    // fprintf(stderr, "Unrecoverable error reading from input!\n");
                    // exits from the function(get_int) immediately
                    exit(EXIT_FAILURE);
                }

            } while (c != '\n');

            // continue commands skips the remainder of the while loop and starts from the begining
            continue;
        }

        //attempt to convert string to number
        //errno is a global variable that indicated the error code if any 
        // erros appear here we initialize it to 0 (meaning no error) to 
        // be able to check for errors in the next lines of our code
        errno = 0; 
        //strtol(string to long(duh!)) parses string to long int
        // buffer is our string, p is the pointer that directs to the end of int part of our string
        // and 10 is the base we use to convert string to long int(idk why 11 does not work!)
        l = strtol(buffer, &p, 10);
        // if the end of our int part is the same as our string it means we didn't have any int!
        if (p == buffer)
        {
            // printf("Error converting string to number!\n");
            continue;
        }

        //make sure that number is representable as an "int"
        if (errno == ERANGE || l < INT_MIN || l > INT_MAX)
        {
            // printf("Number out of range error!\n");
            continue;
        }

        //make sure that remainder of line contains only whitespace,
        //so that input such as "6sdfj23jlj" gets rejected
        for ( ; *p != '\0'; p++)// for loop untill pointer is reached to the end of the string(null-terminated string)
        {
            if (!isspace( (unsigned char)*p))
            {
                // printf("Unexpected input encountered!\n");

                //cannot use `continue` here, because that would go to
                //the next iteration of the innermost loop, but we
                //want to go to the next iteration of the outer loop
                goto continue_outer_loop;
            }
        }

        return l;

    continue_outer_loop:
        continue;
    }
}