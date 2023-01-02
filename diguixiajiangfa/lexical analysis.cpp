#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Token.h"
#include "analyzer.h"
#include "dgxj.h"
using namespace std;
vector<Token> v;
int main()
{
	string program = "";
	string buffer;
	ifstream in;
	in.open("c2.txt");
	if (!in.is_open())
	{
		cout << "打开程序文件错误";
		return 1;
	}
	while (getline(in, buffer))
	{
		program += buffer;
		program += "\n";
	}
	Analyzer analyzer(program);
	v = analyzer.getTokenlist();
	for (int i = 0; i < v.size(); i++) {
		v[i].printToken();
	}
	TreeNode* tree;
	tree = parse();
	return 0;
}
