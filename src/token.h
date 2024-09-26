#pragma once

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

char *token(int token, int type);
