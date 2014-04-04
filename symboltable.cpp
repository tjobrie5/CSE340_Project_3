// Using Lexer from 
// Using Parser from Mark Ahlemeier


#include "Header.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


//Create Symbol Table class
class SymbolTable() {

	//Create a Hash Table for Symbol Table ST
	typedef unordered_map<string, vector> ST;

public:
	//Insert, search and get functions
	void insert(string, string, string);
	bool search(string);
	bool search(string, scope);
	string getType(string);
	srting getScope(string);

} mytable;
