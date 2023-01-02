#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum {
	/*���ǵ��ʷ���*/
	ENDFILE, ERROR,
	/*������*/
	PROGRAM, PROCEDURE, TYPE, VAR, IF,
	THEN, ELSE, FI, WHILE, DO,
	ENDWH, BEGINl, ENDl, READ, WRITE,
	ARRAY, OF, RECORD, RETURNl,
	//����
	INTEGER, CHARl,
	/*���ַ����ʷ���*/
	ID, INTC, CHARC, //��ĸ��ͷ�İ�����ĸ���ֵ��ַ���ΪID������ΪINTC���������ڵ���ĸ����ΪCHARC
	/*�������*/
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
	int line; //���ڴ�������
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
			cout << "(������)";
		}
		else if (this->type > 25) {
			cout << "(����)";
		}
		cout << endl;
	}
};