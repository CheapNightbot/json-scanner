typedef enum
{
    TOKEN_EOF = 0,
    TOKEN_LBRACE,
    TOKEN_LBRACKET,
    TOKEN_COMMA,
    TOKEN_STRING,
    TOKEN_COLON,
    TOKEN_VALUE,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_RBRACKET,
    TOKEN_RBRACE,
    TOKEN_ERROR
} token_t;


// Return token type string based on token
char *token(int token)
{
    switch (token)
    {
    case TOKEN_LBRACE:
        return "LBRACE";
        break;
    case TOKEN_LBRACKET:
        return "LBRACKET";
        break;
    case TOKEN_COMMA:
        return "COMMA";
        break;
    case TOKEN_STRING:
        return "STRING";
        break;
    case TOKEN_COLON:
        return "COLON";
        break;
    case TOKEN_VALUE:
        return "VALUE";
        break;
    case TOKEN_TRUE:
        return "TRUE";
        break;
    case TOKEN_FALSE:
        return "FALSE";
        break;
    case TOKEN_NULL:
        return "NULL";
        break;
    case TOKEN_RBRACKET:
        return "RBRACKET";
        break;
    case TOKEN_RBRACE:
        return "RBRACE";
        break;
    case TOKEN_ERROR:
        return "ERROR";
        break;
    default:
        // Handle error or unknown token
        return "UNKNOWN";
        break;
    }
}
