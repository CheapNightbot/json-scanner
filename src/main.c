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
    printf("----------------------------\n");

    // Initialize variables for line & character number
    int line_num, char_num = 0;

    // Buffer to read file into, char by char
    char c;

    while ((c = getc(json)) != EOF)
    {
        // Add read char into s array for easier printing later
        char s[] = {c};

        switch (c)
        {
        case '{':
            char_num++;
            print(s, token(TOKEN_LBRACE), char_num, line_num);
            break;

        case '}':
            char_num++;
            print(s, token(TOKEN_RBRACE), char_num, line_num);
            break;

        case ':':
            char_num++;
            print(s, token(TOKEN_COLON), char_num, line_num);
            break;

        case ',':
            char_num++;
            print(s, token(TOKEN_COMMA), char_num, line_num);
            break;

        case '\n':
            char_num = 0;
            line_num++;
            break;

        case ' ' | '\t':
            char_num++;
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
