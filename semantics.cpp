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
    
    bool typeCheck(string left)
    {
        //cout << "##"  << left << endl;
        int firstType, secondType;
        int result = 0;
        if(Stack.size() > 1)
        {
        string first = Stack.top();
        string final;
        Stack.pop();
        
        if(first =="INTEGER")
            firstType = 1;
        else if( first == "FLOAT" )
            firstType = 2;
        else if(first =="CHAR")
            firstType = 3;
        else if(first =="STRING")
            firstType = 4;
        else if(first == "BOOLEAN")
            firstType = 5;
        else
            return false;
        while(!Stack.empty())
        {
        if(Stack.top() == "+")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;

            result = c->cube[OP_PLUS][firstType][secondType];
            firstType = result;
        }
        
        else if(Stack.top() == "-")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_MINUS][firstType][secondType];
            
            firstType = result;
        }
        
        else if(Stack.top() == "*")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_MULT][firstType][secondType];
            
            firstType = result;
        }
        
        else if(Stack.top() == "/")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
        
            result = c->cube[OP_DIV][firstType][secondType];
            
            firstType = result;
        }

        else if(Stack.top() == "/")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_MULT][firstType][secondType];
            
            firstType = result;
        }

        else if(Stack.top() == ">")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_GREATER][firstType][secondType];
            
            firstType = result;
        }
        
        else if(Stack.top() == "<")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_LESS][firstType][secondType];
            
            firstType = result;
        }
        
        else if(Stack.top() == "&")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_AND][firstType][secondType];
            
            firstType = result;
        }


        else if(Stack.top() == "|")
        {
            Stack.pop();
            string second = Stack.top();
            if(second =="INTEGER")
                secondType = 1;
            else if( second == "FLOAT" )
                secondType = 2;
            else if(second =="CHAR")
                secondType = 3;
            else if(second =="STRING")
                secondType= 4;
            else if(second == "BOOLEAN")
                secondType = 5;
            else
                return false;
            
            result = c->cube[OP_OR][firstType][secondType];
            
            firstType = result;
        }
        
    
        Stack.pop();
        
        }
        if(result ==1)
            final = "INTEGER";
        else if( result == 2)
            final = "FLOAT" ;
        else if(result ==3)
            final = "CHAR";
        else if(result ==4)
            final = "STRING";
        else if(result == 5)
            final = 5;
        else
            return false;
        
        if(final == left)
            return true;
        
        return false;
        }
        else
        {
            if(Stack.top() == left)
            {
                Stack.pop();
                return true;
            }
            else
            {
                Stack.pop();
                return false;
            }
    
        }
    }
    
    

};