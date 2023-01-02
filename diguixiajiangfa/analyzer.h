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
	START, //开始
	INASSIGN, //赋值
	INCOMMENT, //注释
	INNUM, //数字
	INID, //标识符
	INCHAR, //字符
	INRANGE, //数组下标界限
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
	TokenType reservedLookup(string s);//保留字查找函数，如果是保留字，返回保留字对应的TokenType，否则返回null（记录为ID）
};