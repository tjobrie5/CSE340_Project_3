//Chris's Parser

#include"lexer.hpp"
#include"parser.hpp"
#include <string>
#include "semantics.cpp"
#include <algorithm>
using namespace std;
string name ="";
string type = "";
string value= "";
string scope= "global";
bool methodReDec = false;
string leftType = "";
bool assignFlag = false;
bool returnFlag = false;
bool ifFlag = false;
bool whileFlag = false;
semantics* sem = new semantics();

vector<string> tempVector;

void Parser::writeError(std::string errorMessage){
    buildSuccessful = false;
    std::cout << errorMessage << std::endl;
    errorMessagesToWrite = errorMessagesToWrite + errorMessage + "\n";
}

Parser::Parser(std::string out){
    currentLocation_ = 0;
    buildSuccessful = true;
    outputFileName = out;
    errorMessagesToWrite = "";
}

void Parser::importTokens(std::vector<Token> tL){
    tokenList_ = tL;
    if(tokenList_.size() == 0){
        tokenList_.push_back(Token());
    }
    else{
        currentToken_ = tokenList_[currentLocation_];
    }
}

void Parser::printTokens(){
    std::cout << "Name\t\tValue\t\tLine\n";

    for(unsigned int i = 0; i < tokenList_.size(); i++){

        std::string typeString;
        switch(tokenList_[i].getTokenName()){
            case 0:
                typeString = "UNDECIDED\t";
                break;
            case 1:
                typeString = "OPERATOR\t";
                break;
            case 2:
                typeString = "DELIMITER\t";
                break;
            case 3:
                typeString = "INTEGER\t";
                break;
            case 4:
                typeString = "FLOAT\t\t";
                break;
            case 5:
                typeString = "HEXADECIMAL ";
                break;
            case 6:
                typeString = "OCTAL\t";
                break;
            case 7:
                typeString = "STRING\t";
                break;
            case 8:
                typeString = "CHARACTER\t";
                break;
            case 9:
                typeString = "IDENTIFIER\t";
                break;
            case 10:
                typeString = "KEYWORD\t";
                break;
            case 11:
                typeString = "UNDEFINED\t";
                break;
            default:
                break;
        }

        std::cout << typeString << "\t" << tokenList_[i].getTokenWord() << "\t\t" << tokenList_[i].getTokenLineNumber() << "\n";
    }
}

bool Parser::program(){
//do special handling if there is only one token

//    while(keepTrying){
    
    while(!isLastToken()){
        if(identifyType()){
            type = currentToken_.getTokenWord();//###############################
            nextToken();
            if(currentToken_.getTokenName() == Tokens::ID){
                name = currentToken_.getTokenWord(); //###############################
                nextToken();
                if(currentToken_.getTokenName() == Tokens::DELIMITER && (currentToken_.getTokenWord() == "," || currentToken_.getTokenWord() == ";")){
                    dvar_global();  //highly experimental
                } else
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
                    dmethod();  //experimental
                }
                else{
                    backToken();//experimental
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    //writeError("Line " + convert.str() + ":\texpected delimiter ;");
                    advanceToNextLine();
                }
            }
            else{
                //didn't get ID where one was expected
                backToken();
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected identifier");
                advanceToNextLine();
            }
        }
        else{
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected type");
            advanceToNextLine();           
        }
    }

    return true;
}

bool Parser::dvar_global(){
    bool keepTrying = true;
    bool test = sem->unicity(currentToken_.getTokenWord(),scope);
    
    if(!test)  //#######################
    {
        std::stringstream convert;
        convert << currentToken_.getTokenLineNumber();
        writeError("Duplicated variable " + currentToken_.getTokenWord() +" in line " + convert.str());
        
    }
    else
        sem->st->insert(name,type,"global"); //###############################
    do{
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
            nextToken();
            if(currentToken_.getTokenName() == Tokens::ID){
                name = currentToken_.getTokenWord(); //###############################
                
                test = sem->unicity(currentToken_.getTokenWord(),scope); //########################
                
                if(!test)  //#######################
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Duplicated variable " + currentToken_.getTokenWord() +" in line " + convert.str());
                    
                }
                else
                    sem->st->insert(name, type, "global"); //###############################
                
                nextToken();
            }
            else{
                //wanted an ID, but didn't get one.
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected identifier");
                advanceToNextLine();
                return true;
            }
        }
        else if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
            nextToken();
            keepTrying = false;
        }
        else{
            //not a semicolon or a comma
            backToken();
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected delimiter");
            advanceToNextLine();
            keepTrying = false;
        }
    }while(keepTrying);
    return true;
}

bool Parser::identifyType(){
    return currentToken_.getTokenName() == Tokens::KEYWORD && (currentToken_.getTokenWord() == "integer" || currentToken_.getTokenWord() == "float" || currentToken_.getTokenWord() == "void" || currentToken_.getTokenWord() == "char" || currentToken_.getTokenWord() == "float" || currentToken_.getTokenWord() == "string" || currentToken_.getTokenWord() == "boolean");
}

bool Parser::dvar_local(){
    bool keepTrying = true;

    if(identifyType()){
        type = currentToken_.getTokenWord(); //###############################
        nextToken();
        do{
            if(currentToken_.getTokenName() == Tokens::ID){
                name = currentToken_.getTokenWord(); //###############################
                
                bool test = sem->unicity(currentToken_.getTokenWord(),scope);
                
                if(!test)  //#######################
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Duplicated variable " + currentToken_.getTokenWord() +" in line " + convert.str());
                }
                else
                    sem->st->insert(name, type, scope);
                
                nextToken();
                //leftType = name;  //##############
                //cout << name << endl << endl;
                //optional = exprlog
                if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "="){
                    nextToken();
                    if(!exprlog()){
                        //expected exprlog where there is none
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        writeError("Line " + convert.str() + ":\texpected value or identifier");
                        return false;
                    }
                }
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
                    nextToken();
                }
                else{
                    keepTrying = false;
                }

            }
            else{
                //expected ID where there is none
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected identifier");
                return false;
            }
        }while(keepTrying);

        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
            nextToken();

            return true;
        }
        else{
            //expected ; where there is none
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            //writeError("Line " + convert.str() + ":\texpected delimiter ;");
            

            return false;
        }
    }
    else{
        //expected type where there is none

        return false;
    }
}

bool Parser::dmethod(){
    if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
        nextToken();
        if(identifyType()){
            
            if(!parameter()){
                advanceToNextLine();
                return false;
            }
        }
        //no else on this, it's optional
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
            for(int i = 0; i<tempVector.size(); i=i+2)
            {
                sem->st->insert(tempVector[i], tempVector[i+1], name);
                
            }
            
            tempVector.clear(); // removes vector #####
            
            bool test = sem->unicity(name,scope);
            
            if(!test)  //#######################
            {
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
               writeError("Duplicated method " + name +" in line " + convert.str());
            }
            else
                sem->st->insert(name, type, "function");  //###############################
            
            nextToken();
            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "{"){
                scope = name; //###############################
                nextToken();

                //0 or more lines
                bool keepTrying = true;
                while(keepTrying){
                    if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "}") {
                        keepTrying = false;
                    }
                    else{
                        //if this is the last token, and the } is missing, it just spins its wheels here.
                        if(isLastToken()){
                            std::stringstream convert;
                            convert << currentToken_.getTokenLineNumber();
                            writeError("Line " + convert.str() + ":\texpected delimiter");
                            advanceToNextLine();
                            return true;
                        }
                        else{
                            line();
                        }
                    }
                }

                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "}"){
                    nextToken();
                    return true;
                }
                else{
                    //missing }
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Line " + convert.str() + ":\texpected delimiter");
                    advanceToNextLine();
                    return true;
                }
            }
            else{
                //expected {
                backToken(); //to account for overshooting
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected delimiter");
                do{
                    nextToken();
                }while(!(currentToken_.getTokenWord() == "}" || isLastToken()));
                nextToken();
                return true;
            }
        }
        else{
            //missing )
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected delimiter )");
            do{
                nextToken();
            }while(!(currentToken_.getTokenWord() == "}" || isLastToken()));
            nextToken();
            return true;
        }
    }
    else{
        //expected (
        std::stringstream convert;
        convert << currentToken_.getTokenLineNumber();
        writeError("Line " + convert.str() + ":\texpected delimiter");
        do{
            nextToken();
        }while(!(currentToken_.getTokenWord() == "}" || isLastToken()));
        nextToken();
        return true;
    }
}

bool Parser::parameter(){
    bool keepTrying = true;
    do{
        if(identifyType()){
            string tempType = currentToken_.getTokenWord(); //########################
            name += "-" + currentToken_.getTokenWord();  //###############################
            nextToken();
            if(currentToken_.getTokenName() == Tokens::ID){
                tempVector.push_back(currentToken_.getTokenWord()); //###########
                tempVector.push_back(tempType); //#########
                nextToken();
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
                    nextToken();
                }
                else{
                    keepTrying = false;
                }
            }
            else{
                //expected ID where there is none
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected identifier");
                return false;
            }
        }
        else{
            //expected type where there is none
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected type");
            return false;
        }

    }while(keepTrying);
    return true;
}

bool Parser::line(){
    bool result;

//hacky but it might just work
if(currentToken_.getTokenWord() == "("){
    backToken();
}


    if(identifyType()){
        result = dvar_local();
        if(!result){
            //skip to next line
            advanceToNextLine();
        }
    }
    else{
        if(currentToken_.getTokenName() == Tokens::ID){
            nextToken();
            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
                backToken();
                result = call_function();
                if(!result){
                    //skip to next line
                    advanceToNextLine();
                }
            }
            else{
                backToken();
                result = assign();
                if(!result){
                    //skip to next line
                    advanceToNextLine();
                }
            }
        }
        else{
            if(currentToken_.getTokenName() == Tokens::KEYWORD){
                if(currentToken_.getTokenWord() == "if"){
                    result = ifstmt();
                    if(!result){
                        //dunno where to advance to...
                        advanceToNextLine();
                    }
                } else
                if(currentToken_.getTokenWord() == "while"){
                    result = whilestmt();
                    if(!result){
                       //advance to next line i guess
                        advanceToNextLine();
                    }
                } else
                if(currentToken_.getTokenWord() == "return"){
                    result = returnstmt();
                    if(!result){
                        //skip to next line
                        advanceToNextLine();
                    }
                } else
                if(currentToken_.getTokenWord() == "read"){
                    result = call_function();
                    if(!result){
                        //skip to next line
                        advanceToNextLine();
                    }
                } else
                if(currentToken_.getTokenWord() == "print"){
                    result = call_function();
                    if(!result){
                        //skip to next line
                        advanceToNextLine();
                    }
                } else{
                    //unidentified keyword - prediction failed
                    return false;
                }
            }
            else{
                //no idea what this is - prediction failed to guess
                return false;
            }
        }
    }
    return true;
}

bool Parser::braceBlock(){
    if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "{"){
        nextToken();
        bool keepTrying = true;
        do{
            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "}"){
                keepTrying = false;
            }
            else{
                if(isLastToken()){
                    return true;
                }
                line();
            }
        }while(keepTrying);

        nextToken();
        return true;
    }
    else{
        line();
        nextToken();
        return true;
    }
}

bool Parser::ifstmt(){
    if(currentToken_.getTokenName() == Tokens::KEYWORD && currentToken_.getTokenWord() == "if"){
        nextToken();
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
            nextToken();
            ifFlag = true;
            if(exprlog()){
                if(!sem->boolCheck())
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Boolean expression expected in line " + convert.str());
                }
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
                    ifFlag = false;
                    nextToken();
                    braceBlock();
                    if(currentToken_.getTokenWord() == "{"){
                    backToken();
                    }
                    if(currentToken_.getTokenName() == Tokens::KEYWORD && currentToken_.getTokenWord() == "else"){
                        nextToken();
                        braceBlock();
                    }//optional, no else clause
                    return true;
                    
                }
                else{
                    //missing )
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Line " + convert.str() + ":\texpected delimiter");
                    return false;
                }
            }
            else{
                //missing exprlog
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected value or identifier");
                return false;
            }
        }
        else{
            //missing (
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected delimiter");
            return false;
        }
    }
    else{
        //missing if
        return false;
    }
}

bool Parser::whilestmt(){
    if(currentToken_.getTokenName() == Tokens::KEYWORD && currentToken_.getTokenWord() == "while"){
        nextToken();
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
            nextToken();
            whileFlag = true;
            if(exprlog()){
                if(!sem->boolCheck())
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Boolean expression expected in line " + convert.str());
                }
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
                    whileFlag = false;
                    nextToken();
                    braceBlock();
                    return true;
                }
                else{
                    //missing )
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Line " + convert.str() + ":\texpected delimiter");
                    return false;
                }
            }
            else{
                //missing exprlog
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected value or identifier");
                return false;
            }
        }
        else{
            //missing (
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Line " + convert.str() + ":\texpected delimiter");
            return false;
        }
    }
    else{
        //missing while
        return false;
    }
}

bool Parser::assign(){
    if(currentToken_.getTokenName() == Tokens::ID){
        bool test = sem->decleration(currentToken_.getTokenWord(), scope); //############################
        if(!test)
        {
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Variable " + currentToken_.getTokenWord() + " not found in line " + convert.str());
                       }
        else
        {
                name = currentToken_.getTokenWord();
                //cout <<"----" << name << "----" << scope << endl;
                leftType = sem->st->getType(name, scope);
        }
        
        nextToken();
        if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "="){
            nextToken();
            assignFlag = true;  //################### SETTING ASSIGN FLAG HERE
            if(exprlog()){
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
                    assignFlag = false; //RESETING ASSIgn FLag
                    bool typetest = sem->typeCheck(leftType); //###############################
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    if(!typetest)
                    {
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        writeError("Type mismatch in line " + convert.str());
                   }
                    
                    nextToken();
                    //###########################################################


                    return true;
                }
                else{
                    //no semicolon
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber() - 1;
                    //writeError("Line " + convert.str() + ":\texpected delimiter ;");
                    return false;
                }
            }
            else{
                //not an exprlog
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected value or identifier");
                return false;
            }
        }
        else{

            return false;
        }
    }
    else{
        //no id
        std::stringstream convert;
        convert << currentToken_.getTokenLineNumber();
        writeError("Line " + convert.str() + ":\texpected identifier");
        return false;
    }
}

bool Parser::returnstmt(){
    if(currentToken_.getTokenName() == Tokens::KEYWORD && currentToken_.getTokenWord() == "return"){
        nextToken();
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
            nextToken();
            return true;
        }
        else{
            //not a semicolon, so it must be an exprlog, then a semicolon
            returnFlag = true;
            if(exprlog()){
                
                string returnType = sem->st->getType(scope, "function");
                if(!sem->typeCheck(returnType))
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Return type mismatch in line " + convert.str());
                    return false;

                }
                 
                
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
                    returnFlag = false;
                    nextToken();
                    return true;
                }
                else{
                    //missing semicolon
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber() - 1;
                    //writeError("Line " + convert.str() + ":\texpected delimiter ;");
                    return false;
                }
            }
            else{
                //no exprlog, and not a semicolon
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected value or identifier");
                return false;
            }
        }
    }
    //no return keyword
    return false;
}

bool Parser::call_function(){
    if(currentToken_.getTokenName() == Tokens::ID || (currentToken_.getTokenName() == Tokens::KEYWORD && (currentToken_.getTokenWord() == "print" || currentToken_.getTokenWord() == "read"))){
        name = currentToken_.getTokenWord(); //###################################
        nextToken();

        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "(")
        {
            nextToken();
            Tokens::type temp = currentToken_.getTokenName(); //#######################
            
            switch(temp)
            {
                case Tokens::INTEGER : name += "-int";
                    break;
                case Tokens::CHAR : name += "-char"; break;
                case Tokens::FLOAT : name += "-float"; break;
                case Tokens::STRING : name += "-string"; break;
                default: break;
            }
          
            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
                //a leading comma. function has a problem, abort.
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected value or identifier");
                return false;
            }

            while(exprlog()){
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
                    //if you find a comma, advance and test another exprlog. 
                    nextToken();
                    
                    Tokens::type temp = currentToken_.getTokenName();
                    
                    switch(temp)
                    {
                        case Tokens::INTEGER : name += "-int";
                            break;
                        case Tokens::CHAR : name += "-char"; break;
                        case Tokens::FLOAT : name += "-float"; break;
                        default: break;
                    }
                    //but... if you find a ), then there's a missing exprlog.
                    if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        writeError("Line " + convert.str() + ":\texpected value or identifier");
                        return false;
                    }
                }
                else{
                    //if no close paren, keep testing for exprlog
                    if(!(currentToken_.getTokenWord() == ")")){
                        //what is next isnt a , or a )... what is it?
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        //writeError("Line " + convert.str() + ":\texpected delimiter ,");

                        return false;
                    }
                }
            }

            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
                bool test = sem->decleration(name, scope); //###########
                if(!test)
                {
                    if(!sem->checkParams(name))
                    {
                        
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        writeError("Type or numbers of parameters in method " + name + " are incorrect in line "+ convert.str());
                    }
                    else
                    {
                        std::stringstream convert;
                        convert << currentToken_.getTokenLineNumber();
                        writeError("Method " + name + " not found in line " + convert.str());
                    }
                }
                nextToken();
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ";"){
                    nextToken();
                    return true;
                }
                else{
                    //couldnt find semicolon
                    std::stringstream convert;
                    backToken();
                    convert << currentToken_.getTokenLineNumber();
                    //writeError("Line " + convert.str() + ":\texpected delimiter ;");

                    return false;
                }

            }
            else{
                //couldnt find close paren
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Line " + convert.str() + ":\texpected delimiter )");

                return false;
            }
        }
        else{
            //couldnt find open paren
            return false;
        }
    }
    else{
        //couldnt find identifier
        return false;
    }
}



bool Parser::call_function_no_semicolon(){
    if(currentToken_.getTokenName() == Tokens::ID || (currentToken_.getTokenName() == Tokens::KEYWORD && (currentToken_.getTokenWord() == "print" || currentToken_.getTokenWord() == "read"))){
        nextToken();
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "(")
        {
            nextToken();

            while(exprlog()){
                if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ","){
                    //if you find a comma, advance and test another exprlog. 
                    nextToken();
                }
                else{
                    //if no close paren, keep testing for exprlog
                    if(!(currentToken_.getTokenWord() == ")")){
                        return false;
                    }
                    else{
                    }
                }
            }

            if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
                nextToken();
                return true;

            }
            else{
                //couldnt find close paren
                return false;
            }
        }
        else{
            //couldnt find open paren
            return false;
        }
    }
    else{
        //couldnt find identifier
        return false;
    }
}


bool Parser::exprlog(){
    if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == ")"){
        //essentially an empty exprlog.
        return false;
    }

    if(opand()){
        while(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "|"){
            nextToken();
            if(!opand()){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}


bool Parser::opand(){
    if(opno()){
        while(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "&"){
            if(assignFlag || returnFlag || ifFlag || whileFlag)
                sem->Stack.push(currentToken_.getTokenWord()); //######
            
            nextToken();
            if(!opno()){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool Parser::opno(){
    if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "!"){
        if(assignFlag || returnFlag || ifFlag || whileFlag)
            sem->Stack.push(currentToken_.getTokenWord()); //#####
        
        nextToken();
    }
    return exprel();
}


//convenient split for a complex conditional
bool Parser::exprelConditional(){
        if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "!"){
            nextToken();
            if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "="){
                nextToken();
                return true;
            }
            else{
                backToken();
                return false;
            }
        }
        else{
            if(currentToken_.getTokenName() == Tokens::OPERATOR && (currentToken_.getTokenWord() == "=" || currentToken_.getTokenWord() == ">" || currentToken_.getTokenWord() == "<")){
                if(assignFlag || returnFlag || ifFlag || whileFlag)
                    sem->Stack.push(currentToken_.getTokenWord()); //#######
                
                nextToken();
                if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "="){
                    nextToken();
                    return true;
                }
                else{
                    backToken();
                    return true;
                }
            }
        }
        return false;
    }

bool Parser::exprel(){
    if(expr()){
        while(exprelConditional()){
            nextToken();      //WHAT ARE YOU DOING
            if(!expr()){

                return false;
            }

        }
        return true;
    }
    else{
        return false;
    }
}

bool Parser::expr(){
    if(product()){
        while((currentToken_.getTokenName() == Tokens::OPERATOR) && (currentToken_.getTokenWord() == "+" || currentToken_.getTokenWord() == "-")){
            if(assignFlag || returnFlag || ifFlag || whileFlag)
                sem->Stack.push(currentToken_.getTokenWord()); //#####
            
            nextToken();
            if(!product()){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool Parser::product(){
    if(sign()){
        while((currentToken_.getTokenName() == Tokens::OPERATOR) && (currentToken_.getTokenWord() == "/" || currentToken_.getTokenWord() == "*" || currentToken_.getTokenWord() == "%")){
            if(assignFlag || returnFlag || ifFlag || whileFlag)
                sem->Stack.push(currentToken_.getTokenWord()); //#####
            
            nextToken();
            if(!sign()){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool Parser::sign(){
    if(currentToken_.getTokenName() == Tokens::OPERATOR && currentToken_.getTokenWord() == "-"){
        if(assignFlag || returnFlag || ifFlag || whileFlag)
            sem->Stack.push(currentToken_.getTokenWord()); //#######
        
        nextToken();
    }
    return term();
}

bool Parser::term(){
    
    //must check for call_function before term, to enforce maximal munch
    if(currentToken_.getTokenName() == Tokens::ID){
        //now check for the opening paren
        
        bool test = sem->decleration(currentToken_.getTokenWord(), scope); //############################ Might have to remove
        if(!test)
        {
            std::stringstream convert;
            convert << currentToken_.getTokenLineNumber();
            writeError("Variable " +  currentToken_.getTokenWord() + " not found in line " + convert.str());
           // cout << "------" << scope + " "+ currentToken_.getTokenWord();
        }
        
        nextToken();
        if(currentToken_.getTokenName() == Tokens::DELIMITER && currentToken_.getTokenWord() == "("){
            //this is clearly supposed to be a call_function. back up the token and call it.
            backToken();
            return call_function();
        }
        else{

            //no paren, so it's not a call_function
            backToken();
            
            bool test = sem->decleration(currentToken_.getTokenWord(), scope); //############################
            if(!test)
            {
                std::stringstream convert;
                convert << currentToken_.getTokenLineNumber();
                writeError("Variable " +  currentToken_.getTokenWord() + " not found in line " + convert.str());
                
            }
            
        }
    }
    //no else, we don't care to check here
    if(currentToken_.getTokenName() == Tokens::CHAR || currentToken_.getTokenName() == Tokens::INTEGER || currentToken_.getTokenName() == Tokens::FLOAT || currentToken_.getTokenName() == Tokens::ID || currentToken_.getTokenName() == Tokens::HEXADECIMAL || currentToken_.getTokenName() == Tokens::OCTAL || currentToken_.getTokenName() == Tokens::STRING){
        Tokens::type temp = currentToken_.getTokenName();
        
        bool test;
        
        if(assignFlag || returnFlag || ifFlag || whileFlag)
        {
        switch(temp)
        {
            case Tokens::INTEGER : sem->Stack.push("INTEGER");
                break;
            case Tokens::CHAR : sem->Stack.push("CHAR"); break;
            case Tokens::FLOAT : sem->Stack.push("FLOAT"); break;
            case Tokens::STRING : sem->Stack.push("STRING"); break;
            case Tokens::ID : test = sem->decleration(currentToken_.getTokenWord(), scope); //##########################
                if(!test)
                {
                    std::stringstream convert;
                    convert << currentToken_.getTokenLineNumber();
                    writeError("Variable " +  currentToken_.getTokenWord() + " not found in line " + convert.str());
                    
                }
                else
                {
                    string upper = sem->st->getType(currentToken_.getTokenWord(), scope);
                    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
                    sem->Stack.push(upper);
                }
                break;
            default: break;
        }
        }
        nextToken();
        return true;
    }
    if((currentToken_.getTokenName() == Tokens::KEYWORD) && (currentToken_.getTokenWord() == "true" || currentToken_.getTokenWord() == "false")){
        if(assignFlag || returnFlag || ifFlag || whileFlag)
            sem->Stack.push("BOOLEAN");
        
        nextToken();
        return true;
    }
    //now test for exprlog
    if((currentToken_.getTokenName() == Tokens::DELIMITER) && (currentToken_.getTokenWord() == "(")){
        nextToken();
        if(exprlog()){
            if((currentToken_.getTokenName() == Tokens::DELIMITER) && (currentToken_.getTokenWord() == ")")){
                nextToken();
                return true;
            }
            else{
                //no closing paren
                return false;
            }
        }
    }

    //if no other options
    return false;
}

void Parser::nextToken(){
    if(currentLocation_ + 1 < tokenList_.size()){
        currentLocation_++;
        currentToken_ = tokenList_[currentLocation_];
    }
}

void Parser::backToken(){
    currentLocation_--;
    currentToken_ = tokenList_[currentLocation_];
}

void Parser::advanceToNextLine(){
    unsigned int currentLine = currentToken_.getTokenLineNumber();
    bool keepTrying = true;
    while(keepTrying){
        if(currentLocation_ + 1 < tokenList_.size()){
            currentLocation_++;
            currentToken_ = tokenList_[currentLocation_];

            if(currentToken_.getTokenLineNumber() != currentLine){
                keepTrying = false;
            }
        }
        else{
            //no tokens left... just return
            keepTrying = false;
        }
    }
}

bool Parser::isLastToken(){
    return currentLocation_ + 1 == tokenList_.size();
}

void Parser::beginParsing(){
    program();
    if(buildSuccessful){
        std::cout << "Build Successful\n";
    }

    std::ofstream fileStream;
    fileStream.open(outputFileName.c_str());
    if(fileStream.is_open()){
        fileStream << errorMessagesToWrite;
        fileStream.close();
    }
    else
        std::cout << "Error writing to " << this->outputFileName << "\n";
}

int main(int argc, char * argv[]){
    LexerDriver lDriver = LexerDriver();
    if(argc < 3)
        std::cout << "Error: Please specify input and output files.\n";
    else{
        std::vector<Token> tokens = lDriver.performLexing(argv[1], argv[2]);
        Parser parser = Parser(argv[2]);
        parser.importTokens(tokens);
        parser.beginParsing();
        
    }

    return 0;
}
