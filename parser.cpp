// THINGS TO REMEMBER: once more rules are made, I may not need to increment a token for an error
#include "Header.h"
#include "symboltable.cpp"
std::vector<Token> tokens;
std::string output;

int curr; //keeps track of current token

int main(int argc, char* argv[])
{
    /*
    curr = 0;
	init(argc, argv);   //lexical analysis, fills vector with tokens
    
    output = "";
    
    program();
    std::ofstream fout(argv[2]);
    if(output == "")
    {
        std::cout << "Build successful\n";
        output = "Build successful";
        fout << output;
    }
    
    else
    {
        fout << output;
        std::cout << output;
    }
     */
    
	//std::cout << "List of Tokens:\n";
    
    
    SymbolTable* ST;
    ST = new SymbolTable();
    ST->insert("t","test","ttest");
    ST->print("t");
}

bool eol()
{
    if(tokens[curr].line != tokens[curr+1].line)
        return true;
    else
        return false;
}
void backToken()
{
    if(curr != 0)
        curr--;
}
void nextToken()
{
    if(curr != tokens.size()-1)
        curr++;
}

bool eof()
{
    if (curr == tokens.size()-1)
        return true;
    else
        return false;
}


//Rules remember to take out eol should not be needed once all rules implemented
//---------------------------------
void term()
{
    if (tokens[curr].type == "CHAR")
    {
            nextToken();
    }
    else if(tokens[curr].type == "INTEGER")
    {
         

            nextToken();
         

    }
    else if(tokens[curr].type == "FLOAT")
    {
            nextToken();
    }
    else if(tokens[curr].type == "IDENTIFIER")
    {
            nextToken();
        if(tokens[curr].name == "(")
        {
            backToken();
            call_function();
        }
    }
    //Could causer errors, possible implemented wrong might need to check for eol before incrementing after last ")"
    else if(tokens[curr].name == "(")
    {
        nextToken();
        exprlog();
        
        if(tokens[curr].name == ")")
            nextToken();
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected ')' ";
            nextToken();

        }
        
    }
    
    else if (tokens[curr].name == "true")
            nextToken();
    
    else if(tokens[curr].name == "false")
            nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": not valid term\n";
        nextToken();
    }
    
}

void sign()
{
    if (tokens[curr].name == "-")
    {
        nextToken();
        term();
    }
    
    else
        term();
}

void product()
{
    sign();
    while ((tokens[curr].name == "/" || tokens[curr].name == "*" || tokens[curr].name == "%") && !eof())
    {
        nextToken();
        sign();
    }
}

// use for testing unlikely any errors
void expr()
{
    product();
    while((tokens[curr].name == "+" || tokens[curr].name == "-") && !eof())
    {
        nextToken();
        product();
    }
}

void exprel()
{
    expr();
     while((tokens[curr].name == ">" || tokens[curr].name == "<") && curr!= tokens.size()-1) // incase eof() gives problems use: curr!= tokens.size()-1
     {
         nextToken();
         expr();
     }
}

void opno()
{
    if (tokens[curr].name == "!")
    {
        nextToken();
        exprel();
    }
    
    else
        exprel();
}

void opand()
{
    opno();
    while(tokens[curr].name == "&" && !eof())
    {
        nextToken();
        opno();
    }
}
//use for testing --- minimal test performed if errors later on could be root but not likely
void exprlog()
{
    opand();
    while(tokens[curr].name == "|" && !eof())
    {
        nextToken();
        opand();
    }
}

//use for testing ---- Tested unlikely of any errors
void call_function()
{
    if(tokens[curr].type == "IDENTIFIER" || tokens[curr].name == "print" || tokens[curr].name == "read")
    {
        nextToken();
          
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected identifier\n";
        nextToken();
    }
    
    if(tokens[curr].name == "(")
        nextToken();
    
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected open parenthesis\n";
        nextToken();
    }
    
    if(tokens[curr].name != ")")
    {
        do
        {
            if(tokens[curr].name != ",")
            {
                
                exprlog();
                  
            }
            else
                nextToken();
        }
        while (tokens[curr].name != ")" && !eof());
        
        if(tokens[curr].name != ")")
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected close parenthesis\n";
            nextToken();
        }
        
        else
        {
            nextToken();
        }
    }
    else
        nextToken();
    
    if(tokens[curr].name == ";")
    {
        nextToken();
        
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected semi colon\n";
        nextToken();
    }
}

void _return()
{
    if(tokens[curr].name == "return")
    {
        nextToken();
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": missing return\n";
        nextToken();
    }
    
    if(tokens[curr].name != ";")
    {
        exprlog();
        if(tokens[curr].name == ";")
            nextToken();
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": missing semicolon\n";
            nextToken();
        }
    }
    else
        nextToken();
}

void assign()
{
    if(tokens[curr].type == "IDENTIFIER")
        nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected Identifier\n";
        nextToken();
    }
    
    if(tokens[curr].name == "=")
    {
        nextToken();
    }
    
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected = \n";
        nextToken();
    }
    
    exprlog();
    
    if(tokens[curr].name == ";")
        nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": missing semicolon\n";
        nextToken();
    }
    
}

void _while()
{
    
    
    if(tokens[curr].name == "while")
    {
        nextToken();
         
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected while\n";
        nextToken();
    }
    
    if(tokens[curr].name == "(")
    {
        nextToken();
         
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected open parenthesis\n";
        nextToken();
    }
    
    exprlog();
    
    if(tokens[curr].name == ")")
        nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected closed parenthesis\n";
        nextToken();
    }
    
    if(tokens[curr].name != "{")
        line();
    else
    {
        nextToken();
        if(tokens[curr].name != "}")
        {
            do
            {
                line();
            }
            while (tokens[curr].name != "}" && !eof());
            
            if(tokens[curr].name != "}")
            {
                output += "Line ";
                output += std::to_string(tokens[curr].line);
                output += ": expected closed curly bracket\n";
                nextToken();
            }
            else
                nextToken();
        }
    }
    
}

void _if()
{
   if(tokens[curr].name == "if")
    {
        nextToken();
    }
    
    if(tokens[curr].name == "(")
        nextToken();
    
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected '('\n";
        nextToken();
    }
    
    exprlog();

    if(tokens[curr].name == ")")
        nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected ')'\n";
        nextToken();
    }
    
    if(tokens[curr].name != "{")
    {
        line();
    }
    else
    {
        nextToken();
        if(tokens[curr].name != "}")
        {
            do
            {
                line();

            }
            while (tokens[curr].name != "}" && !eof());
            
            if(tokens[curr].name != "}")
            {
                output += "Line ";
                output += std::to_string(tokens[curr].line);
                output += ": expected closed curly bracket\n";
                nextToken();
            }
            else
                nextToken();
        }
    }
    
    if(tokens[curr].name == "else")
    {
        nextToken();
        if(tokens[curr].name != "{")
             line();
        else
        {
            nextToken();
            if(tokens[curr].name != "}")
            {
                do
                {
                    line();
                }
                while (tokens[curr].name != "}" && !eof());
                
                if(tokens[curr].name != "}")
                {
                    output += "Line ";
                    output += std::to_string(tokens[curr].line);
                    output += ": expected closed curly bracket\n";
                    nextToken();
                }
                else
                    nextToken();
            }
        }
    }
}

void line()
{
    if(tokens[curr].type == "IDENTIFIER" )
    {
        if(tokens[curr+1].name == "=")
            assign();
        else if(tokens[curr+1].name == "(")
            call_function();
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": incorrect line statement/n";
            nextToken();
        }
    }
    
    else if(tokens[curr].name == "if")
        _if();
    
    else if(tokens[curr].name == "while")
    {
         
        _while();
    }
    else if(tokens[curr].name == "return")
        _return();
    
    else if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
    {
        dvar_local();
    }
    else
    {
          
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": not a valid statement\n";
        nextToken();
    }
}

void parameter()
{
    if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
    {
        nextToken();
         
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected type\n";
        nextToken();
    }
    
    if(tokens[curr].type == "IDENTIFIER")
    {
        nextToken();
         
    }
    else
    {
        
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected identifier\n";
        nextToken();
    }
    
    while(tokens[curr].name == ",")
    {
        nextToken();
         
        if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
        {
            nextToken();
             
        }
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected type\n";
            nextToken();
        }
        
        if(tokens[curr].type == "IDENTIFIER")
        {
            nextToken();
             
        }
        else
        {
            
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected identifier\n";
            nextToken();
        }
    }
}

void dmethod()
{
    if(tokens[curr].name == "(")
    {
        nextToken();
         
    }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected '(' \n";
        nextToken();
    }
    
    if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
    {
        parameter();
         
    }
    

    if(tokens[curr].name == ")")
    {
        
        nextToken();
         
    }
    
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected ')' \n";
        nextToken();
    }

    if(tokens[curr].name == "{")
    {
        nextToken();
         
    }
    
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected '{' \n";
        nextToken();
    }
    
    if(tokens[curr].name != "}")
    {
        do
        {
            line();
        }
        while (tokens[curr].name != "}" && !eof());
        
        if(tokens[curr].name != "}")
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected closed curly bracket\n";
            nextToken();
        }
        else
            nextToken();
    }
}

void dvar_local()
{
    
     if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
     {
         nextToken();
     }
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected type\n";
        nextToken();

    }
    
    do
    {
        if(tokens[curr].type == "IDENTIFIER")
        {
            nextToken();
        }
        
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected identifier'\n";
            nextToken();

        }
                if(tokens[curr].name != "," && tokens[curr].name != ";")
                {
                    if(tokens[curr].name == "=")
                    {
                        nextToken();
                    }
                    else
                    {
                        output += "Line ";
                        output += std::to_string(tokens[curr].line);
                        output += ": expected '='\n";
                        nextToken();
                    }
                    
                    exprlog();
                    if(tokens[curr].name == ",")
                        nextToken();
                }
        
            else if(tokens[curr].name == ",")
                nextToken();
            }
        while (tokens[curr].name != ";" && !eof());
        
        if(tokens[curr].name == ";")
            nextToken();
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected ';'\n";
            nextToken();
        }
}

void dvar_global()
{
    while(tokens[curr].name == ",")
    {
        nextToken();
        
        if(tokens[curr].type == "IDENTIFIER")
        {
            nextToken();
        }
        else
        {
            output += "Line ";
            output += std::to_string(tokens[curr].line);
            output += ": expected identifier";
            nextToken();
        }
    }
    
    if(tokens[curr].name == ";")
        nextToken();
    else
    {
        output += "Line ";
        output += std::to_string(tokens[curr].line);
        output += ": expected ';'\n";
        nextToken();
    }
}

void program()
{
    
    
    if(tokens.size() !=0)
    {
        do
        {
             
            if(tokens[curr].name == "int" || tokens[curr].name == "char" || tokens[curr].name == "float" || tokens[curr].name == "boolean" || tokens[curr].name == "string" || tokens[curr].name == "void")
            {
                nextToken();
                 
            }
            else
            {
                output += "Line ";
                output += std::to_string(tokens[curr].line);
                output +=  ": expected type\n";
            }
            
            if(tokens[curr].type == "IDENTIFIER")
            {
                nextToken();
                 
            }
            else
            {
                output += "Line ";
                output += std::to_string(tokens[curr].line);
                output += ": Expected identifier\n";
                
            }
            
            if(tokens[curr].name == "(")
            {
                dmethod();
            }
            else
            {
                dvar_global();
            }
        }
        while(!eof());
    }
}
