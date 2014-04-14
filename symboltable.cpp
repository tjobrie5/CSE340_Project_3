// Using Lexer from 
// Using Parser from Mark Ahlemeier


#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;


//Create Symbol Table class
class SymbolTable {
public:               //my changes
	//Create a Hash Table for Symbol Table ST
    unordered_map<string, vector<string>> ST;

public:
    SymbolTable()
    {
        
    }
	void insert(string name, string type, string scope)
    {
        
        vector<string> temp;
        if(search(name))
        {
            temp = ST[name];
            temp.push_back(type);
            temp.push_back(scope);
            
            ST[name] = temp;
            
        }
        else
        {
            temp.push_back(type);
            temp.push_back(scope);
            ST.insert({name,temp});
        }
    }
    
    bool search(string name)
    {
        if(!ST.empty())
        {
            unordered_map<string, vector<string>>::const_iterator found = ST.find(name);
            if(found == ST.end())
                return false;
            else
                return true;
        }
        else
            return false;
    }
    
    bool search(string name, string scope)
    {
        if(!ST.empty())
        {
            vector<string> v;
            unordered_map<string, vector<string>>::const_iterator found = ST.find(name);
        
            if(found == ST.end())
                return false;
            
            else
            {
                v = found->second;
                for(int i=1; i<v.size(); i=i+2)
                {
                    
                    if(v[i] == scope)
                    {
                        return true;
                    }
                }
                return false;
            }
        }
        
        return false;
        
        
    }
    
    string getType(string name, string scope)
    {
        string n, s;
        n = name;
        s = scope;
        vector<string> v;
        unordered_map<string, vector<string>>::const_iterator found = ST.find(n);
        
        v = found->second;
        for(int i = 1; i <v.size(); i = i+2)
        {
            if(v[i] == s)
                return v[i-1];
        }
        
        return "";
    }
    
    //possible getScope function later
    
    void print()
    {
        cout << "----------------------------" << endl;
        vector<string> v;
        for ( auto it = ST.begin(); it != ST.end(); ++it )
        {
            cout << " " << it->first << " ";
            v = it->second;
            for(int i=0; i<v.size(); ++i)
            {
                cout << v[i];
                if(i%2 == 1)
                    cout << "::";
            }
            cout << endl;
        }
    }
};

#define OP_PLUS 1
#define OP_MINUS 2
#define OP_MULT 3
#define OP_DIV 4
#define OP_MINUS_U 5
#define OP_GREATER 6
#define OP_LESS 7
#define OP_NO 8
#define OP_AND 9
#define OP_OR 10

#define INTEGEr 1
#define FlOAt 2
#define CHAr 3
#define STRINg 4
#define BOOl 5
#define VOId 6


class Cube {
public:
	int cube[11][7][7];
public:
    
	Cube() {
        //plus
		cube[1][1][1] = { 1 };
		cube[OP_PLUS][INTEGEr][FlOAt] = FlOAt;
		cube[OP_PLUS][INTEGEr][CHAr] = 0;
		cube[OP_PLUS][INTEGEr][STRINg] = STRINg;
		cube[OP_PLUS][INTEGEr][BOOl] = 0;
		cube[OP_PLUS][INTEGEr][VOId] = 0;
		cube[OP_PLUS][FlOAt][INTEGEr] = FlOAt;
		cube[OP_PLUS][FlOAt][FlOAt] = FlOAt;
		cube[OP_PLUS][FlOAt][CHAr] = 0;
		cube[OP_PLUS][FlOAt][STRINg] = STRINg;
		cube[OP_PLUS][FlOAt][BOOl] = 0;
		cube[OP_PLUS][FlOAt][VOId] = 0;
		cube[OP_PLUS][CHAr][INTEGEr] = 0;
		cube[OP_PLUS][CHAr][FlOAt] = 0;
		cube[OP_PLUS][CHAr][CHAr] = 0;
		cube[OP_PLUS][CHAr][STRINg] = STRINg;
		cube[OP_PLUS][CHAr][BOOl] = 0;
		cube[OP_PLUS][CHAr][VOId] = 0;
		cube[OP_PLUS][STRINg][INTEGEr] = STRINg;
		cube[OP_PLUS][STRINg][FlOAt] = STRINg;
		cube[OP_PLUS][STRINg][CHAr] = STRINg;
		cube[OP_PLUS][STRINg][STRINg] = STRINg;
		cube[OP_PLUS][STRINg][BOOl] = STRINg;
		cube[OP_PLUS][STRINg][VOId] = 0;
		cube[OP_PLUS][BOOl][INTEGEr] = 0;
		cube[OP_PLUS][BOOl][FlOAt] = 0;
		cube[OP_PLUS][BOOl][CHAr] = 0;
		cube[OP_PLUS][BOOl][STRINg] = STRINg;
		cube[OP_PLUS][BOOl][BOOl] = 0;
		cube[OP_PLUS][BOOl][VOId] = 0;
		cube[OP_PLUS][VOId][INTEGEr] = 0;
		cube[OP_PLUS][VOId][FlOAt] = 0;
		cube[OP_PLUS][VOId][CHAr] = 0;
		cube[OP_PLUS][VOId][STRINg] = 0;
		cube[OP_PLUS][VOId][BOOl] = 0;
		cube[OP_PLUS][VOId][VOId] = 0;
        
        
        
		//minus
        
		cube[OP_MINUS][INTEGEr][INTEGEr] = INTEGEr;
		cube[OP_MINUS][INTEGEr][FlOAt] = FlOAt;
		cube[OP_MINUS][INTEGEr][CHAr] = 0;
		cube[OP_MINUS][INTEGEr][STRINg] = 0;
		cube[OP_MINUS][INTEGEr][BOOl] = 0;
		cube[OP_MINUS][INTEGEr][VOId] = 0;
		cube[OP_MINUS][FlOAt][INTEGEr] = FlOAt;
		cube[OP_MINUS][FlOAt][FlOAt] = FlOAt;
		cube[OP_MINUS][FlOAt][CHAr] = 0;
		cube[OP_MINUS][FlOAt][STRINg] = 0;
		cube[OP_MINUS][FlOAt][BOOl] = 0;
		cube[OP_MINUS][FlOAt][VOId] = 0;
		cube[OP_MINUS][CHAr][INTEGEr] = 0;
		cube[OP_MINUS][CHAr][FlOAt] = 0;
		cube[OP_MINUS][CHAr][CHAr] = 0;
		cube[OP_MINUS][CHAr][STRINg] = 0;
		cube[OP_MINUS][CHAr][BOOl] = 0;
		cube[OP_MINUS][CHAr][VOId] = 0;
		cube[OP_MINUS][STRINg][INTEGEr] = 0;
		cube[OP_MINUS][STRINg][FlOAt] = 0;
		cube[OP_MINUS][STRINg][CHAr] = 0;
		cube[OP_MINUS][STRINg][STRINg] = 0;
		cube[OP_MINUS][STRINg][BOOl] = 0;
		cube[OP_MINUS][STRINg][VOId] = 0;
		cube[OP_MINUS][BOOl][INTEGEr] = 0;
		cube[OP_MINUS][BOOl][FlOAt] = 0;
		cube[OP_MINUS][BOOl][CHAr] = 0;
		cube[OP_MINUS][BOOl][STRINg] = 0;
		cube[OP_MINUS][BOOl][BOOl] = 0;
		cube[OP_MINUS][BOOl][VOId] = 0;
		cube[OP_MINUS][VOId][INTEGEr] = 0;
		cube[OP_MINUS][VOId][FlOAt] = 0;
		cube[OP_MINUS][VOId][CHAr] = 0;
		cube[OP_MINUS][VOId][STRINg] = 0;
		cube[OP_MINUS][VOId][BOOl] = 0;
		cube[OP_MINUS][VOId][VOId] = 0;
        
        
        
		//Multiplication
        
		cube[OP_MULT][INTEGEr][INTEGEr] = INTEGEr;
		cube[OP_MULT][INTEGEr][FlOAt] = FlOAt;
		cube[OP_MULT][INTEGEr][CHAr] = 0;
		cube[OP_MULT][INTEGEr][STRINg] = 0;
		cube[OP_MULT][INTEGEr][BOOl] = 0;
		cube[OP_MULT][INTEGEr][VOId] = 0;
		cube[OP_MULT][FlOAt][INTEGEr] = FlOAt;
		cube[OP_MULT][FlOAt][FlOAt] = FlOAt;
		cube[OP_MULT][FlOAt][CHAr] = 0;
		cube[OP_MULT][FlOAt][STRINg] = 0;
		cube[OP_MULT][FlOAt][BOOl] = 0;
		cube[OP_MULT][FlOAt][VOId] = 0;
		cube[OP_MULT][CHAr][INTEGEr] = 0;
		cube[OP_MULT][CHAr][FlOAt] = 0;
		cube[OP_MULT][CHAr][CHAr] = 0;
		cube[OP_MULT][CHAr][STRINg] = 0;
		cube[OP_MULT][CHAr][BOOl] = 0;
		cube[OP_MULT][CHAr][VOId] = 0;
		cube[OP_MULT][STRINg][INTEGEr] = 0;
		cube[OP_MULT][STRINg][FlOAt] = 0;
		cube[OP_MULT][STRINg][CHAr] = 0;
		cube[OP_MULT][STRINg][STRINg] = 0;
		cube[OP_MULT][STRINg][BOOl] = 0;
		cube[OP_MULT][STRINg][VOId] = 0;
		cube[OP_MULT][BOOl][INTEGEr] = 0;
		cube[OP_MULT][BOOl][FlOAt] = 0;
		cube[OP_MULT][BOOl][CHAr] = 0;
		cube[OP_MULT][BOOl][STRINg] = 0;
		cube[OP_MULT][BOOl][BOOl] = 0;
		cube[OP_MULT][BOOl][VOId] = 0;
		cube[OP_MULT][VOId][INTEGEr] = 0;
		cube[OP_MULT][VOId][FlOAt] = 0;
		cube[OP_MULT][VOId][CHAr] = 0;
		cube[OP_MULT][VOId][STRINg] = 0;
		cube[OP_MULT][VOId][BOOl] = 0;
		cube[OP_MULT][VOId][VOId] = 0;
        
        
        
		//division
        
		cube[OP_DIV][INTEGEr][INTEGEr] = INTEGEr;
		cube[OP_DIV][INTEGEr][FlOAt] = FlOAt;
		cube[OP_DIV][INTEGEr][CHAr] = 0;
		cube[OP_DIV][INTEGEr][STRINg] = 0;
		cube[OP_DIV][INTEGEr][BOOl] = 0;
		cube[OP_DIV][INTEGEr][VOId] = 0;
		cube[OP_DIV][FlOAt][INTEGEr] = FlOAt;
		cube[OP_DIV][FlOAt][FlOAt] = FlOAt;
		cube[OP_DIV][FlOAt][CHAr] = 0;
		cube[OP_DIV][FlOAt][STRINg] = 0;
		cube[OP_DIV][FlOAt][BOOl] = 0;
		cube[OP_DIV][FlOAt][VOId] = 0;
		cube[OP_DIV][CHAr][INTEGEr] = 0;
		cube[OP_DIV][CHAr][FlOAt] = 0;
		cube[OP_DIV][CHAr][CHAr] = 0;
		cube[OP_DIV][CHAr][STRINg] = 0;
		cube[OP_DIV][CHAr][BOOl] = 0;
		cube[OP_DIV][CHAr][VOId] = 0;
		cube[OP_DIV][STRINg][INTEGEr] = 0;
		cube[OP_DIV][STRINg][FlOAt] = 0;
		cube[OP_DIV][STRINg][CHAr] = 0;
		cube[OP_DIV][STRINg][STRINg] = 0;
		cube[OP_DIV][STRINg][BOOl] = 0;
		cube[OP_DIV][STRINg][VOId] = 0;
		cube[OP_DIV][BOOl][INTEGEr] = 0;
		cube[OP_DIV][BOOl][FlOAt] = 0;
		cube[OP_DIV][BOOl][CHAr] = 0;
		cube[OP_DIV][BOOl][STRINg] = 0;
		cube[OP_DIV][BOOl][BOOl] = 0;
		cube[OP_DIV][BOOl][VOId] = 0;
		cube[OP_DIV][VOId][INTEGEr] = 0;
		cube[OP_DIV][VOId][FlOAt] = 0;
		cube[OP_DIV][VOId][CHAr] = 0;
		cube[OP_DIV][VOId][STRINg] = 0;
		cube[OP_DIV][VOId][BOOl] = 0;
		cube[OP_DIV][VOId][VOId] = 0;
        
        
        
		//minus Unary
        
		cube[OP_MINUS_U][INTEGEr][0] = INTEGEr;
		cube[OP_MINUS_U][INTEGEr][0] = FlOAt;
		cube[OP_MINUS_U][INTEGEr][0] = 0;
		cube[OP_MINUS_U][INTEGEr][0] = 0;
		cube[OP_MINUS_U][INTEGEr][0] = 0;
		cube[OP_MINUS_U][INTEGEr][0] = 0;
        
        
		//CONSTRUCT CUBE OF TYPES FOR 'GREATER THAN' OPERATION
		cube[OP_GREATER][INTEGEr][INTEGEr] = BOOl;
		cube[OP_GREATER][INTEGEr][FlOAt] = BOOl;
		cube[OP_GREATER][INTEGEr][CHAr] = 0;
		cube[OP_GREATER][INTEGEr][STRINg] = 0;
		cube[OP_GREATER][INTEGEr][BOOl] = 0;
		cube[OP_GREATER][INTEGEr][VOId] = 0;
		cube[OP_GREATER][FlOAt][INTEGEr] = BOOl;
		cube[OP_GREATER][FlOAt][FlOAt] = BOOl;
		cube[OP_GREATER][FlOAt][CHAr] = 0;
		cube[OP_GREATER][FlOAt][STRINg] = 0;
		cube[OP_GREATER][FlOAt][BOOl] = 0;
		cube[OP_GREATER][FlOAt][VOId] = 0;
		cube[OP_GREATER][CHAr][INTEGEr] = 0;
		cube[OP_GREATER][CHAr][FlOAt] = 0;
		cube[OP_GREATER][CHAr][CHAr] = 0;
		cube[OP_GREATER][CHAr][STRINg] = 0;
		cube[OP_GREATER][CHAr][BOOl] = 0;
		cube[OP_GREATER][CHAr][VOId] = 0;
		cube[OP_GREATER][STRINg][INTEGEr] = 0;
		cube[OP_GREATER][STRINg][FlOAt] = 0;
		cube[OP_GREATER][STRINg][CHAr] = 0;
		cube[OP_GREATER][STRINg][STRINg] = 0;
		cube[OP_GREATER][STRINg][BOOl] = 0;
		cube[OP_GREATER][STRINg][VOId] = 0;
		cube[OP_GREATER][BOOl][INTEGEr] = 0;
		cube[OP_GREATER][BOOl][FlOAt] = 0;
		cube[OP_GREATER][BOOl][CHAr] = 0;
		cube[OP_GREATER][BOOl][STRINg] = 0;
		cube[OP_GREATER][BOOl][BOOl] = 0;
		cube[OP_GREATER][BOOl][VOId] = 0;
		cube[OP_GREATER][VOId][INTEGEr] = 0;
		cube[OP_GREATER][VOId][FlOAt] = 0;
		cube[OP_GREATER][VOId][CHAr] = 0;
		cube[OP_GREATER][VOId][STRINg] = 0;
		cube[OP_GREATER][VOId][BOOl] = 0;
		cube[OP_GREATER][VOId][VOId] = 0;
        
        
		//CONSTRUCT CUBE OF TYPES FOR 'LESS THAN' OPERATION
		cube[OP_LESS][INTEGEr][INTEGEr] = BOOl;
		cube[OP_LESS][INTEGEr][FlOAt] = BOOl;
		cube[OP_LESS][INTEGEr][CHAr] = 0;
		cube[OP_LESS][INTEGEr][STRINg] = 0;
		cube[OP_LESS][INTEGEr][BOOl] = 0;
		cube[OP_LESS][INTEGEr][VOId] = 0;
		cube[OP_LESS][FlOAt][INTEGEr] = BOOl;
		cube[OP_LESS][FlOAt][FlOAt] = BOOl;
		cube[OP_LESS][FlOAt][CHAr] = 0;
		cube[OP_LESS][FlOAt][STRINg] = 0;
		cube[OP_LESS][FlOAt][BOOl] = 0;
		cube[OP_LESS][FlOAt][VOId] = 0;
		cube[OP_LESS][CHAr][INTEGEr] = 0;
		cube[OP_LESS][CHAr][FlOAt] = 0;
		cube[OP_LESS][CHAr][CHAr] = 0;
		cube[OP_LESS][CHAr][STRINg] = 0;
		cube[OP_LESS][CHAr][BOOl] = 0;
		cube[OP_LESS][CHAr][VOId] = 0;
		cube[OP_LESS][STRINg][INTEGEr] = 0;
		cube[OP_LESS][STRINg][FlOAt] = 0;
		cube[OP_LESS][STRINg][CHAr] = 0;
		cube[OP_LESS][STRINg][STRINg] = 0;
		cube[OP_LESS][STRINg][BOOl] = 0;
		cube[OP_LESS][STRINg][VOId] = 0;
		cube[OP_LESS][BOOl][INTEGEr] = 0;
		cube[OP_LESS][BOOl][FlOAt] = 0;
		cube[OP_LESS][BOOl][CHAr] = 0;
		cube[OP_LESS][BOOl][STRINg] = 0;
		cube[OP_LESS][BOOl][BOOl] = 0;
		cube[OP_LESS][BOOl][VOId] = 0;
		cube[OP_LESS][VOId][INTEGEr] = 0;
		cube[OP_LESS][VOId][FlOAt] = 0;
		cube[OP_LESS][VOId][CHAr] = 0;
		cube[OP_LESS][VOId][STRINg] = 0;
		cube[OP_LESS][VOId][BOOl] = 0;
		cube[OP_LESS][VOId][VOId] = 0;
        
        
		//CONSTRUCT 'NOT' OPERATION
		cube[OP_NO][INTEGEr][0] = 0;
		cube[OP_NO][FlOAt][0] = 0;
		cube[OP_NO][CHAr][0] = 0;
		cube[OP_NO][STRINg][0] = 0;
		cube[OP_NO][BOOl][0] = BOOl;
		cube[OP_NO][VOId][0] = 0;
        
        
		//CONSTRUCT 'AND' OPERATION
		cube[OP_AND][INTEGEr][INTEGEr] = 0;
		cube[OP_AND][INTEGEr][FlOAt] = 0;
		cube[OP_AND][INTEGEr][CHAr] = 0;
		cube[OP_AND][INTEGEr][STRINg] = 0;
		cube[OP_AND][INTEGEr][BOOl] = 0;
		cube[OP_AND][INTEGEr][VOId] = 0;
		cube[OP_AND][FlOAt][INTEGEr] = 0;
		cube[OP_AND][FlOAt][FlOAt] = 0;
		cube[OP_AND][FlOAt][CHAr] = 0;
		cube[OP_AND][FlOAt][STRINg] = 0;
		cube[OP_AND][FlOAt][BOOl] = 0;
		cube[OP_AND][FlOAt][VOId] = 0;
		cube[OP_AND][CHAr][INTEGEr] = 0;
		cube[OP_AND][CHAr][FlOAt] = 0;
		cube[OP_AND][CHAr][CHAr] = 0;
		cube[OP_AND][CHAr][STRINg] = 0;
		cube[OP_AND][CHAr][BOOl] = 0;
		cube[OP_AND][CHAr][VOId] = 0;
		cube[OP_AND][STRINg][INTEGEr] = 0;
		cube[OP_AND][STRINg][FlOAt] = 0;
		cube[OP_AND][STRINg][CHAr] = 0;
		cube[OP_AND][STRINg][STRINg] = 0;
		cube[OP_AND][STRINg][BOOl] = 0;
		cube[OP_AND][STRINg][VOId] = 0;
		cube[OP_AND][BOOl][INTEGEr] = 0;
		cube[OP_AND][BOOl][FlOAt] = 0;
		cube[OP_AND][BOOl][CHAr] = 0;
		cube[OP_AND][BOOl][STRINg] = 0;
		cube[OP_AND][BOOl][BOOl] = BOOl;
		cube[OP_AND][BOOl][VOId] = 0;
		cube[OP_AND][VOId][INTEGEr] = 0;
		cube[OP_AND][VOId][FlOAt] = 0;
		cube[OP_AND][VOId][CHAr] = 0;
		cube[OP_AND][VOId][STRINg] = 0;
		cube[OP_AND][VOId][BOOl] = 0;
		cube[OP_AND][VOId][VOId] = 0;
        
        
		//CONSTRUCT 'OR' OPERATION
		cube[OP_OR][INTEGEr][INTEGEr] = 0;
		cube[OP_OR][INTEGEr][FlOAt] = 0;
		cube[OP_OR][INTEGEr][CHAr] = 0;
		cube[OP_OR][INTEGEr][STRINg] = 0;
		cube[OP_OR][INTEGEr][BOOl] = 0;
		cube[OP_OR][INTEGEr][VOId] = 0;
		cube[OP_OR][FlOAt][INTEGEr] = 0;
		cube[OP_OR][FlOAt][FlOAt] = 0;
		cube[OP_OR][FlOAt][CHAr] = 0;
		cube[OP_OR][FlOAt][STRINg] = 0;
		cube[OP_OR][FlOAt][BOOl] = 0;
		cube[OP_OR][FlOAt][VOId] = 0;
		cube[OP_OR][CHAr][INTEGEr] = 0;
		cube[OP_OR][CHAr][FlOAt] = 0;
		cube[OP_OR][CHAr][CHAr] = 0;
		cube[OP_OR][CHAr][STRINg] = 0;
		cube[OP_OR][CHAr][BOOl] = 0;
		cube[OP_OR][CHAr][VOId] = 0;
		cube[OP_OR][STRINg][INTEGEr] = 0;
		cube[OP_OR][STRINg][FlOAt] = 0;
		cube[OP_OR][STRINg][CHAr] = 0;
		cube[OP_OR][STRINg][STRINg] = 0;
		cube[OP_OR][STRINg][BOOl] = 0;
		cube[OP_OR][STRINg][VOId] = 0;
		cube[OP_OR][BOOl][INTEGEr] = 0;
		cube[OP_OR][BOOl][FlOAt] = 0;
		cube[OP_OR][BOOl][CHAr] = 0;
		cube[OP_OR][BOOl][STRINg] = 0;
		cube[OP_OR][BOOl][BOOl] = BOOl;
		cube[OP_OR][BOOl][VOId] = 0;
		cube[OP_OR][VOId][INTEGEr] = 0;
		cube[OP_OR][VOId][FlOAt] = 0;
		cube[OP_OR][VOId][CHAr] = 0;
		cube[OP_OR][VOId][STRINg] = 0;
		cube[OP_OR][VOId][BOOl] = 0;
		cube[OP_OR][VOId][VOId] = 0;
        

	}
    
};
