//Abdulaziz Alwashmi's Lexer
//NEW COMMENT
#include "Header.h"

extern std::vector<Token> tokens;

void init(int argc, char* argv[]){
    //std::cout << "started\n";
	// input file
	std::ifstream fin(argv[1]);

	// variable to store each line of the input:
	std::string line;

	int lineCount= 0;

	// read the input line by line and parse:
	while(std::getline(fin, line)){
		lineCount++;
		if(line.length() > 0){
			split_line(line, lineCount);
		}
		//std::cout << "splitted a line\n";
	}

	//std::ofstream fout(argv[2]);
	//fout << output;
	 
	//std::cout << "Doine!  the output is written\n";
} //END MAIN

/*
signeture: void split_line(std::string)
parameters: line (std::string), line to be parsed
returns: void
*/
void split_line(std::string line, int lineCount){
	Token token;
	// variable to store the words in the line:
	std::string word = "";
	int c = 0;	// count of single qoutes
	int cc = 0;	// count of double qoutes
	//std::cout << line << std::endl;
	
	// loop the line character by character:
	for(int i = 0 ; i <= line.length()-1 ; i++){
		
		// if a qoute is detected, separate and increment the corresponding count:
		if(line[i] == '\'' && cc == 0){
			
			if(c == 0){
				if(word.length() > 0){
					tokens.push_back(lexer(word, lineCount));
					
					word = "";
				}
			}
			
			if(c == 1){
				if(line[i-1] != '\\') c++; // if it is escaped, do not increment count.
			}
			else
				c++;
		}
		
		if(line[i] == '\"' && c == 0){
			
			if(cc == 0){
				if(word.length() > 0){
					tokens.push_back(lexer(word, lineCount));
					
					word = "";
				}
			}
			
			if(cc == 1){
				if(line[i-1] != '\\') cc++;	// if it is escaped, do not increment count.
			}
			else
				cc++;
		}
		
		// if no qoutes are detected:
		if(c == 0 && cc == 0){
			// check is there is a separator:
		 	if(isSeparator(line[i])){
				//std::cout << word << std::endl;
				// call lexer and append to output:
				if(word.length() > 0){
					tokens.push_back(lexer(word, lineCount));
					
				}

				// check if the character is a delimeter:

				if(isDelimiter(line[i])){
					token.type = "DELIMITER";
					token.name = line[i];
					token.line = lineCount;
					tokens.push_back(token);
					
				}
				if(isOperator(line[i])){
					token.type = "OPERATOR"; 
					token.name = line[i];
					token.line = lineCount;
					tokens.push_back(token);
					
				}
				word = "";
			}
			else{
		
				// add the char to the word:
				word += line[i];
			}
		}
		else{
			// if only one qoute is detected:
			if(c == 1 || cc == 1) word += line[i];
			else{	// if the closing qoute is detected:
				word += line[i];	// append it to the word
				
				tokens.push_back(lexer(word, lineCount));
				
				word = "";	// reset the word
				
				// reset the counters:
				c = 0;
				cc = 0;
			}
		}
	}
	if(word.length() > 0){
			tokens.push_back(lexer(word, lineCount));
			
	}
}

/*
signeture: bool isDelimiter(char){
parameters: alpha (char) character to be evaluated
returns: true if the char is a delimiter.
*/
bool isDelimiter(char alpha){

	if((alpha == ';') || (alpha == ',') || (alpha == ':') || (alpha == '\\') || (alpha == '(') || (alpha == ')') || (alpha == '{') || (alpha == '}') || (alpha == '[') || (alpha == ']') || (alpha == '?'))
		return true;
	else
		return false;
}

/*
signeture: bool isOperator(char){
parameters: alpha (char) character to be evaluated
returns: true if the char is an operator.
*/
bool isOperator(char alpha){

	if((alpha == '=') || (alpha == '+') || (alpha == '-') || (alpha == '*') || (alpha == '/') || (alpha == '%') || (alpha == '!') || (alpha == '<') || (alpha == '>') || (alpha == '|') || (alpha == '&') || (alpha == '~') || (alpha == '^')|| (alpha == '&'))
		return true;
	else
		return false;
}

/*
signeture: bool isSeparator(char){
parameters: alpha (char) character to be evaluated
returns: true if the char is a sparator(delimiter, operator, or space).
*/
bool isSeparator(char alpha){

	if((isDelimiter(alpha)) || (isOperator(alpha)) || (alpha == ' ') || (alpha == '\t'))
		return true;
	else
		return false;
}

/*
signeture: bool isKeyword(std::string word){
parameters: word (std::string) word to be evaluated
returns: true if the string is a keyword(if, else, while, return, ...).
*/
bool isKeyword(std::string word){

        if((word == "if") || (word == "else") || (word == "while") || (word == "return") || (word == "int") || (word == "float") || (word == "void") || (word == "char") || (word == "string") || (word == "boolean") || (word == "for")
	  ||(word == "read") || (word == "print") )
                return true;
        else
                return false;
}

Token lexer(std::string word, int lineCount){
	Token token;
	// if the word is a keyword, return keyword.
	if(isKeyword(word)){
		token.type = "KEYWORD";
		token.name= word;
		token.line = lineCount;
		return token;
	}

	// begin DFA:
	int state = 0;
	
	for(int i = 0 ; i < word.length() ; i++){
		
		state = calculateNextState(state, word[i]);
	}
	
	switch(state){
		
		case 1:
			token.type = "INTEGER";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 2:
			token.type = "OCTAL";
			token.name = word;
			token.line = lineCount;
			return token;
	
			break;
		case 4:
			token.type = "HEXADECIMAL";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 5:
			token.type = "FLOAT";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 6:
			token.type = "INTEGER";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 10:
			token.type = "STRING";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 13:
			token.type = "CHAR";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		case 14:
			token.type = "IDENTIFIER";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
		default:
			token.type = "UNDEFINED";
			token.name = word;
			token.line = lineCount;
			return token;
			
			break;
	}
}

int calculateNextState(int state, char input){
	
		switch(state){
		
		case 0:
			if(input == '0') return 1;
			else if(input >= '1' && input <= '9') return 6;
			else if(input == '\"') return 8;
			else if(input == '\'') return 11;
			else if(input == '$' || input == '_' || (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) return 14;
			else return -1;
			break;
		case 1:
			if(input >= '0' && input <= '7') return 2;
			else if(input == 'x' || input == 'X') return 3;
			else if(input == '.') return 7;
			else return -1;
			break;
		case 2:
			if(input >= '0' && input <= '7') return 2;
			else return -1;
			break;
		case 3:
			if((input >= '0' && input <= '9') || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F')) return 4;
			else return -1;
			break;
		case 4:
			if((input >= '0' && input <= '9') || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F')) return 4;
			else return -1;
			break;
		case 5:
			if(input >= '0' && input <= '9') return 5;
			else return -1;
			break;
		case 6:
			if(input >= '0' && input <= '9') return 6;
			else if(input == '.') return 7;
			else return -1;
			break;
		case 7:
			if(input >= '0' && input <= '9') return 5;
			else return -1;
			break;
		case 8:
			if(input == '\\') return 16;
			else if(input == '\"') return 10;
			else return 9;
			break;
		case 9:
			if(input == '\"') return 10;
			else if(input == '\\') return 16;
			else return 9;
			break;
		case 10:
			return -1;
			break;
		case 11:
			if(input == '\\') return 15;
			else return 12;
			break;
		case 12:
			if(input == '\'') return 13;
			else return -1;
			break;
		case 13:
			return -1;
			break;
		case 14:
			if(input == '$' || input == '_' || (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || (input >= '0' && input <= '9')) return 14;
			else -1;
			break;
		case 15:
			return 12;
			break;
		case 16:
			return 9;
			break;
		default:
			return -1;
			break;
		}
    return -1;
}

////tests////
/*
		// check for single qoutes:
		if(line[i] = '\''){
			if(c == 0){
				if(word.length() > 0){
					output += lexer(word);
					output += "\n";
				}
				c++;
				word = line[i];	//word = '
			}
			if(c == 1){
				word += line[i];
				if(word.length() > 0){
					output += lexer(word);
					output += "\n";
				}
				c = 0;
				word = "";
			}
		}
		
		// check for double qoutes:
		else if(line[i] = '\"'){
			if(cc == 0){
				if(word.length() > 0){
					output += lexer(word);
					output += "\n";
				}
				cc++;
				word = line[i];	//word = '
			}
			if(cc == 1){
				word += line[i];
				if(word.length() > 0){
					output += lexer(word);
					output += "\n";
				}
				cc = 0;
				word = "";
			}
		}
		
		// if a qoute is open, keep appending:
		if(c == 1 || cc == 1){
			word += line[i];
		}
		
		// otherwise, check if the character is a separator:
		else*/
