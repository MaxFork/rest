package types;

public enum TokenType
{
	NAME, NEWLINE,
	
	STRING, NUMBER,
	
	FROM, IMPORT, AS,
	
	GOTO, LABEL,
	IF, THEN, ELSE, END,
	LOOP, FOR, IN, WHILE,
	SWITCH, CASE, DEFAUL,
	BREAK, CONTINUE,
	
	VAR, CONST, LET, REF,
	DEF, YIELD, RETURN,
	
	TYPE, UNTYPE,
	STRUCT, CLASS, SELF,
	PUBLIC, PRIVATE,
	
	TRUE, FALSE, NULL, NONE,
	
	BACKSLASH, SEMICOLON, COLON, COMMA, DOT,
	LPAR, RPAR, LBCE, RBCE, LBKT, RBKT,
	
	EQ, NE, LT, LE, GT, GE,
	AND, OR, XOR, NOT,
	
	ADD, SUB, DIV, MUL,
	MOD, TDIV, EXP,
	
	BIT_AND, BIT_OR, BIT_XOR, BIT_NOT,
	LSHIFT, RSHIFT,
	
	ASSIGN,
	ADD_ASSIGN, SUB_ASSIGN, DIV_ASSIGN, MUL_ASSIGN,
	MOD_ASSIGN, TDIV_ASSIGN, EXP_ASSIGN,
	
	BIT_AND_ASSIGN, BIT_OR_ASSIGN, BIT_XOR_ASSIGN,
	LSHIFT_ASSIGN, RSHIFT_ASSIGN,
}
