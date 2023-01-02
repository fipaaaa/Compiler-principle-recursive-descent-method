#include "Token.h"
#include "analyzer.h"
#include <string>

using namespace std;

bool isNumber(char c) {
	if ((c >= '0')&&(c <= '9')) {
		return true;
	}
	else {
		return false;
	}
}

bool isLetter(char c) {
	if (((c >= 'a')&&(c <= 'z'))|| ((c >= 'A') && (c <= 'Z'))) {
		return true;
	}
	else {
		return false;
	}
}

Analyzer::Analyzer(string source) {
	this->source = source;
	this->state = START;
	this->line = 1;
	this->next = 0;
	this->tokenlist = {};
}

TokenType Analyzer::reservedLookup(string s) {
	for (int i = 0; i < MAXRESERVED; i++) {
		if (s == reservedWords[i].str) {
			return reservedWords[i].type;
		}
	}
	return ID;
}

Token Analyzer::getNextToken() {
	state = START;
	while (1) {
		if (next < 0) {
			next = 0;
		}
		if (next + 1 > source.length()) {
			return Token(ENDFILE, "", line);
		}
		if (state == START) {
			while (source.at(next) == ' ' || source.at(next) == '\n' || source.at(next) == '\t') {
				if (source.at(next) == '\n') {
					line++;
				}
				next++;
				if (next + 1 > source.length()) {
					return Token(ENDFILE, "", line);
				}
			}
			if (isLetter(source.at(next))) {
				state = INID;
			}else if (isNumber(source.at(next))) {
				state = INNUM;
			}
			else {
				switch (source.at(next++)) {
					//单个符号：完成状态，此处代码简化
				case'+':
					return Token(PLUS, "", line);
					break;
				case'-':
					return Token(MINUS, "", line);
					break;
				case'*':
					return Token(TIMES, "", line);
					break;
				case'/':
					return Token(OVER, "", line);
					break;
				case'(':
					return Token(LPAREN, "", line);
					break;
				case')':
					return Token(RPAREN, "", line);
					break;
				case';':
					return Token(SEMI, "", line);
					break;
				case'[':
					return Token(LMIDPAREN, "", line);
					break;
				case']':
					return Token(RMIDPAREN, "", line);
					break;
				case'=':
					return Token(EQ, "", line);
					break;
				case'<':
					return Token(LT, "", line);
					break;
				case',':
					return Token(COMMA, "", line);
					break;
				case':':
					state = INASSIGN;
					break;
				case'{':
					state = INCOMMENT;
					break;
				case'.':
					state = INRANGE;
					break;
				case'\'':
					state = INCHAR;
					break;
				default:
					string t(1, source.at(next - 1));
					return Token(ERROR, t, line);
				}
			}
		}
		else if (state == INASSIGN) {
			if (source.at(next) == '=') {
				next++;
				return Token(ASSIGN, "", line);
			}
			else {
				return Token(COLON, "", line);
			}
		}
		else if (state == INCOMMENT) {
			while (source.at(next) != '}' && next < source.length()) {
				if (source.at(next) == '\n')
					line++;
				next++;
			}
			next++;
			state = START;
		}
		else if (state == INNUM) {
			string number = "";
			number += source.at(next++);
			while (next < source.length() && isNumber(source.at(next))) {
				number += source.at(next++);
			}
			return Token(INTC, number, line);
		}
		else if (state == INID) {
			string id = "";
			id += source.at(next++);
			while (next < source.length() && (isNumber(source.at(next)) || isLetter(source.at(next)))) {
				id += source.at(next++);
			}
			TokenType type = reservedLookup(id); //若不是，返回ID
			if (type == ID) {
				return Token(ID, id, line);
			}
			else {
				return Token(type, "", line);
			}
		}
		else if (state == INCHAR) {
			string chars = "";
			while (next < source.length() && (isNumber(source.at(next)) || isLetter(source.at(next)))) {
				chars += source.at(next++);
			}
			if (next < source.length() && source.at(next++) == '\''){
				return Token(CHARC, chars, line);
			}else{
				return Token(ERROR, "char error", line);
			}
		}
		else if (state == INRANGE) {
			if (source.at(next) == '.') {
				next++;
				return Token(UNDERANGE, "", line);
			}
			else {
				return Token(DOT, "", line);
			}
		}
	}
}

vector<Token> Analyzer::getTokenlist() {
	Token temp;
	while (next < source.length()) {
		temp = getNextToken();
		tokenlist.push_back(temp);
	}
	return this->tokenlist;
}