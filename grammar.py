
import string

ignores = (' ', '\t')

newlines = '\n'

name_first_char = string.ascii_letters + '_'
name_rest_char = string.ascii_letters + '_' + string.digits

keywords = {
    "from":         "from",
    "import":       "import",
    "as":           "as",

    "goto":         "goto",
    "label":        "label",

    "if":           "if",
    "then":         "then",
    "else":         "else",
    "end":          "end",

    "loop":         "loop",
    "for":          "for",
    "in":           "in",
    "while":        "while",

    "switch":       "switch",
    "case":         "case",
    "default":      "default",

    "break":        "break",
    "continue":     "continue",

    "var":          "var",
    "let":          "let",

    "def":          "def",
    "yield":        "yield",
    "return":       "return",

    "type":         "type",
    "struct":       "struct",
    "class":        "class",
    "self":         "self",
    "new":          "new",

    "true":         "true",
    "false":        "false",
    "null":         "null",
}

symbols = {
    "BACKSLASH":            "\\",

    "LPAREN":               "(",
    "RPAREN":               "(",
    "LBRACE":               "{",
    "RBRACE":               "}",
    "LBRACKET":             "[",
    "RBRACKET":             "[",

    "SEMICOLON":            ";",
    "COLON":                ":",
    "COMMA":                ",",
    "DOT":                  ".",

    "EQ":                   "==",
    "NE":                   "!=",
    "LT":                   "<",
    "LE":                   "<=",
    "GT":                   ">",
    "GE":                   ">=",

    "AND":                  "&&",
    "OR":                   "||",
    "XOR":                  "^^",
    "NOT":                  "!",

    "ADD":                  "+",
    "SUB":                  "-",
    "DIV":                  "/",
    "MUL":                  "*",

    "MOD":                  "%",
    "TDIV":                 "//",
    "EXP":                  "**",

    "BIT_AND":              "&",
    "BIT_OR":               "|",
    "BIT_XOR":              "^",
    "BIT_NOT":              "~",

    "LSHIFT":               "<<",
    "RSHIFT":               ">>",

    "ASSIGN":               "=",

    "ADD_ASSIGN":           "+=",
    "SUB_ASSIGN":           "-=",
    "DIV_ASSIGN":           "/=",
    "MUL_ASSIGN":           "*=",

    "MOD_ASSIGN":           "%=",
    "TDIV_ASSIGN":          "//=",
    "EXP_ASSIGN":           "**=",

    "BIT_AND_ASSIGN":       "&=",
    "BIT_OR_ASSIGN":        "|=",
    "BIT_XOR_ASSIGN":       "^=",

    "LSHIFT_ASSIGN":        "<<=",
    "RSHIFT_ASSIGN":        ">>=",

    "TYPE_OF":              "?=",
    "NOT_TYPE_OF":          "?!=",
}
