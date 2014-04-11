/* 
John Lillyblad
CSE 340
Assignment 2
2/22/2014

This program will take an input file as argv[1] and generate an output file argv[2] that is the 
parsed interpretation of the lexical analysis of the input. */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "lexer.hpp"
using std::cout;
using std::string;
using std::vector;

unsigned int index;
vector<Token> myTokens(1); //empty list of tokens

Token nextToken() { 
	Token next;
	if(index < myTokens.size() - 1) {
		next = myTokens[index + 1];
	}
	else {
		next = myTokens[index];
	}
	return next;
}

Token currentToken() {
	if(index >= 0)
		return myTokens[index];
	else
		return myTokens[0];
}

Token endToken() {
	return myTokens[myTokens.size()-1];
}

bool increment();
bool isType(string s); //helper functions
bool isLast();
bool errorHandling(int temp);

bool Program();
bool dvar_global();
bool dvar_local();
bool dmethod();
bool parameter();
bool line();
bool if_function();
bool while_function();
bool assign();
bool call_function();
bool return_function();
bool exprlog();
bool opand();
bool opno();
bool exprel();
bool expr();
bool product();
bool sign();
bool term();


void startFile(const char* filename) {
	freopen(filename, "w", stdout); //initialize file (destroy existing, if applicable)
}

int main(int argc, char* argv[]) {
	index = 0; //index that will be used to iterate through vector of tokens
	const char* filename = argv[2];
	string line;
	std::ifstream fin;		//input stream
	fin.open(argv[1]);		//open input text file for input operations
	startFile(filename);	//open output stream, redirect standart output to file. COMMENT THIS LINE OUT TO SEND EVERYTHING TO SCREEN FOR DEBUGGING.

	if(fin.is_open()) {
		while(getline(fin, line)) {
			split_lines(line);
		}
		myTokens = getList();
		/*for(size_t i = 0; i < myTokens.size(); i++) {
			cout << "Index " << i << "\t\tline:" << myTokens[i].line << '\n';
			cout << "Index " << i << "\t\tname:" << myTokens[i].name << '\n';
			cout << "Index " << i << "\t\tword:" << myTokens[i].word << '\n';
			cout << '\n';
		}*/
	}
	//printList(myTokens); //uncomment to print tokens from lexer

	if(Program() && index == myTokens.size() - 1) {
		//freopen("CON","w",stdout); //uncomment for Windows IDE (Visual Studio)
		freopen ("/dev/tty", "a", stdout); //uncomment for g++ 
		cout << "Build successful" << '\n';
	}
	fin.close();
	fclose(stdout);
	return 0;
}

bool increment() {//if cannot increment when we should be able to, report fault
	bool success = false;
	if(index < myTokens.size() - 1) { //only increment if there is another valid token	
		index++; 
		success = true;
	}
	else if(currentToken().line == endToken().line) {
		success = false;
	}
	return success;
}

bool isType(string s) { //evaluates word of a token
	if(s == "int" || s == "char" || s == "string" || s == "float" || s == "boolean" || s == "integer"
		|| s == "void")
		return true;
	else
		return false;
}

bool isLast() { //determines if token is the last token
	bool isLast = false;
	if(index == myTokens.size() - 1) {
		isLast = true;
	}
	return isLast;
}

bool errorHandling(int temp) {
	bool success = true;
	while(nextToken().word != ";" && nextToken().line == temp && !isLast()) {
		if(increment() == false) {
			success = false;
		}
	}
	if(nextToken().word == ";") {
		if(increment() == false) {//if there is no next token, consume ";"
			success = false;
		}
		else {
			while(nextToken().line == temp) {
				if(increment() == false) {
					success = false;
				}
			}
		}
	}
	if(currentToken().word == "{" && nextToken().word == "}") {//skip past curly braces
		increment();
	}
	return success;
}

bool Program() {
	bool success = true;
	bool error = false;
	int temp = 0; //used for error recovery
	if(myTokens.size() == 0)
		return true;
	do {	
		temp = currentToken().line;
		if(index == 0) { //check for the first type of the program		
			if(isType(currentToken().word)) {}//do nothing
			else
				cout << "Line " << currentToken().line << ":" << "\texpected type" << '\n';
		}
		else if(isType(nextToken().word)) {
			increment();
		}
		else {
			//cout << "Line " << nextToken().line << ":" << "\texpected type" << '\n';
			error = true; 
			if(nextToken().line == endToken().line) {
				increment(); //consume final token, ending program
			}
		}
		if(nextToken().name == "identifier" && !error) {
			increment();
		}
		else if(nextToken().line != temp && !error) { //if next token is on next line
			cout << "Line " << currentToken().line << ":" << "\texpected identifier" << '\n';	
			temp = currentToken().line;
			error = true;
		}
		else if(!error) {
			cout << "Line " << currentToken().line << ":" << "\texpected identifier" << '\n';	
			error = true;
		}
		if(nextToken().name == "delimiter" && nextToken().word != ";"  && nextToken().word != "," 
			&& !error) {
			success = dmethod();
		}
		else if(!error) {
			dvar_global();
		}
		if(error) {
			if(endToken().line == 1) { //check if error is on first line
				increment();
			}
			else {
				if(errorHandling(temp)) {	//this will increment to first token of next line
					//do nothing			//errorHandling returns false if already on first token of next line
				}
			}
		}
		error = false; //reset error
	} while(index < myTokens.size() - 1);
	if(isType(currentToken().word) && currentToken().line > 1) {
		cout << "Line " << currentToken().line << ":" << "\texpected identifier" << '\n';
	}
	else if(currentToken().name == "identifier" && currentToken().line > 1) {
		cout << "Line " << currentToken().line << ":" << "\texpected type" << '\n';
	}
	return success;
}

bool dvar_global() { //after reading a type and id
	bool success = true;
	bool error = false;
	int temp = 0; //used for error recovery

	while(nextToken().word == "," && !error) {
		increment();
		if(nextToken().name == "identifier") {
			increment();
		}
		else {
			temp = currentToken().line;
			cout << "Line " << currentToken().line << ":\t" << "expected identifier" << '\n';	
			error = true;
		}
	}
	if(nextToken().name == "identifier" && !error && !isLast()) {
		temp = currentToken().line;
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter ," << '\n';	
		error = true;
	}
	else if(nextToken().word == ";" && !error) {
		//do nothing
	}
	else if((nextToken().word != ";" || isLast()) && !error) {
		if(isLast()) {
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter ;" << '\n';
			error = true;
		}
		else if(!error) {
			temp = currentToken().line;
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter ;" << '\n';
			error = true;
		}
	}
	if(error) {
		errorHandling(temp);
	}
	if(!error)
		increment();
	return success;
}

bool dmethod() { //after reading a type and id
	bool success = true;
	bool error = false;
	int temp = 0; //used for error recovery
	if(nextToken().word == "(") {
		increment();
		if(nextToken().word == ")") {
			increment(); 
		}
		else if(isType(nextToken().word)) {
			parameter();
			if(nextToken().word == ")") {
				increment();
			}				
			else {
				cout << "Line " << currentToken().line << ":\t" << "expected delimiter )" << '\n';
				temp = currentToken().line;
				error = true;
			}
		}
		else if(nextToken().name == "identifier") {
			cout << "Line " << currentToken().line << ":\t" << "expected type" << '\n';
			temp = currentToken().line;
			error = true;
		}
		else if (!error) {
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter )" << '\n';
			temp = currentToken().line;
			error = true;
		}
		if(nextToken().word == "{"  && !error) {
			increment();
		}
		else if(!error) {
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter {" << '\n';
			increment();
			error = true;
		}
		if(nextToken().word == "}" && !error) {
			//do nothing
		}
		else if(!error) {
			do {
				success = line();
			} while(nextToken().word != "}" && !isLast());
			if(nextToken().word == "}" && !error) {
				//do nothing //increment();
			}
			else if(!error) {
				cout << "Line " << currentToken().line << ":\t" << "expected delimiter }" << '\n';
				temp = currentToken().line;
				error = true;
			}
		}
	}
	else if(!error) {
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter (" << '\n';
		temp = currentToken().line;
		error = true;
	}
	if(error) {
		errorHandling(temp);
	}
	else if(!error) {
		increment();
	}
	return success;
}

bool parameter() {
	bool success = true;
	bool error = false;
	int temp = 0;	
	do {
		/*if(isType(currentToken().word)) {
			increment();
		}*/
		if(isType(nextToken().word)) {
			increment();
		}
		else { 
			cout << "Line " << currentToken().line << ":" << "\texpected type" << '\n';
			temp = currentToken().line;
			error = true;
		}
		if(nextToken().name == "identifier" && !error) {
			increment();
		}
		else if(!error) {
			cout << "Line " << currentToken().line << ":" << "\texpected identifier" << '\n';
			temp = currentToken().line;
			error = true;
		}
		if((nextToken().word == "," || nextToken().word == ")") && !error) {
			if(nextToken().word == ",") {
				increment();
			}
		}
		else if(!error) {
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter ," << '\n';
			temp = currentToken().line;
			error = true;
		}
	} while(isType(nextToken().word) && !error);
	if(nextToken().name == "identifier" && !error) {
		cout << "Line " << currentToken().line << ":" << "\texpected type" << '\n';
		temp = currentToken().line;
		error = true;
	}
	if(error) {
		while(nextToken().line == temp && nextToken().word != ")") {
			if(increment() == false) {
				success = true;
				break;
			}
		}
	}
	//increment();
	return success;
}

bool line() { //reading lines inside of a function after a "{" was read
	bool success = true;
	bool error = false;
	int temp = 0; //used for error recovery
	if(nextToken().name == "identifier") { //call_function or assign or error
		increment(); //consume identifier
		if(nextToken().word == "=") {
			if(assign()) {}
			else {
				cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
				temp = currentToken().line;
				error = true;
			}
		}
		else if(nextToken().word == "(") {
			success = call_function();
			if(success) {}
			else { 
				temp = currentToken().line;
				error = true;
			}
			if(nextToken().word == ";" && !error) {
				increment();
			}
			else if(success) {
				cout << "Line " << currentToken().line << ":\t" << "expected delimiter ;" << '\n';
			}
			else {
				error = true;
			}
		}
		else if(nextToken().word == "{" || nextToken().word == "}" || 
			nextToken().word == ";" || nextToken().name == "identifier") {
			cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
		}
	}
	else if(nextToken().word == "print" || nextToken().word == "read") { //call_function for "print" and "read"
		increment();
		if(nextToken().word == "(") {
			//index--; //reset to beginning to call call_function()
			success = call_function();
			if(success) {}
				else { 
					temp = currentToken().line;
					error = true;
				}
		}
		if(nextToken().word == ";" && !error) {
			increment(); //consume ";"
		}
		else {
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter ;" << '\n';
			temp = currentToken().line;
			error = true;
		}
	}
	else if(isType(nextToken().word)) {
		dvar_local();
	}
	else if(nextToken().word == "if") {
		success = if_function();
		if(success) {}
		else { 
			temp = currentToken().line;
			error = true;
		}
	}
	else if(nextToken().word == "while") {
		success = while_function();
		if(success) {}
		else { 
			temp = currentToken().line;
			error = true;
		}
	}
	else if(nextToken().word == "return") {
		success = return_function();
		if(success) {}
		else { 
			temp = currentToken().line;
			error = true;
		}
	}
	else if(isLast()) {
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter }" << '\n';
	}
	else if(nextToken().word == "}") { //empty line
		success = true;	
	}
	else {
		cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
	}
	if(error) {
		errorHandling(temp);
	}
	return success;
}

bool dvar_local() {
	bool success = true;
	bool error = false;
	int temp = 0; //used for error recovery
	if(isType(nextToken().word)) {
		increment();
	}
	else {
		cout << "Line " << currentToken().line << ":\t" << "expected type" << '\n';
	}
	do {
		if(nextToken().name == "identifier") {
			increment();
		}
		else {
			cout << "Line " << currentToken().line << ":\t" << "expected identifier" << '\n';	
			temp = currentToken().line;
			error = true;
		}
		while(nextToken().word == "," && !error) {
			increment();
			if(nextToken().name == "identifier") {
				increment();
			}
			else {
				cout << "Line " << currentToken().line << ":\t" << "expected identifier" << '\n';	
				temp = currentToken().line;
				error = true;
			}
		}
		if(nextToken().word == ";" && !error) {
			//do nothing 
		}
		else if(nextToken().word == "=" && !error) {
			increment();
			success = exprlog();
			if(!success || nextToken().word != ";") {
				error = true;
				temp = currentToken().line;
				if(!success) {
					cout << "Line " <<currentToken().line << ":\t" << "expected identifier or value" << '\n';
				}
				else {
					cout << "Line " <<currentToken().line << ":\t" << "expected delimiter ;" << '\n';
				}
			}
		}
		else if (!error) {
			error = true;
			cout << "Line " <<currentToken().line << ":\t" << "expected delimiter ;" << '\n';	
			temp = currentToken().line;
		}
		if(error) {
			errorHandling(temp);
		}
	} while(nextToken().word != ";" && !error);
	if(nextToken().word == ";" && !error) {
		increment();
		success = true;
	}
	return success;
}

bool if_function() {
	bool success = true;
	if(nextToken().word == "if") {
		increment();
	}
	else {
		success = false;
		cout << "Line " << currentToken().line << ":\t" << "expected identifier" << '\n';
	}
	if(nextToken().word == "(" && success) {
		increment();
		success = exprlog();
		if(success) {
			//increment();
		}
		else if (success) {
			cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
		}
	}
	else { 
		success = false;
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter (" << '\n';
	}
	if(nextToken().word == ")" && success) {
		increment();
	}
	else {
		success = false;
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter )" << '\n';
	}
	if(nextToken().word == "{" && success) { //first curly braces
		increment();
		do {
			success = line();
		} while(nextToken().word != "}" && !isLast() && success);
	}
	if(nextToken().word == "}") {
		increment();
	}
	else if(success) {
		success = line();
	}
	if(nextToken().word == "else" && success) {
		increment();
		if(nextToken().word == "{" && success) { //first curly braces
			increment();
			do {
				success = line();
			} while(nextToken().word != "}" && !isLast() && success);	
		}
		if(nextToken().word == "}") {
			increment();
		}
		else if(success) {
			success = line(); //top line on diagram
		}
	}
	//increment();
	return success;
}

bool while_function() {
	bool success = true;
	if(nextToken().word == "while") {
		increment();
		if(nextToken().word == "(") {
			increment();
			success = exprlog();
			if(success) {
				if(nextToken().word == ")") {
					success = true; //not needed, but easier to see what's happening
					increment(); //consume ")"
				}
				else if(nextToken().word != ")") {
					cout << "Line " << currentToken().line << ":\t" << "expected delimiter )" << '\n';
					success = false;
				}
			}
			else {
				cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
			}
		}
		else { 
			success = false;
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter (" << '\n';
		}
		if(nextToken().word == "{" && success) { //first curly braces
			increment();
			do {
				success = line();
			} while(nextToken().word != "}" && !isLast() && success);
		}
		if(nextToken().word == "}" && success) {
			increment();
		}
		else if(success) {
			success = line();
		}
	}
	return success;
}

bool assign() {
	bool success = false;
	if(nextToken().word == "=") {
		increment();
		success = exprlog();
	}
	if(nextToken().word == ";" && success) {
		increment(); //consume ;
	}
	else if(success) { //only check for delimiter if there are no errors
		cout << "Line " << currentToken().line << ":" << "\texpected delimiter ;" << '\n';
	}
	else if(!success) {
		//do nothing, line() will take care of error
	}
	else {
		success = false;
	}
	return success;
}

bool call_function() { //after having read "identifier", "print", or "read" (sitting at this index)
	bool success = false;
	if(nextToken().word == "(") { 
		increment(); //consume "("
		success = true;
	}
	else {
		success = false;
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter (" << '\n';
	}
	if(nextToken().word == ")" && success) {
		success = true;
		increment(); //consume ")"
	}
	else if(!success) {
		success = false;
		cout << "Line " << currentToken().line << ":\t" << "expected delimiter )" << '\n';
	}
	else {
		do {
			if(exprlog() && success) {
				success = true;
				//increment(); //consume valid exprlog, sitting on exprlog
			}
			else {
				success = false;
			}
			do {
				if(nextToken().word == "," && success) {
					increment(); //consume comma
					if(exprlog()) {
						success = true;
						//increment(); //consume valid exprlog
					}
					else {
						success = false;
					}
				}
			} while(nextToken().word != ")" && success);
		} while(nextToken().word != ")" && success);
		if(!success) {
			cout << "Line " << currentToken().line << ":\t" << "expected identifier or value" << '\n';
		}
		else if(nextToken().word == ")") {
			increment();
		}
	}
	return success;
}

bool return_function() {
	bool success = false;
	if(nextToken().word == "return") { 
		increment();
		success = true;
	}
	if(nextToken().word == ";") { 
		increment(); //consume ";"
		success = true;
	}
	else {
		success = exprlog();
		if(nextToken().word == ";") {
			increment();
		}
		else {
			success = false;
			cout << "Line " << currentToken().line << ":\t" << "expected delimiter ;" << '\n';
		}
	}
	return success;
}

bool exprlog() { //after reading "=" (if calling assign)
	bool success = false;
	if(opand()) {
		if(nextToken().word == "|") {
			increment();
			success = exprlog(); //recursive call
		}
		else {
			success = true;
		}
	}
	return success;
}

bool opand() {
	bool success = false;
	if(opno()) {
		if(nextToken().word == "&") {
			increment();
			success = opand(); //recursive call
		}
		else {
			success = true;
		}
	}
	return success;
}

bool opno() {
	bool success = false;
	if(nextToken().word == "!") {
		increment();
		success = exprel();
	}
	else {
		success = exprel();
	}
	return success;
}

bool exprel() {
	bool success = false;
	if(expr()) {
		if(nextToken().word == ">" || nextToken().word == "<") {
			increment();
			success = exprel(); //recursive call
		}
		else {
			success = true;
		}
	}
	else {
		success = false;
	}
	return success;
}

bool expr() {
	bool success = false;
	if(product()) {
		if(nextToken().word == "+" || nextToken().word == "-") {
			increment();
			success = expr(); //recursive call
		}
		else {
			success = true;
		}
	}
	else {
		success = false;
	}
	return success;
}

bool product() {
	bool success = false;
	if(sign()) {
		if(nextToken().word == "/" || nextToken().word == "*") {
			increment();
			success = product(); //recursive call
		}
		else {
			success = true;
		}
	}
	else {
		success = false;
	}
	return success;
}

bool sign() {
	bool success = false;
	if(nextToken().word == "-") {
		increment();
		success = term();
	}
	else {
		success = term();
	}
	return success;
}

bool term() { //still need to add a couple functions
	bool success = false;
	if(nextToken().name == "character" || nextToken().name == "integer" || 
		nextToken().name == "float" || nextToken().name == "identifier" || 
		nextToken().name == "string" || nextToken().name == "hexadecimal" ||
		nextToken().name == "octal") {
		success = true;
		if(nextToken().name == "identifier") { //call_function
			increment(); //consume identifier
		if(nextToken().word == "(") {
			success = call_function();
			index--; //must step back
		}
		else {
			index--;
		}
		}
	}
	else if(nextToken().word == "true" || nextToken().word == "false") {
		success = true;
	}
	else if(nextToken().word == "(") {
		increment();
		success = exprlog();
		if(nextToken().word == ")" && success) { //added the second condition
			success = true;
		}
		else {
			success = false;
		}
	}
	if(success) {
		increment(); //consume valid term
	}
	return success;
}