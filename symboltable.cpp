// Using Lexer from 
// Using Parser from Mark Ahlemeier

nclude "Header.h"


using namespace std;


//Create Symbol Table class
class SymbolTable {

	//Create a Hash Table for Symbol Table ST
    unordered_map<string, vector<string>> ST;

public:
	void insert(string name, string type, string scope)
    {
        vector<string> v;
        v.push_back(type);
        v.push_back(scope);
        ST.insert({name,v});
    }
    
    void search(string name)
    {
        
        
    }
} mytable;

