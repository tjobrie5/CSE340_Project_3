// Using Lexer from 
// Using Parser from Mark Ahlemeier


#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;


//Create Symbol Table class
class SymbolTable {

	//Create a Hash Table for Symbol Table ST
    unordered_map<string, vector<string>> ST;

public:
    SymbolTable()
    {
        
    }
	void insert(string name, string type, string scope)
    {
        vector<string> v;
        v.push_back(type);
        v.push_back(scope);
        ST.insert({name,v});
    }
    
    bool search(string name)
    {
        unordered_map<string, vector<string>>::const_iterator found = ST.find(name);
        if(found == ST.end())
            return false;
        else
            return true;
        
    }
    
    void print(string name)
    {
        vector<string> v;
        v = ST[name];
        cout << v[0];
        cout << v[1];
        
    }
};
