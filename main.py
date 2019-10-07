
import sys
import config
from printf import *

keyword_names = {
    "from", "import", "label",

    "goto", "label",
    "if", "then", "else", "end",
    "loop", "for", "in", "while",
    "switch", "case", "default",
    "break", "continue",

    "var", "let",
    "def", "yield", "return",

    "type", "untype",
    "struct", "class", "self", "new",
    "public", "private",

    "true", "false", "null",
}

symbol_names = {
    "BACKSLASH", "SEMICOLON", "COLON", "COMMA", "DOT",
    "LPAR", "RPAR", "LBCE", "RBCE", "LBKT", "RBKT",

    "EQ", "NE", "LT", "LE", "GT", "GE",
    "AND", "OR", "XOR", "NOT",

    "ADD", "SUB", "DIV", "MUL",
    "MOD", "TDIV", "EXP",

    "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT",
    "LSH", "RSH",

    "ASSIGN",
    "ADD_ASSIGN", "SUB_ASSIGN", "DIV_ASSIGN", "MUL_ASSIGN",
    "MOD_ASSIGN", "TDIV_ASSIGN", "EXP_ASSIGN",

    "BIT_AND_ASSIGN", "BIT_OR_ASSIGN", "BIT_XOR_ASSIGN",
    "LSH_ASSIGN", "RSH_ASSIGN",

    "TYPE_OF", "NOT_TYPE_OF",
}


# main

text = """\

#ifndef RESFIG_H
#define RESFIG_H 1

typedef enum
{
#{token_types}
} token_type;

#define KEYWORD struct { const char *word; size_t word_len; token_type type; }
#define ITEM(STR, TYPE) {STR, (sizeof(STR) - 1), TYPE}

KEYWORD reswords[] = {
#{reswords}
};

KEYWORD resymbols[] = {
#{resymbols}
};

#undef KEYWORD
#undef ITEM

#endif // RESFIG_H

"""
