
#ifndef RESFIG_H
#define RESFIG_H 1

#define WORD(STR, TYPE)     {STR, (sizeof(STR) - 1), TYPE}
#define KEYWORD           struct \
    { const char *word; size_t word_len; token_type type; }

KEYWORD reswords[] = {
    WORD("from",                TOKEN_TYPE_FROM),
    WORD("import",              TOKEN_TYPE_IMPORT),
    WORD("as",                  TOKEN_TYPE_AS),

    WORD("goto",                TOKEN_TYPE_GOTO),
    WORD("label",               TOKEN_TYPE_LABEL),

    WORD("if",                  TOKEN_TYPE_IF),
    WORD("then",                TOKEN_TYPE_THEN),
    WORD("else",                TOKEN_TYPE_ELSE),
    WORD("end",                 TOKEN_TYPE_END),
};

KEYWORD resymbols[] = {
    WORD("==",                  TOKEN_TYPE_EQ),
    WORD("!=",                  TOKEN_TYPE_NE),
    WORD("<",                   TOKEN_TYPE_LT),
    WORD("<=",                  TOKEN_TYPE_LE),
    
};

#undef KEYWORD
#undef WORD

#endif // RESFIG_H
