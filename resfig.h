
#ifndef RESFIG_H
#define RESFIG_H 1

#define KEYWORD \
    struct { const char *word; size_t word_len; token_type type; }
#define ITEM(STR, TYPE) {STR, (sizeof(STR) - 1), TYPE}

KEYWORD reswords[] = {
    ITEM("from",                TOKEN_TYPE_FROM),
    ITEM("import",              TOKEN_TYPE_IMPORT),
    ITEM("as",                  TOKEN_TYPE_AS),

    ITEM("goto",                TOKEN_TYPE_GOTO),
    ITEM("label",               TOKEN_TYPE_LABEL),

    ITEM("if",                  TOKEN_TYPE_IF),
    ITEM("then",                TOKEN_TYPE_THEN),
    ITEM("else",                TOKEN_TYPE_ELSE),
    ITEM("end",                 TOKEN_TYPE_END),
};

KEYWORD resymbols[] = {
    ITEM("==",                  TOKEN_TYPE_EQ),
    ITEM("!=",                  TOKEN_TYPE_NE),
    ITEM("<",                   TOKEN_TYPE_LT),
    ITEM("<=",                  TOKEN_TYPE_LE),

};

#undef KEYWORD
#undef ITEM

#endif // RESFIG_H
