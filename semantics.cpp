#include "symboltable.cpp"
#include <stack>
#include <string>
#include <vector>

class semantics
{
public:
    stack<string> Stack;
    SymbolTable* st = new SymbolTable();
    Cube* c = new Cube();
    
    semantics()
    {
        
    }
    bool decleration(string name, string scope)
    {
        if(st->search(name,scope))
            return true;
        else
            return false;
    }
    
    bool unicity(string name, string scope)
    {
        
        if(st->search(name,scope))
            return false;
        else
            return true;

    }

};
