#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

bool check_validity(long l);
long sum_digits(long l);
long math_pow(long l, int p);
long get_long( const char *prompt );

int main(void) 
{
    bool isValid = false;
    printf("%li\n", sum_digits(1111111111));
    while (!isValid)
    {
        isValid = check_validity(get_long("Number: "));
        if (!isValid)
            printf("INVALID\n");
    }
    printf("VALID\n");
    
}

bool check_validity(long l)
{
    long sum = 0;
    long pow10 = 10;
    int c = 0;
    while (l > pow10)
    {
        int x = (c % 2 == 0) ? 1 : 2;
        pow10 = math_pow(10, c);
        sum = sum + sum_digits(x * ( (l / pow10) % 10 ));
        c++;
    }
    
    return (sum % 10 == 0);
}

long sum_digits(long l)
{
    long sum = 0;
    long pow10 = 0;
    int c = 0;
    while (l > pow10)
    {
        pow10 = math_pow(10, c);
        sum += (l / pow10) % 10;
        c++;
    }

    return sum;
}

long math_pow(long l, int p)
{
    long r = 1;
    for (int i = 0; i < p; i++)
    {
        r *= l;
    }
    
    return r;
}

long get_long(const char *prompt)
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
        // and 10 is the base we use to convert string to long int(base-10)
        l = strtol(buffer, &p, 10);
        // if the end of our int part is the same as our string it means we didn't have any int!
        if (p == buffer)
        {
            // printf("Error converting string to number!\n");
            continue;
        }

        //make sure that number is representable as an "long"
        if (errno == ERANGE)
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