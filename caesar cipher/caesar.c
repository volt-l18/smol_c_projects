#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

typedef char *string;

string get_string(const char *format, ...)
{
    if (format != NULL)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }

    size_t capacity = 0;
    size_t length = 0;
    string buffer = NULL;

    while (1)
    {
        int c = fgetc(stdin);
        if (c == '\n' || c == EOF)
        {
            if (c == EOF && length == 0)
            {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length + 1 >= capacity)
        {
            capacity = (capacity == 0) ? 16 : capacity * 2;
            string temp = realloc(buffer, capacity);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        buffer[length++] = c;
    }

    if (buffer == NULL)
    {
        buffer = malloc(1);
        if (buffer == NULL) return NULL;
    }
    buffer[length] = '\0';
    string text = realloc(buffer, length + 1);
    return (text == NULL) ? buffer : text;
}

int main(int argc, string argv[])
{
    // 1. Condition if no argument was provided
    if (argc != 2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }

    // 2. Checking if the whole argument is a valid positive integer digit by digit
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("usage: ./caesar key\n");
            return 1;
        }
    }

    // 3. Converting key into integer and taking the plaintext input
    int key = atoi(argv[1]) % 26;
    string text = get_string("plaintext: ");
    
    if (text == NULL)
    {
        return 1;
    }

    // 4. Making Cipher text using plaintext
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
        {
            // Shift relative to ASCII 'A' (65), wrap around 26, then restore ASCII
            text[i] = ((text[i] - 'A' + key) % 26 + 'A');
        }
        else if (islower(text[i]))
        {
            // Shift relative to ASCII 'a' (97), wrap around 26, then restore ASCII
            text[i] = ((text[i] - 'a' + key) % 26 + 'a');
        }
    }

    // 5. Print the cipher text
    printf("ciphertext: %s\n", text);
    
    // 6. Free the memory we allocated inside get_string to stop the leak!
    free(text); 
    return 0;
}
