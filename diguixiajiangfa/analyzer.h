#pragma once
#include <iostream>
#include <vector>

#include "Token.h"

using namespace std;

const int MAXRESERVED = 21;
static struct {
	string str;
	TokenType type;
} reservedWords[MAXRESERVED] = {
	{"program",PROGRAM},{"type",TYPE},{"var",VAR},
	{"procedure",PROCEDURE},{"begin",BEGINl},{"end",ENDl},
	{"array",ARRAY},{"of",OF},{"record",RECORD},{"if",IF},
	{"then",THEN},{"else",ELSE},{"fi",FI},{"while",WHILE},
	{"do",DO},{"endwh",ENDWH},{"read",READ},{"write",WRITE},
	{"return",RETURNl},{"integer",INTEGER },{"char",CHARl}
};

typedef enum {
	START, //��ʼ
	INASSIGN, //��ֵ
	INCOMMENT, //ע��
	INNUM, //����
	INID, //��ʶ��
	INCHAR, //�ַ�
	INRANGE, //�����±����
}State;

class Analyzer {
private:
	vector<Token> tokenlist;
	string source;
	State state;
	int line;
	int next;
public:
	Analyzer(string source);
	vector<Token> getTokenlist(); 
	Token getNextToken();
	TokenType reservedLookup(string s);//�����ֲ��Һ���������Ǳ����֣����ر����ֶ�Ӧ��TokenType�����򷵻�null����¼ΪID��
};