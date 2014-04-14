#include "symboltable.cpp"
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

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
        
        //string leftType;
        
        transform(left.begin(), left.end(), left.begin(), ::toupper);
        //cout << "LEFTTYPE " << leftType << endl
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
        {
            while(!Stack.empty())
                Stack.pop();
            return false;
        }
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }
            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

        
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }
            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

            
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
            {
                while(!Stack.empty())
                    Stack.pop();
                return false;
            }

            
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
        {
            while(!Stack.empty())
                Stack.pop();
            return false;
        }

        
        if(final == left)
            return true;
        else
        {
            while(!Stack.empty())
                Stack.pop();
            return false;
        }

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
    
bool boolCheck()
    {
        
        int firstType;
        int secondType;
        int result=0;
        if(Stack.size() == 1)
        {
            if(Stack.top() == "BOOLEAN")
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
        else if(Stack.size()== 2)
        {
            if(Stack.top() == "BOOLEAN")
            {
                Stack.pop();
                if(Stack.top() == "!")
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
            else
            {
                Stack.pop();
                Stack.pop();
                return false;
            }
        }
        
       else
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
           {
               while(!Stack.empty())
                   Stack.pop();
               return false;
           }
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
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
                   {
                       while(!Stack.empty())
                           Stack.pop();
                       return false;
                   }
                   
                   
                   result = c->cube[OP_OR][firstType][secondType];
                   
                   firstType = result;
               }
               
               
               Stack.pop();
               
           }
           
           if (result == 5)
           {
               return true;
           }
           else
           {
               while(!Stack.empty())
                   Stack.pop();
               return false;
           }

   
       }//else
        return false;
    }//bool
    
    bool checkParams(string name)
    {
        string temp="";
        string params;
        int i;
    
        
            for (i = 0; i < name.size() && name[i] !='-';++i)
            {
                temp += name[i];
            }
        
        for(int j = i+1; j<name.size()&& name[j] != '-'; ++j)
        {
            params += name[j];
        }
        
        if(params == "int")
        {
            string temp1 = temp + "-float";
            unordered_map<string, vector<string>>::const_iterator found = st->ST.find(temp1);
            if(found != st->ST.end())
                return false;
            
            string temp2 = temp + "-string";
            unordered_map<string, vector<string>>::const_iterator found1 = st->ST.find(temp2);
            if(found1 != st->ST.end())
                return false;
            
            string temp3 = temp + "-char";
            unordered_map<string, vector<string>>::const_iterator found2 = st->ST.find(temp3);
            if(found2 != st->ST.end())
                return false;
        }
        
        if(params == "float")
        {
            string temp1 = temp + "-int";
            unordered_map<string, vector<string>>::const_iterator found = st->ST.find(temp1);
            if(found != st->ST.end())
                return false;
            
            string temp2 = temp + "-string";
            unordered_map<string, vector<string>>::const_iterator found1 = st->ST.find(temp2);
            if(found1 != st->ST.end())
                return false;
            
            string temp3 = temp + "-char";
            unordered_map<string, vector<string>>::const_iterator found2 = st->ST.find(temp3);
            if(found2 != st->ST.end())
                return false;
        }
        
        else if(params == "string")
        {
            string temp1 = temp + "-int";
            unordered_map<string, vector<string>>::const_iterator found = st->ST.find(temp1);
            if(found != st->ST.end())
                return false;
            
            string temp2 = temp + "-float";
            unordered_map<string, vector<string>>::const_iterator found1 = st->ST.find(temp2);
            if(found1 != st->ST.end())
                return false;
            
            string temp3 = temp + "-char";
            unordered_map<string, vector<string>>::const_iterator found2 = st->ST.find(temp3);
            if(found2 != st->ST.end())
                return false;
        }
        else if(params == "char")
        {
            string temp1 = temp + "-int";
            unordered_map<string, vector<string>>::const_iterator found = st->ST.find(temp1);
            if(found != st->ST.end())
                return false;
            
            string temp2 = temp + "-float";
            unordered_map<string, vector<string>>::const_iterator found1 = st->ST.find(temp2);
            if(found1 != st->ST.end())
                return false;
            
            string temp3 = temp + "-string";
            unordered_map<string, vector<string>>::const_iterator found2 = st->ST.find(temp3);
            if(found2 != st->ST.end())
                return false;
        }
        else
            return false;
        
        return true;
        
        
        
        
        
        //loop through temp till
    }
     
};