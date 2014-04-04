#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>

// function declarations:
struct Token
{
	std::string type;
	std::string name;
	int line;
};

void init(int argc, char* argv[]);
void split_line(std::string line, int lineCount);
bool isDelimiter(char alpha);
bool isOperator(char alpha);
bool isSeparator(char alpha);
bool isKeyword(std::string word);
Token lexer(std::string word, int lineCount);
int calculateNextState(int state, char input);
void program();
void dvar_global();
void dvar_local();
void dmethod();
void parameter();
void line();
void _if();
void _while();
void assign();
void _return();
void call_function();
void exprlog();
void opand();
void exprel();
void opno();
void expr();
void product();
void sign();
void term();
void nextToken();
bool eof();
void backToken();
bool eol();
void eraseWhitespace();