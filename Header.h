#ifndef HEADER_H
#define HEADER_H
using std::string;

class Token { //token class we will use to record attributes of each token
public:
	string name;
	string word;
	int line;
	Token(string a = "", string b = "", int c = 0); 
};

void split_lines(string line);
bool isOperator(char c);
bool isDelimiter(char c);
bool isKeyword(string s); 
string lexer(string word);
int calculateNextState(int current_state, char letter);
void growList();
void printList(std::vector<Token> list1);
std::vector<Token> getList();

#endif