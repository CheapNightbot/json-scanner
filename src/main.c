#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

// Function prototypes
void print(char *text, char *token, int char_num, int line_num);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s file.json\n", argv[0]);
        return 1;
    }

    FILE *json = fopen(argv[1], "r");
    if (json == NULL)
    {
        printf("Unable to open %s\n", argv[1]);
        return 1;
    }

    printf("\n%-8s | %s:%s | -> %s\n", "TOKEN", "LINE", "CHAR", "TEXT");
    printf("------------------------------\n");

    // Initialize variables for line & character number
    int char_num = 1;
    int line_num = 1;

    // Buffer to read file into, char by char
    char c;

    // Buffer for space character (i.e., a space or tab) and char
    char tmp;

    while ((c = getc(json)) != EOF)
    {
        // Add read char into s array for easier printing later
        char s[] = {c};

        switch (c)
        {
        case '{':
            print(s, token(TOKEN_LBRACE), char_num, line_num);
            char_num++;
            break;

        case '}':
            print(s, token(TOKEN_RBRACE), char_num, line_num);
            char_num++;
            break;

        case ':':
            print(s, token(TOKEN_COLON), char_num, line_num);
            char_num++;
            break;

        case ',':
            print(s, token(TOKEN_COMMA), char_num, line_num);
            char_num++;
            break;

        case '"':
            // Buffer size for a string
            int buffer_size = 10;

            // Index for the string
            int i = 0;

            // Remember the starting position of the string
            int char_start = char_num;

            // Allocate memroy for the text
            char *text = malloc(buffer_size * sizeof(char));
            if (text == NULL)
            {
                printf("Memory allocation failed!\n");
                return 1;
            }

            // Add litral doube quote before `text` string
            text[i++] = '"';

            do
            {
                tmp = fgetc(json);

                // Assume reached the end of the string
                if (tmp == '"')
                {
                    char_num += 2;
                    break;
                }

                // Check if buffer is full
                // `-2` bacuse we need space for double quote & terminator character.
                if (i >= buffer_size - 2)
                {
                    // Double buffer size
                    buffer_size *= 2;

                    // Reallocate memory for the text
                    char *temp = realloc(text, buffer_size * sizeof(char));
                    if (temp == NULL)
                    {
                        printf("Memory reallocation failed!\n");
                        free(text);
                        return 1;
                    }
                    // Point to newly allocated memroy
                    text = temp;
                }
                text[i] = tmp;
                char_num++;
                i++;
            } while (1);

            // Add litral doube quote after `text` string
            text[i++] = '"';

            // Terminate the string with NUL
            text[i] = '\0';
            print(text, token(TOKEN_STRING), char_start, line_num);
            free(text);
            break;

        // Handle newline character
        case '\n':
            char_num = 1;
            line_num++;
            break;

        // Skip a space character
        case ' ':
            ungetc(c, json);
            do
            {
                tmp = fgetc(json);
                if (tmp != ' ')
                {
                    ungetc(tmp, json);
                    break;
                }
                char_num++;
            } while (1);

            break;

        // Skip a tab character
        case '\t':
            ungetc(c, json);
            do
            {
                tmp = fgetc(json);
                if (tmp != '\t')
                {
                    ungetc(tmp, json);
                    break;
                }
                char_num++;
            } while (1);

            break;

        default:
            char_num++;
            print(s, token(TOKEN_ERROR), char_num, line_num);
            break;
        }
    }

    fclose(json);
    return 0;
}

// Format and print parsed text and token type
void print(char *text, char *token, int char_num, int line_num)
{
    printf("%-8s %-4c %i:%-4i | -> %s\n", token, '|', line_num, char_num, text);
}
