
#ifndef RESTOKENS_H
#define RESTOKENS_H 1

typedef enum
{
    TOKEN_TYPE_NULL,
    TOKEN_TYPE_NEWLINE,
    TOKEN_TYPE_NAME,

    TOKEN_TYPE_FROM,
    TOKEN_TYPE_IMPORT,

    TOKEN_TYPE_GOTO,

} token_type;

#endif
