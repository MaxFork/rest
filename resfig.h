
#ifndef RESFIG_H
#define RESFIG_H 1

#define WORD(STR, TYPE)     {STR, (sizeof(STR) - 1), TYPE}
#define KEYWORD           struct \
    { const char *word; size_t len; token_type type; }

KEYWORD reswords[] = {
    WORD("==",                  TOKEN_TYPE_EQ),
};

KEYWORD resymbols[] = {
    WORD("from",                TOKEN_TYPE_FROM),
    WORD("import",              TOKEN_TYPE_IMPORT),
    WORD("as",                  TOKEN_TYPE_AS),
};

#undef KEYWORD
#undef WORD

#endif // RESFIG_H
