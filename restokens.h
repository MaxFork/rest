
#ifndef RESTOKENS_H
#define RESTOKENS_H 1

typedef uint8_t token_type;

#define TOKEN_TYPE_START            0

#define TOKEN_TYPE_NULL             (TOKEN_TYPE_START + 0)
#define TOKEN_TYPE_NEWLINE          (TOKEN_TYPE_START + 1)
#define TOKEN_TYPE_NAME             (TOKEN_TYPE_START + 2)

#undef  TOKEN_TYPE_START
#define TOKEN_TYPE_START            3

#define TOKEN_TYPE_FROM             (TOKEN_TYPE_START + 0)
#define TOKEN_TYPE_IMPORT           (TOKEN_TYPE_START + 1)
#define TOKEN_TYPE_AS               (TOKEN_TYPE_START + 2)

#undef  TOKEN_TYPE_START
#define TOKEN_TYPE_START            6

#define TOKEN_TYPE_GOTO             (TOKEN_TYPE_START + 0)
#define TOKEN_TYPE_LABEL            (TOKEN_TYPE_START + 1)

#undef  TOKEN_TYPE_START
#define TOKEN_TYPE_START            8

#define TOKEN_TYPE_IF               (TOKEN_TYPE_START + 0)
#define TOKEN_TYPE_THEN             (TOKEN_TYPE_START + 1)
#define TOKEN_TYPE_ELSE             (TOKEN_TYPE_START + 2)
#define TOKEN_TYPE_END              (TOKEN_TYPE_START + 3)

#undef  TOKEN_TYPE_START
#define TOKEN_TYPE_START            12

#define TOKEN_TYPE_EQ               (TOKEN_TYPE_START + 0)
#define TOKEN_TYPE_NE               (TOKEN_TYPE_START + 1)
#define TOKEN_TYPE_LT               (TOKEN_TYPE_START + 2)
#define TOKEN_TYPE_LE               (TOKEN_TYPE_START + 3)

#undef  TOKEN_TYPE_START
#define TOKEN_TYPE_START            16

#define TOKEN_TYPE_MAX 100

#endif
