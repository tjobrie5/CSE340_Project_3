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
        vector<string> v;
        unordered_map<string, vector<string>>::const_iterator found = ST.find(name);
        
        v = found->second;
        for(int i = 1; i <v.size(); i = i+2)
        {
            if(v[i] == scope)
                return v[i-1];
        }
        
        return "";
    }
    
    //possible getScope function later
    
    void print(string name)
    {
        vector<string> v;
        v = ST[name];
        cout << v[0];
        cout << v[1];
        
    }
};
