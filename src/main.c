#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

// Function prototypes
void print(char *text, char *token, int char_num, int line_num, char *msg);

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

    printf("\n\033[1m%-12s\033[0m | \033[1m%6s\033[0m:\033[1m%-6s\033[0m | \033[1m%s\033[0m\n", "TOKEN", "LINE", "CHAR", "TEXT");
    printf("-------------+---------------+-------------\n");

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
            print(s, token(TOKEN_LBRACE, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case '}':
            print(s, token(TOKEN_RBRACE, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case '[':
            print(s, token(TOKEN_LBRACKET, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case ']':
            print(s, token(TOKEN_RBRACKET, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case ':':
            print(s, token(TOKEN_COLON, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case ',':
            print(s, token(TOKEN_COMMA, -1), char_num, line_num, NULL);
            char_num++;
            break;

        case '"':
            // Buffer size for a string
            int buffer_size = 10;

            // Index for the string
            int i = 0;

            char e = '\0'; // For catching errors

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

                else if (tmp == ':')
                {
                    e = '?';
                    ungetc(tmp, json);
                    char_num++;
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

            if (e == '?')
            {
                text[i] = '\0';
                print(text, token(TOKEN_ERROR, -1), char_num, line_num, "Closing Quote is missing.");
                free(text);
                break;
            }

            // Add litral doube quote after `text` string
            text[i++] = '"';

            // Terminate the string with NUL
            text[i] = '\0';

            tmp = getc(json);
            if (tmp == ':')
            {
                ungetc(tmp, json);
                print(text, token(TOKEN_STRING, TOKEN_KEY), char_start, line_num, NULL);
            }
            else if (tmp == ',' || tmp == '[' || tmp == ']')
            {
                ungetc(tmp, json);
                print(text, token(TOKEN_STRING, TOKEN_VALUE), char_start, line_num, NULL);
            }

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
            if isdigit (c)
            {
                ungetc(c, json);
                // Reset buffer size
                buffer_size = 10;

                // Reset string index
                i = 0;

                // Remember the starting position of the digit
                char_start = char_num;

                // Allocate memory for the numbers (stored as string)
                char *nums = malloc(buffer_size * sizeof(char));
                if (nums == NULL)
                {
                    printf("Memory allocation failed!\n");
                    return 1;
                }

                do
                {
                    tmp = getc(json);

                    // Assume reached the end of the number value
                    if (tmp == ',' || tmp == '}' || tmp == ':' || isspace(tmp))
                    {
                        ungetc(tmp, json);
                        break;
                    }

                    // Check if buffer is full
                    // `-1` because we need space for the terminator character
                    if (i >= buffer_size - 1)
                    {
                        // Double buffer size
                        buffer_size *= 2;

                        // Reallocate memory for the nums
                        char *temp = realloc(nums, buffer_size * sizeof(char));
                        if (temp == NULL)
                        {
                            printf("Memory reallocation failed!\n");
                            free(nums);
                            return 1;
                        }
                        // Point to newly allocated memory
                        text = temp;
                    }
                    text[i] = tmp;
                    char_num++;
                    i++;
                } while (1);

                // Terminate the string with NUL
                text[i] = '\0';

                tmp = getc(json);
                if (tmp == ':')
                {
                    ungetc(tmp, json);
                    print(text, token(TOKEN_NUMBER, TOKEN_KEY), char_start, line_num, NULL);
                }

                else if (tmp == ',')
                {
                    print(text, token(TOKEN_NUMBER, TOKEN_VALUE), char_start, line_num, NULL);
                }

                free(nums);
                break;
            }

            // Check for `true`, `false` & `null` values respectively
            else if (c == 't' || c == 'f' || c == 'n')
            {
                ungetc(c, json);

                // Reset buffer size
                buffer_size = 10;

                // Reset string index
                i = 0;

                // Remember the starting position of the string
                char_start = char_num;

                // Allocate memory for the text (defined earlier!)
                text = malloc(buffer_size * sizeof(char));
                if (text == NULL)
                {
                    printf("Memory allocation failed!\n");
                    return 1;
                }

                do
                {
                    tmp = fgetc(json);

                    // Assume reached the end of the value
                    if (tmp == ',' || tmp == '}' || tmp == ':' || isspace(tmp))
                    {
                        ungetc(tmp, json);
                        break;
                    }

                    // Check if buffer is full
                    if (i >= buffer_size - 1)
                    {
                        buffer_size *= 2;

                        char *temp = realloc(text, buffer_size * sizeof(char));
                        if (temp == NULL)
                        {
                            printf("Memory reallocation failed!\n");
                            free(text);
                            return 1;
                        }
                        text = temp;
                    }
                    text[i] = tmp;
                    char_num++;
                    i++;
                } while (1);

                text[i] = '\0';

                if (strcmp(text, "true") == 0)
                {
                    print(text, token(TOKEN_TRUE, -1), char_start, line_num, NULL);
                }

                else if ((strcmp(text, "false")) == 0)
                {
                    print(text, token(TOKEN_FALSE, -1), char_start, line_num, NULL);
                }

                else if ((strcmp(text, "null")) == 0)
                {
                    print(text, token(TOKEN_NULL, -1), char_start, line_num, NULL);
                }

                else
                {
                    print(text, token(TOKEN_ERROR, -1), char_num, line_num, "Unknown or incomplete token.");
                }

                free(text);
                break;
            }

            else
            {
                char_num++;
                print(s, token(TOKEN_ERROR, -1), char_num, line_num, NULL);
                break;
            }
        }
    }

    fclose(json);
    return 0;
}

// Format and print parsed text and token type
void print(char *text, char *token, int char_num, int line_num, char *msg)
{
    if (!msg)
    {
        printf("%-12s %-4c %3i:%-3i %4c %s\n", token, '|', line_num, char_num, '|', text);
        printf("-------------+---------------+-------------\n");
        return;
    }

    printf("%-12s %-4c %3i:%-3i %4c %s <- \033[31m%s\033[0m\n", token, '|', line_num, char_num, '|', text, msg);
    printf("-------------+---------------+-------------\n");
}
