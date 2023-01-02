#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum {
	/*薄记单词符号*/
	ENDFILE, ERROR,
	/*保留字*/
	PROGRAM, PROCEDURE, TYPE, VAR, IF,
	THEN, ELSE, FI, WHILE, DO,
	ENDWH, BEGINl, ENDl, READ, WRITE,
	ARRAY, OF, RECORD, RETURNl,
	//类型
	INTEGER, CHARl,
	/*多字符单词符号*/
	ID, INTC, CHARC, //字母开头的包含字母数字的字符串为ID，整数为INTC，单引号内的字母数字为CHARC
	/*特殊符号*/
	ASSIGN, EQ, LT, PLUS, MINUS, // := = < + -
	TIMES, OVER, LPAREN, RPAREN, DOT, // * /  ( ) .
	COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN, //: ; , [ ]
	UNDERANGE // ..
} TokenType;

static string type1[] = { "ENDFILE", "ERROR","PROGRAM", "PROCEDURE", "TYPE", "VAR", "IF","THEN", "ELSE", "FI", "WHILE", "DO","ENDWH", "BEGINl", "ENDl", "READ", "WRITE",
"ARRAY", "OF", "RECORD", "RETURNl","INTEGER", "CHARl" ,"ID" , "INTC", "CHARC", "ASSIGN", "EQ", "LT", "PLUS", "MINUS", "TIMES", "OVER", "LPAREN",
"RPAREN", "DOT", "COLON", "SEMI", "COMMA", "LMIDPAREN", "RMIDPAREN", "UNDERANGE" };

class Token {
public:
	TokenType type;
	string context;
	int line; //所在代码行数
public:
	Token(){}
	Token(TokenType type, string context, int line) {
		this->type = type;
		this->context = context;
		this->line = line;
	}
	Token(const Token & token) {
		this->type = token.type;
		this->context = token.context;
		this->line = token.line;
	}
	void printToken() {
		cout << this->line << ": " << type1[this->type] << " " << this->context << " ";
		if (this->type > 1 && this->type < 23) {
			cout << "(保留字)";
		}
		else if (this->type > 25) {
			cout << "(符号)";
		}
		cout << endl;
	}
};