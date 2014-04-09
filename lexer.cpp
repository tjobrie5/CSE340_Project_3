#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include "Header.h"
//#include "token.h"

using std::cout;
using std::string;

bool send_word = false;
int tokenIndex = -1;
int lineNum = 1;

Token::Token(string a, string b, int c) {
	name = a;
	word = b;
	line = c;
}

std::vector<Token> list(0); //empty list of tokens

void split_lines(string line) {
	string word = ""; //word that will be added onto before printing
	size_t i = 0;
	while(i <= line.length()) { //build strings first
		send_word = false;
		if(line[i] == '\"') { //detect first quotation marks
			if(word != "") {
				send_word = true;
			}
			if(send_word == false) { //only continue if word isn't being sent to lexer
			word = word + line[i]; //start string
			i++;
			while(line[i] != '\"' && i < line.length()) { //while there is open quote, build string
				word = word + line[i];
				i++;
			}
			if(line[i] == '\"') {
				word = word + line[i];
				i++;
				if(i < line.length() && line[i] == '\"' && word.length() < 4) {
					word = word + line[i];
					i++;
				}
				send_word = true;
			}
			else { //invalid string
				//cout << "error\t" << word << '\n';
				growList(); 
				list[tokenIndex] = Token("error", word, lineNum);
				word = ""; //reset word
			}
		}
		}

		if(line[i] == '\'') { //detect first quotation mark
			if(word != "") {
				send_word = true;
			}
			if(send_word == false) { //only continue if word isn't being sent to lexer
			word = word + line[i];
			i++;
			while(line[i] != '\'' && i < line.length()) { //while there is open quote, build string
				word = word + line[i];
				i++;
			}
			
			if(line[i] == '\'') {
				word = word + line[i];
				i++;
				if(word.length() == 2)
					send_word = true;
				else if(i < line.length() && line[i] == '\'' && word.length() < 4) {
					word = word + line[i];
					i++;
				}
				send_word = true;
			}
			else { //invalid string
				//cout << "error\t" << word << '\n';
				growList(); 
				list[tokenIndex] = Token("error", word, lineNum);
				word = ""; //reset word
			}
		}
		}
																		  //line[i] == 0 checks if char is NULL
		if(line[i] == '\t' || line[i] == ' ' || isDelimiter(line[i]) || isOperator(line[i]) || line[i] == 0 || send_word) { //check for delimiter or operator at end of line
			if(word != "" && !isKeyword(word)) { //check if there is a string to print
				growList(); //grow vector list by 1
				list[tokenIndex] = Token(lexer(word), word, lineNum);
			}
			else if(isKeyword(word)) {//check for keyword
				growList(); 
				list[tokenIndex] = Token("keyword", word, lineNum);
			}
			if(isDelimiter(line[i])) {
				word = string(1, line[i]); //cast char to string
				growList(); 
				list[tokenIndex] = Token("delimiter", word, lineNum);
			}
			else if (isOperator(line[i])) { //check for operator
				word = string(1, line[i]); //cast char to string
				growList(); 
				list[tokenIndex] = Token("operator", word, lineNum);
			}
			word = ""; //reset word
		}
			else 
				word = word + line[i];
			if(send_word == false || isDelimiter(line[i]) || isOperator(line[i]))
				i++;
	}//end while
	lineNum++; //increment line number
}

bool isOperator(char c) { //check for operator
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '='  || c == '&' || 
		c == '|' || c == '!' || c == '<' || c == '>') {
			return true;
	}
	else
		return false;
}

bool isDelimiter(char c) { //check for delimiter
	if(c == ':'  || c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' ||  c == '[' || c == ']') {
			return true;
	}
	return false;
}

bool isKeyword(string s) { //check if potential ID is a keyword
	if(s == "read" || s == "print" || s == "if" || s == "else" || s == "while" || s == "void" || 
		s == "int" || s == "char" || s == "string" || s == "float" || s == "boolean" ||
		s == "true" ||s == "false" || s == "return" || s == "for" || s == "integer")
		return true;
	else
		return false;
}

string lexer(string word) { //this function takes a string and determines the token type
	int state = 0;
	if(word[0] == '\"' && word[word.length()-1] == '\"') //check for string
		return "string";
	for(size_t i = 0; i < word.length(); i++) {
		state = calculateNextState(state, word[i]);
	}

	if(state == 1) //route state to proper type
		return "integer";
	
	else if(state == 3)
		return "float";

	else if(state == 4)
		return "identifier";

	else if(state == 5)
		return "integer";
	
	else if(state == 6)
		return "octal";
	
	else if(state == 7)
		return "hexadecimal";

	else if(state == 11)
		return "character";

	else if(state == 13)
		return "character";

	else if(state == 15)
		return "string";

	else 
		return "error";
}


int calculateNextState(int current_state, char key) {
	int new_state = -1; //default state is reject
	
	std::unordered_map<char, int> hashtable0; //state 0 hashtable
	hashtable0.emplace('\'', 8);

	hashtable0.emplace('0', 5);
	hashtable0.emplace('1', 1);
	hashtable0.emplace('2', 1);
	hashtable0.emplace('3', 1);
	hashtable0.emplace('4', 1);
	hashtable0.emplace('5', 1);
	hashtable0.emplace('6', 1);
	hashtable0.emplace('7', 1);
	hashtable0.emplace('8', 1);
	hashtable0.emplace('9', 1);

	hashtable0.emplace('.', 2);
		
	hashtable0.emplace('$', 4);
	hashtable0.emplace('_', 4);
	hashtable0.emplace('a', 4);	hashtable0.emplace('A', 4);
	hashtable0.emplace('b', 4);	hashtable0.emplace('B', 4);
	hashtable0.emplace('c', 4);	hashtable0.emplace('C', 4);
	hashtable0.emplace('d', 4);	hashtable0.emplace('D', 4);
	hashtable0.emplace('e', 4);	hashtable0.emplace('E', 4);
	hashtable0.emplace('f', 4);	hashtable0.emplace('F', 4);
	hashtable0.emplace('g', 4);	hashtable0.emplace('G', 4);
	hashtable0.emplace('h', 4);	hashtable0.emplace('H', 4);
	hashtable0.emplace('i', 4);	hashtable0.emplace('I', 4);
	hashtable0.emplace('j', 4);	hashtable0.emplace('J', 4);
	hashtable0.emplace('k', 4);	hashtable0.emplace('K', 4);
	hashtable0.emplace('l', 4);	hashtable0.emplace('L', 4);
	hashtable0.emplace('m', 4);	hashtable0.emplace('M', 4);
	hashtable0.emplace('n', 4);	hashtable0.emplace('N', 4);
	hashtable0.emplace('o', 4);	hashtable0.emplace('O', 4);
	hashtable0.emplace('p', 4);	hashtable0.emplace('P', 4);
	hashtable0.emplace('q', 4);	hashtable0.emplace('Q', 4);
	hashtable0.emplace('r', 4);	hashtable0.emplace('R', 4);
	hashtable0.emplace('s', 4);	hashtable0.emplace('S', 4);
	hashtable0.emplace('t', 4);	hashtable0.emplace('T', 4);
	hashtable0.emplace('u', 4);	hashtable0.emplace('U', 4);
	hashtable0.emplace('v', 4);	hashtable0.emplace('V', 4);
	hashtable0.emplace('w', 4);	hashtable0.emplace('W', 4);
	hashtable0.emplace('x', 4);	hashtable0.emplace('X', 4);
	hashtable0.emplace('y', 4);	hashtable0.emplace('Y', 4);
	hashtable0.emplace('z', 4); hashtable0.emplace('Z', 4);

	std::unordered_map<char, int> hashtable1; //state 1 hashtable
	hashtable1.emplace('0', 1);
	hashtable1.emplace('1', 1);
	hashtable1.emplace('2', 1);
	hashtable1.emplace('3', 1);
	hashtable1.emplace('4', 1);
	hashtable1.emplace('5', 1);
	hashtable1.emplace('6', 1);
	hashtable1.emplace('7', 1);
	hashtable1.emplace('8', 1);
	hashtable1.emplace('9', 1);

	hashtable1.emplace('.', 2);

	std::unordered_map<char, int> hashtable2; //state 2 hashtable
	hashtable2.emplace('0', 3);
	hashtable2.emplace('1', 3);
	hashtable2.emplace('2', 3);
	hashtable2.emplace('3', 3);
	hashtable2.emplace('4', 3);
	hashtable2.emplace('5', 3);
	hashtable2.emplace('6', 3);
	hashtable2.emplace('7', 3);
	hashtable2.emplace('8', 3);
	hashtable2.emplace('9', 3);

	std::unordered_map<char, int> hashtable3; //state 3 hashtable
	hashtable3.emplace('0', 3);
	hashtable3.emplace('1', 3);
	hashtable3.emplace('2', 3);
	hashtable3.emplace('3', 3);
	hashtable3.emplace('4', 3);
	hashtable3.emplace('5', 3);
	hashtable3.emplace('6', 3);
	hashtable3.emplace('7', 3);
	hashtable3.emplace('8', 3);
	hashtable3.emplace('9', 3);

	std::unordered_map<char, int> hashtable4; //state 4 hashtable
	hashtable4.emplace('$', 4);
	hashtable4.emplace('_', 4);
	
	hashtable4.emplace('0', 4);
	hashtable4.emplace('1', 4);
	hashtable4.emplace('2', 4);
	hashtable4.emplace('3', 4);
	hashtable4.emplace('4', 4);
	hashtable4.emplace('5', 4);
	hashtable4.emplace('6', 4);
	hashtable4.emplace('7', 4);
	hashtable4.emplace('8', 4);
	hashtable4.emplace('9', 4);
		
	hashtable4.emplace('a', 4);	hashtable4.emplace('A', 4);
	hashtable4.emplace('b', 4);	hashtable4.emplace('B', 4);
	hashtable4.emplace('c', 4);	hashtable4.emplace('C', 4);
	hashtable4.emplace('d', 4);	hashtable4.emplace('D', 4);
	hashtable4.emplace('e', 4);	hashtable4.emplace('E', 4);
	hashtable4.emplace('f', 4);	hashtable4.emplace('F', 4);
	hashtable4.emplace('g', 4);	hashtable4.emplace('G', 4);
	hashtable4.emplace('h', 4);	hashtable4.emplace('H', 4);
	hashtable4.emplace('i', 4);	hashtable4.emplace('I', 4);
	hashtable4.emplace('j', 4);	hashtable4.emplace('J', 4);
	hashtable4.emplace('k', 4);	hashtable4.emplace('K', 4);
	hashtable4.emplace('l', 4);	hashtable4.emplace('L', 4);
	hashtable4.emplace('m', 4);	hashtable4.emplace('M', 4);
	hashtable4.emplace('n', 4);	hashtable4.emplace('N', 4);
	hashtable4.emplace('o', 4);	hashtable4.emplace('O', 4);
	hashtable4.emplace('p', 4);	hashtable4.emplace('P', 4);
	hashtable4.emplace('q', 4);	hashtable4.emplace('Q', 4);
	hashtable4.emplace('r', 4);	hashtable4.emplace('R', 4);
	hashtable4.emplace('s', 4);	hashtable4.emplace('S', 4);
	hashtable4.emplace('t', 4);	hashtable4.emplace('T', 4);
	hashtable4.emplace('u', 4);	hashtable4.emplace('U', 4);
	hashtable4.emplace('v', 4);	hashtable4.emplace('V', 4);
	hashtable4.emplace('w', 4);	hashtable4.emplace('W', 4);
	hashtable4.emplace('x', 4);	hashtable4.emplace('X', 4);
	hashtable4.emplace('y', 4);	hashtable4.emplace('Y', 4);
	hashtable4.emplace('z', 4); hashtable4.emplace('Z', 4);

	std::unordered_map<char, int> hashtable5; //state 5 hashtable
	hashtable5.emplace('x', 7);

	hashtable5.emplace('0', 6);
	hashtable5.emplace('1', 6);
	hashtable5.emplace('2', 6);
	hashtable5.emplace('3', 6);
	hashtable5.emplace('4', 6);
	hashtable5.emplace('5', 6);
	hashtable5.emplace('6', 6);
	hashtable5.emplace('7', 6);

	hashtable5.emplace('.', 2);

	std::unordered_map<char, int> hashtable6; //state 6 hashtable
	hashtable6.emplace('0', 6);
	hashtable6.emplace('1', 6);
	hashtable6.emplace('2', 6);
	hashtable6.emplace('3', 6);
	hashtable6.emplace('4', 6);
	hashtable6.emplace('5', 6);
	hashtable6.emplace('6', 6);
	hashtable6.emplace('7', 6);

	std::unordered_map<char, int> hashtable7; //state 7 hashtable
	hashtable7.emplace('0', 7);
	hashtable7.emplace('1', 7);
	hashtable7.emplace('2', 7);
	hashtable7.emplace('3', 7);
	hashtable7.emplace('4', 7);
	hashtable7.emplace('5', 7);
	hashtable7.emplace('6', 7);
	hashtable7.emplace('7', 7);
	hashtable7.emplace('8', 7);
	hashtable7.emplace('9', 7);

	hashtable7.emplace('a', 7);	hashtable7.emplace('A', 7);	
	hashtable7.emplace('b', 7); hashtable7.emplace('B', 7);	
	hashtable7.emplace('c', 7); hashtable7.emplace('C', 7);	
	hashtable7.emplace('d', 7); hashtable7.emplace('D', 7);	
	hashtable7.emplace('e', 7); hashtable7.emplace('E', 7);	
	hashtable7.emplace('f', 7); hashtable7.emplace('F', 7);	

	std::unordered_map<char, int> hashtable8; //state 8 hashtable
	if(key != '\\')
		hashtable8.emplace(key, 9); //we know the key is a char, so this is valid
	hashtable8.emplace('\\', 10);

	std::unordered_map<char, int> hashtable9;	//state 9 hashtable
	if(key != '\'') 
		hashtable9.emplace(key, 18);
	hashtable9.emplace('\'', 11);
	

	std::unordered_map<char, int> hashtable10;	//state 10 hashtable
	hashtable10.emplace(key, 12);

	std::unordered_map<char, int> hashtable11;	//state 11 hashtable

	std::unordered_map<char, int> hashtable12;	//state 12 hashtable
	hashtable12.emplace('\'', 13);

	std::unordered_map<char, int> hashtable13;	//state 13 hashtable

	std::unordered_map<char, int> hashtable18;
	if(key != '\'')
		hashtable18.emplace(key, 18);
	if(key == '\'')
		hashtable18.emplace(key, -1);

	switch(current_state) {
	case 0:
		if(hashtable0.count(key) != 0) //check if key is in hashtable
			new_state = hashtable0[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 1:
		if(hashtable1.count(key) != 0) //check if key is in hashtable
			new_state = hashtable1[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 2:
		if(hashtable2.count(key) != 0) //check if key is in hashtable
			new_state = hashtable2[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 3:
		if(hashtable3.count(key) != 0) //check if key is in hashtable
			new_state = hashtable3[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 4:
		if(hashtable4.count(key) != 0) //check if key is in hashtable
			new_state = hashtable4[key];
		else
			new_state = -1; //return reject state if not found
		break;
	
	case 5:
		if(hashtable5.count(key) != 0) //check if key is in hashtable
			new_state = hashtable5[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 6:
		if(hashtable6.count(key) != 0) //check if key is in hashtable
			new_state = hashtable6[key];
		else
			new_state = -1; //return reject state if not found
		break;
	
	case 7:
		if(hashtable7.count(key) != 0) //check if key is in hashtable
			new_state = hashtable7[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 8:
		if(hashtable8.count(key) != 0) //check if key is in hashtable
			new_state = hashtable8[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 9:
		if(hashtable9.count(key) != 0) //check if key is in hashtable
			new_state = hashtable9[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 10:
		if(hashtable10.count(key) != 0) //check if key is in hashtable
			new_state = hashtable10[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 11:
		if(hashtable11.count(key) != 0) //check if key is in hashtable
			new_state = hashtable11[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 12:
		if(hashtable12.count(key) != 0) //check if key is in hashtable
			new_state = hashtable12[key];
		else
			new_state = -1; //return reject state if not found
		break;

	case 13:
		if(hashtable13.count(key) != 0) //check if key is in hashtable
			new_state = hashtable13[key];
		else
			new_state = -1; //return reject state if not found
		break;
	}

	return new_state; 
}

void growList() {
	list.resize(list.size() + 1);
	tokenIndex++;
}

void printList(std::vector<Token> list1) {
	if(tokenIndex == 0)
		cout << "Error: no tokens in list";
	else {
		for(int i = 1; i <= tokenIndex; i++) {
			cout << list1[i].name << ' ';
			cout << list1[i].word << ' ';
			cout << list1[i].line << '\n';
		}
	}
}

std::vector<Token> getList() {
	return list;
}