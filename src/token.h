typedef enum
{
    TOKEN_EOF = 0,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_KEY,
    TOKEN_VALUE,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_ERROR
} token_t;

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
