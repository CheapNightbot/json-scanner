#include <stdio.h>
#include "token.h"
#include <ctype.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./sjson file.json\n");
        return 1;
    }

    FILE *json = fopen(argv[1], "r");

    char c;
    while ((c = fgetc(json)) != EOF)
    {
        if (c == '{')
        {
            printf("TEXT: %c ~ TOKEN: %d\n", c, TOKEN_LBRACKET);
        }
        else if (isspace(c))
        {
            char d = '\0';
            do
            {
                d = fgetc(json);
            } while (isspace(d));
            ungetc(d, json);
        }
        else if (c == '"')
        {
            printf("TEXT: ");
            char d = '\0';
            do
            {
                printf("%c", d);
                d = fgetc(json);
            } while (d != '"');

            d = fgetc(json);
            if (d == ':')
            {
                ungetc(d, json);
                printf(" ~ TOKEN: %d\n", TOKEN_STRING);
            }
            else
            {
                printf(" ~ TOKEN: %d\n", TOKEN_VALUE);
            }
        }
        else if (c == ':')
        {
            printf("TEXT: %c ~ TOKEN: %d\n", c, TOKEN_COLON);
        }
        else if (c == '}')
        {
            printf("TEXT: %c ~ TOKEN: %d\n", c, TOKEN_RBRACKET);
        }
        else
        {
            if (c == 't')
            {
                ungetc(c, json);
                printf("TEXT: ");
                char d = '\0';
                do
                {
                    printf("%c", d);
                    d = fgetc(json);
                    if (d == '}' || isspace(d))
                    {
                        ungetc(d, json);
                        break;
                    }
                } while (d != ',');
                if (d == '}')
                {
                    ungetc(d, json);
                }
                printf(" ~ TOKEN: %d\n", TOKEN_TRUE);
            }
            else if (c == 'f')
            {
                ungetc(c, json);
                printf("TEXT: ");
                char d = '\0';
                do
                {
                    printf("%c", d);
                    d = fgetc(json);
                    if (d == '}' || isspace(d))
                    {
                        ungetc(d, json);
                        break;
                    }
                } while (d != ',');
                printf(" ~ TOKEN: %d\n", TOKEN_FALSE);
            }
            else if (c == 'n')
            {
                ungetc(c, json);
                printf("TEXT: ");
                char d = '\0';
                do
                {
                    printf("%c", d);
                    d = fgetc(json);
                    if (d == '}' || isspace(d))
                    {
                        ungetc(d, json);
                        break;
                    }
                } while (d != ',');
                printf(" ~ TOKEN: %d\n", TOKEN_NULL);
            }
            else if (isdigit(c))
            {
                ungetc(c, json);
                printf("TEXT: ");
                char d = '\0';
                do
                {
                    printf("%c", d);
                    d = fgetc(json);
                    if (d == '}' || isspace(d))
                    {
                        ungetc(d, json);
                        break;
                    }
                } while (d != ',');
                printf(" ~ TOKEN: %d\n", TOKEN_VALUE);
            }
            else
            {
                printf("TOKEN: %d\n", TOKEN_ERROR);
            }
        }
    }
    return 0;
}
