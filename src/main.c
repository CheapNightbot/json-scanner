#include <ctype.h>
#include <stdio.h>
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

    // Buffer for space character (i.e., a space or tab)
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
