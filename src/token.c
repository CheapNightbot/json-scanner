#include "token.h"

// Return token type string based on token
char *token(int token, int type)
{
    switch (token)
    {
    case TOKEN_LBRACE:
        return "LBRACE";

    case TOKEN_RBRACE:
        return "RBRACE";

    case TOKEN_LBRACKET:
        return "LBRACKET";

    case TOKEN_RBRACKET:
        return "RBRACKET";

    case TOKEN_COLON:
        return "COLON";

    case TOKEN_COMMA:
        return "COMMA";

    case TOKEN_NUMBER:
        return "NUMBER";

    case TOKEN_STRING:
        switch (type)
        {
        case TOKEN_KEY:
            return "STRING_KEY";

        case TOKEN_VALUE:
            return "STRING_VALUE";

        default:
            return "STRING";
        }

    case TOKEN_TRUE:
        return "TRUE";

    case TOKEN_FALSE:
        return "FALSE";

    case TOKEN_NULL:
        return "NULL";

    case TOKEN_ERROR:
        return "ERROR";

    default:
        // Handle error or unknown token
        return "UNKNOWN";
    }
}
