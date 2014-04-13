#include"lexer.hpp"
#include<stdio.h>

/**
* Constructor for WordTokenPair. Allows the word to be specified, but the token is left UNDECIDED.
* Param word - The initial word in the pair
* Param line - the line number of the token
*/
WordTokenPair::WordTokenPair(std::string word, unsigned int line){
    this->word_ = word;
    this->type_ = Tokens::UNDECIDED;
    this->lineNumber_ = line + 1;   //convenience for loops
}

/**
* Constructor for WordTokenPair. Allows both the word and token to be specified.
* Param word - The initial word in the pair
* Param type - the initial token in the pair
* Param line - the line number of the token
*/
WordTokenPair::WordTokenPair(std::string word, Tokens::type type, unsigned int line){
    this->word_ = word;
    this->type_ = type;
    this->lineNumber_ = line + 1; // convenience for loops
}

/*
* Standard accessor function for the type_ member of the WordTokenPair.
* Return - the value of member variable type_
*/
Tokens::type WordTokenPair::getType(){
    return type_;
}

/**
* Standard accessor function for the word_ member of the WordTokenpair.
* Return - the value of member variable word_
*/
std::string WordTokenPair::getWord(){
    return word_;
}

/**
* Standard mutator function for the type_ member of the WordTokenPair
* Param type - The new value for the type_ member variable
*/
void WordTokenPair::setType(Tokens::type type){
    type_ = type;
}

/**
* Generates the pretty-printed string for the pair, including the word, the token, and spacing.
* Return - the pretty-printed output
*/
std::string WordTokenPair::getFormattedOutput(){
    std::string typeString;
    switch(this->type_){
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
    std::cout << typeString << this->word_ << " line " << this->lineNumber_ << "\n";
    return typeString + this->word_;
}

/*
* Constructor for FileManager. Requires the input and output filenames.
* Param inFile - The name of the file to read from.
* Param outFile - The name of the file to write to.
*/
FileManager::FileManager(std::string inFile, std::string outFile){
    this->inputFile_ = inFile;
    this->outputFile_ = outFile;
}

/*
* Reads the entire contents of the input file.
* Return - A string containing the text-mode contents of the input file.
*/
std::string FileManager::readInput(){
    std::ifstream fileStream;
    fileStream.open(this->inputFile_.c_str());

    std::string contents = "";

    if(fileStream.is_open()){
        std::string currentLine;

        while(std::getline(fileStream, currentLine)){
            contents = contents + "\n" + currentLine;
        }

        //for some reason, there is an extra newline on the beginning. i want it gone.
        contents = std::string(contents.c_str(), 1, std::string::npos);

        fileStream.close();
    }
    else
        std::cout << "Error reading " << this->inputFile_ << ".\n";

    return contents;
}

/*
* Writes a given string to the output file.
* Param stringToWrite - The string to write to the output file
*/
void FileManager::writeOutput(std::string stringToWrite){
    std::ofstream fileStream;
    fileStream.open(this->outputFile_.c_str());
    if(fileStream.is_open()){
        fileStream << stringToWrite;
        fileStream.close();
    }
    else
        std::cout << "Error writing to " << this->outputFile_ << "\n";
}


/*
* Constructor for LexicalAnalyzer. Sets up the DFA transition function table.
*/
LexicalAnalyzer::LexicalAnalyzer(){
    //set up the state lookup table
    this->dfaLookup = std::vector<std::vector<int> >(18);
    
    for(unsigned int i = 0; i < this->dfaLookup.size(); i++){
        this->dfaLookup[i] = std::vector<int>(15);
    }

//0
    this->dfaLookup[0][0] = 1;
    this->dfaLookup[0][1] = 2;
    this->dfaLookup[0][2] = 2;
    this->dfaLookup[0][3] = 8;
    this->dfaLookup[0][4] = 8;
    this->dfaLookup[0][5] = 8;
    this->dfaLookup[0][6] = 8;
    this->dfaLookup[0][7] = 8;
    this->dfaLookup[0][8] = 8;
    this->dfaLookup[0][9] = 17;
    this->dfaLookup[0][10] = 17;
    this->dfaLookup[0][11] = 14;
    this->dfaLookup[0][12] = 9;
    this->dfaLookup[0][13] = 17;
    this->dfaLookup[0][14] = 17;    //double check this

//1
    this->dfaLookup[1][0] = 17;
    this->dfaLookup[1][1] = 5;
    this->dfaLookup[1][2] = 17;
    this->dfaLookup[1][3] = 17;
    this->dfaLookup[1][4] = 17;
    this->dfaLookup[1][5] = 17;
    this->dfaLookup[1][6] = 6;
    this->dfaLookup[1][7] = 17;
    this->dfaLookup[1][8] = 17;
    this->dfaLookup[1][9] = 3;
    this->dfaLookup[1][10] = 17;
    this->dfaLookup[1][11] = 17;
    this->dfaLookup[1][12] = 17;
    this->dfaLookup[1][13] = 17;
    this->dfaLookup[1][14] = 17; 

//2
    this->dfaLookup[2][0] = 2;
    this->dfaLookup[2][1] = 2;
    this->dfaLookup[2][2] = 2;
    this->dfaLookup[2][3] = 17;
    this->dfaLookup[2][4] = 17;
    this->dfaLookup[2][5] = 17;
    this->dfaLookup[2][6] = 17;
    this->dfaLookup[2][7] = 17;
    this->dfaLookup[2][8] = 17;
    this->dfaLookup[2][9] = 3;
    this->dfaLookup[2][10] = 17;
    this->dfaLookup[2][11] = 17;
    this->dfaLookup[2][12] = 17;
    this->dfaLookup[2][13] = 17;
    this->dfaLookup[2][14] = 17; 

//3
    this->dfaLookup[3][0] = 4;
    this->dfaLookup[3][1] = 4;
    this->dfaLookup[3][2] = 4;
    this->dfaLookup[3][3] = 17;
    this->dfaLookup[3][4] = 17;
    this->dfaLookup[3][5] = 17;
    this->dfaLookup[3][6] = 17;
    this->dfaLookup[3][7] = 17;
    this->dfaLookup[3][8] = 17;
    this->dfaLookup[3][9] = 17;
    this->dfaLookup[3][10] = 17;
    this->dfaLookup[3][11] = 17;
    this->dfaLookup[3][12] = 17;
    this->dfaLookup[3][13] = 17;
    this->dfaLookup[3][14] = 17;

//4
    this->dfaLookup[4][0] = 4;
    this->dfaLookup[4][1] = 4;
    this->dfaLookup[4][2] = 4;
    this->dfaLookup[4][3] = 17;
    this->dfaLookup[4][4] = 17;
    this->dfaLookup[4][5] = 17;
    this->dfaLookup[4][6] = 17;
    this->dfaLookup[4][7] = 17;
    this->dfaLookup[4][8] = 17;
    this->dfaLookup[4][9] = 17;
    this->dfaLookup[4][10] = 17;
    this->dfaLookup[4][11] = 17;
    this->dfaLookup[4][12] = 17;
    this->dfaLookup[4][13] = 17;
    this->dfaLookup[4][14] = 17;

//5
    this->dfaLookup[5][0] = 5;
    this->dfaLookup[5][1] = 5;
    this->dfaLookup[5][2] = 17;
    this->dfaLookup[5][3] = 17;
    this->dfaLookup[5][4] = 17;
    this->dfaLookup[5][5] = 17;
    this->dfaLookup[5][6] = 17;
    this->dfaLookup[5][7] = 17;
    this->dfaLookup[5][8] = 17;
    this->dfaLookup[5][9] = 17;
    this->dfaLookup[5][10] = 17;
    this->dfaLookup[5][11] = 17;
    this->dfaLookup[5][12] = 17;
    this->dfaLookup[5][13] = 17;
    this->dfaLookup[5][14] = 17;

//6
    this->dfaLookup[6][0] = 7;
    this->dfaLookup[6][1] = 7;
    this->dfaLookup[6][2] = 7;
    this->dfaLookup[6][3] = 7;
    this->dfaLookup[6][4] = 7;
    this->dfaLookup[6][5] = 17;
    this->dfaLookup[6][6] = 17;
    this->dfaLookup[6][7] = 17;
    this->dfaLookup[6][8] = 17;
    this->dfaLookup[6][9] = 17;
    this->dfaLookup[6][10] = 17;
    this->dfaLookup[6][11] = 17;
    this->dfaLookup[6][12] = 17;
    this->dfaLookup[6][13] = 17;
    this->dfaLookup[6][14] = 17;

//7
    this->dfaLookup[7][0] = 7;
    this->dfaLookup[7][1] = 7;
    this->dfaLookup[7][2] = 7;
    this->dfaLookup[7][3] = 7;
    this->dfaLookup[7][4] = 7;
    this->dfaLookup[7][5] = 17;
    this->dfaLookup[7][6] = 17;
    this->dfaLookup[7][7] = 17;
    this->dfaLookup[7][8] = 17;
    this->dfaLookup[7][9] = 17;
    this->dfaLookup[7][10] = 17;
    this->dfaLookup[7][11] = 17;
    this->dfaLookup[7][12] = 17;
    this->dfaLookup[7][13] = 17;
    this->dfaLookup[7][14] = 17;

//8
/*    this->dfaLookup[8][0] = 17;
    this->dfaLookup[8][1] = 17;         some DEEP MAGIC. a fix for something i lost the manual for
    this->dfaLookup[8][2] = 17;*/

    this->dfaLookup[8][0] = 8;
    this->dfaLookup[8][1] = 8;
    this->dfaLookup[8][2] = 8;

    this->dfaLookup[8][3] = 8;
    this->dfaLookup[8][4] = 8;
    this->dfaLookup[8][5] = 8;
    this->dfaLookup[8][6] = 8;
    this->dfaLookup[8][7] = 8;
    this->dfaLookup[8][8] = 8;
    this->dfaLookup[8][9] = 17;
    this->dfaLookup[8][10] = 8;
    this->dfaLookup[8][11] = 17;
    this->dfaLookup[8][12] = 17;
    this->dfaLookup[8][13] = 17;
    this->dfaLookup[8][14] = 17;

//9
    this->dfaLookup[9][0] = 10;
    this->dfaLookup[9][1] = 10;
    this->dfaLookup[9][2] = 10;
    this->dfaLookup[9][3] = 10;
    this->dfaLookup[9][4] = 10;
    this->dfaLookup[9][5] = 10;
    this->dfaLookup[9][6] = 10;
    this->dfaLookup[9][7] = 10;
    this->dfaLookup[9][8] = 10;
    this->dfaLookup[9][9] = 10;
    this->dfaLookup[9][10] = 10;
    this->dfaLookup[9][11] = 10;
    this->dfaLookup[9][12] = 17;
    this->dfaLookup[9][13] = 11;
    this->dfaLookup[9][14] = 10;

//10
    this->dfaLookup[10][0] = 17;
    this->dfaLookup[10][1] = 17;
    this->dfaLookup[10][2] = 17;
    this->dfaLookup[10][3] = 17;
    this->dfaLookup[10][4] = 17;
    this->dfaLookup[10][5] = 17;
    this->dfaLookup[10][6] = 17;
    this->dfaLookup[10][7] = 17;
    this->dfaLookup[10][8] = 17;
    this->dfaLookup[10][9] = 17;
    this->dfaLookup[10][10] = 17;
    this->dfaLookup[10][11] = 17;
    this->dfaLookup[10][12] = 13;
    this->dfaLookup[10][13] = 17;
    this->dfaLookup[10][14] = 17;

//11
    this->dfaLookup[11][0] = 12;
    this->dfaLookup[11][1] = 12;
    this->dfaLookup[11][2] = 12;
    this->dfaLookup[11][3] = 12;
    this->dfaLookup[11][4] = 12;
    this->dfaLookup[11][5] = 12;
    this->dfaLookup[11][6] = 12;
    this->dfaLookup[11][7] = 12;
    this->dfaLookup[11][8] = 12;
    this->dfaLookup[11][9] = 12;
    this->dfaLookup[11][10] = 12;
    this->dfaLookup[11][11] = 12;
    this->dfaLookup[11][12] = 12;
    this->dfaLookup[11][13] = 12;
    this->dfaLookup[11][14] = 12;

//12
    this->dfaLookup[12][0] = 17;
    this->dfaLookup[12][1] = 17;
    this->dfaLookup[12][2] = 17;
    this->dfaLookup[12][3] = 17;
    this->dfaLookup[12][4] = 17;
    this->dfaLookup[12][5] = 17;
    this->dfaLookup[12][6] = 17;
    this->dfaLookup[12][7] = 17;
    this->dfaLookup[12][8] = 17;
    this->dfaLookup[12][9] = 17;
    this->dfaLookup[12][10] = 17;
    this->dfaLookup[12][11] = 17;
    this->dfaLookup[12][12] = 13;
    this->dfaLookup[12][13] = 17;
    this->dfaLookup[12][14] = 17;

//13
    this->dfaLookup[13][0] = 17;
    this->dfaLookup[13][1] = 17;
    this->dfaLookup[13][2] = 17;
    this->dfaLookup[13][3] = 17;
    this->dfaLookup[13][4] = 17;
    this->dfaLookup[13][5] = 17;
    this->dfaLookup[13][6] = 17;
    this->dfaLookup[13][7] = 17;
    this->dfaLookup[13][8] = 17;
    this->dfaLookup[13][9] = 17;
    this->dfaLookup[13][10] = 17;
    this->dfaLookup[13][11] = 17;
    this->dfaLookup[13][12] = 17;
    this->dfaLookup[13][13] = 17;
    this->dfaLookup[13][14] = 17;

//14
    this->dfaLookup[14][0] = 14;
    this->dfaLookup[14][1] = 14;
    this->dfaLookup[14][2] = 14;
    this->dfaLookup[14][3] = 14;
    this->dfaLookup[14][4] = 14;
    this->dfaLookup[14][5] = 14;
    this->dfaLookup[14][6] = 14;
    this->dfaLookup[14][7] = 14;
    this->dfaLookup[14][8] = 14;
    this->dfaLookup[14][9] = 14;
    this->dfaLookup[14][10] = 14;
    this->dfaLookup[14][11] = 15;
    this->dfaLookup[14][12] = 14;
    this->dfaLookup[14][13] = 16;
    this->dfaLookup[14][14] = 14;

//15
    this->dfaLookup[15][0] = 17;
    this->dfaLookup[15][1] = 17;
    this->dfaLookup[15][2] = 17;
    this->dfaLookup[15][3] = 17;
    this->dfaLookup[15][4] = 17;
    this->dfaLookup[15][5] = 17;
    this->dfaLookup[15][6] = 17;
    this->dfaLookup[15][7] = 17;
    this->dfaLookup[15][8] = 17;
    this->dfaLookup[15][9] = 17;
    this->dfaLookup[15][10] = 17;
    this->dfaLookup[15][11] = 17;
    this->dfaLookup[15][12] = 17;
    this->dfaLookup[15][13] = 17;
    this->dfaLookup[15][14] = 17;

//16
    this->dfaLookup[16][0] = 14;
    this->dfaLookup[16][1] = 14;
    this->dfaLookup[16][2] = 14;
    this->dfaLookup[16][3] = 14;
    this->dfaLookup[16][4] = 14;
    this->dfaLookup[16][5] = 14;
    this->dfaLookup[16][6] = 14;
    this->dfaLookup[16][7] = 14;
    this->dfaLookup[16][8] = 14;
    this->dfaLookup[16][9] = 14;
    this->dfaLookup[16][10] = 14;
    this->dfaLookup[16][11] = 14;
    this->dfaLookup[16][12] = 14;
    this->dfaLookup[16][13] = 14;
    this->dfaLookup[16][14] = 14;

//17
    this->dfaLookup[17][0] = 17;
    this->dfaLookup[17][1] = 17;
    this->dfaLookup[17][2] = 17;
    this->dfaLookup[17][3] = 17;
    this->dfaLookup[17][4] = 17;
    this->dfaLookup[17][5] = 17;
    this->dfaLookup[17][6] = 17;
    this->dfaLookup[17][7] = 17;
    this->dfaLookup[17][8] = 17;
    this->dfaLookup[17][9] = 17;
    this->dfaLookup[17][10] = 17;
    this->dfaLookup[17][11] = 17;
    this->dfaLookup[17][12] = 17;
    this->dfaLookup[17][13] = 17;
    this->dfaLookup[17][14] = 17;
}

/*
* Constructor for LexerDriver. Needs to be empty, but explicitly declared for clarity.
*/
LexerDriver::LexerDriver(){
}

/*
* Wrapper for the entire action of the lexer. Used so the lexer may be easily ported as a library to other programs without rewriting main()
* Param inFile - The name of the input file
* Param outFile - The name of the output file.
*/
std::vector<Token> LexerDriver::performLexing(std::string inFile, std::string outFile){
    FileManager fileHandling = FileManager(inFile, outFile);
    std::string inputFromFile = fileHandling.readInput();

    LexicalAnalyzer lexAnalyzer = LexicalAnalyzer();
    std::vector<WordTokenPair> tokenizedOutput = lexAnalyzer.lexer(inputFromFile);

    return lexAnalyzer.convertOutputToParserStandard(tokenizedOutput);
}

std::vector<Token> LexicalAnalyzer::convertOutputToParserStandard(std::vector<WordTokenPair> input){
    std::vector<Token> output;

    for(unsigned int i = 0; i < input.size(); i++){
        output.push_back(Token(input[i]));
    }

    return output;
}


Token::Token(){ //required for dynamic vector initialization

}

Token::Token(WordTokenPair convertible){
    tokenName_ = convertible.getType();
    tokenWord_ = convertible.getWord();
    tokenLineNumber_ = convertible.getLineNumber();
}

Tokens::type Token::getTokenName(){
    return tokenName_;
}

std::string Token::getTokenWord(){
    return tokenWord_;
}

unsigned int Token::getTokenLineNumber(){
    return tokenLineNumber_;
}

unsigned int WordTokenPair::getLineNumber(){
    return lineNumber_;
}

void WordTokenPair::setLineNumber(unsigned int lineNumber){
    lineNumber_ = lineNumber;
}

/*
* Determines whether or not a character is an operator.
* Param input - The char to check
* Return - true if the char is an operator, false otherwise.
*/
bool LexicalAnalyzer::isOperator(char input){
    return (input == '+' || input == '-' || input == '*' || input == '/' || input == '%' || input == '<' || input == '>' || input == '=' || input == '!' || input == '|' || input == '&');
}

/*
* Determines whether or not a character is an delimiter.
* Param input - The char to check
* Return - true if the char is an delimiter, false otherwise.
*/
bool LexicalAnalyzer::isDelimiter(char input){
    return (input == '(' || input == ')' || input == '{' || input == '}' || input == '[' || input == ']' || input == ';' || input == ',' || input == ':');
}

/*
* Converts a vector of WordPairTokens to a string consisting of all the pretty-printed values of the pairs.
* Param tokenizedInput - a vector of WordTokenPairs
* Return - A string containing the pairs' formatted output, pretty-printed.
*/
std::string LexicalAnalyzer::tokenizedOutputToString(std::vector<WordTokenPair> tokenizedInput){
    std::string stringifiedOutput = "";
    for(unsigned int i = 0; i < tokenizedInput.size(); i++)
        stringifiedOutput = stringifiedOutput + tokenizedInput[i].getFormattedOutput() + "\n";
    return stringifiedOutput;
}

/*
* Given a vector of WordTokenPairs, re-processes all ID tokens to check if they should be KEYWORD tokens.
* Param input - The vector to check over
* Return - The input, with all KEYWORDs identified and marked
*/
std::vector<WordTokenPair> LexicalAnalyzer::identifyKeywords(std::vector<WordTokenPair> input){
    for(unsigned int i = 0; i < input.size(); i++){
        if(input[i].getType() == Tokens::ID){
            if(this->isKeyword(input[i].getWord())){
                input[i].setType(Tokens::KEYWORD);
            }
        }
    }
    return input;
}

/*
* Determines whether or not a string is a KEYWORD.
* Param input - The string to check
* Return - true if the string is a KEYWORD, false otherwise.
*/
bool LexicalAnalyzer::isKeyword(std::string input){
    return (input == "for" || input == "if" || input == "else" || input == "while" || input == "return" || input == "integer" || input == "float" || input == "void" || input == "char" || input == "string" || input == "boolean" || input == "read" || input == "print" || input == "true" || input == "false");
}

/*
* Given a vector of strings, splits the lines in the strings into words, and packs them into WordTokenPairs.
* Param inputAsLines - A vector of strings matching the lines taken from the input file
* Return - A vector of WordTokenPairs containing the words from the input, with tokens partially resolved
*/
std::vector<WordTokenPair> LexicalAnalyzer::convertLinesToPairs(std::vector<std::string> inputAsLines){

    bool inStringOrChar = false;
    bool endStringOrChar = false;
    bool justReadBackslash = false;
    bool readBackslashLastTime = false;
    //now lines to wordtokenpairs
    std::vector<WordTokenPair> words = std::vector<WordTokenPair>();
    std::string currentWord;    
    //for each line, and each char in the line
    for(unsigned int i = 0; i < inputAsLines.size(); i++){
        currentWord = "";
        inStringOrChar = false;
        endStringOrChar = false;
        justReadBackslash = false;
        readBackslashLastTime = false;
        //for each character in that line
        for(unsigned int j = 0; j < inputAsLines[i].length(); j++){
           if(readBackslashLastTime){
                //do something to ignore ' and "
            }
            else{
                if(inputAsLines[i][j] == '\\'){
                    justReadBackslash = true;
                }
            }

            //track if we're in a string or not
           if((inputAsLines[i][j] == '\'' || inputAsLines[i][j] == '\"') && !readBackslashLastTime){
               if(!inStringOrChar){
                    //this is the beginning of a new!
                    if(currentWord.length() > 0)
                        words.push_back(WordTokenPair(currentWord, i));
                    currentWord = "";
                    inStringOrChar = true;
                    //if its the end of a string, put it on the word, then end the word, and suppress the following
                }
                else{
                    //this is the end of a word
                    endStringOrChar = true;
                }
            }

            if((inputAsLines[i][j] == '\n' || inputAsLines[i][j] == ' ' || this->isOperator(inputAsLines[i][j]) || this->isDelimiter(inputAsLines[i][j])) && !inStringOrChar){
                if(currentWord.length() > 0){
                    words.push_back(WordTokenPair(currentWord, i));
                    currentWord = "";
                }
                //if it's isOperator or isDelimiter, add it as a word
                if(this->isOperator(inputAsLines[i][j])){
                        words.push_back(WordTokenPair(std::string(1,inputAsLines[i][j]), Tokens::OPERATOR, i));       //going to need to find a way to turn a char into a char array of one element
                }
                if(this->isDelimiter(inputAsLines[i][j])){
                    words.push_back(WordTokenPair(std::string(1,inputAsLines[i][j]), Tokens::DELIMITER, i));
                }
            }
            else{   //this is when it's not an op, delim, or newline, and we're not in potatoes
                currentWord = currentWord + inputAsLines[i][j];
            }

            if(endStringOrChar){
                //no longer be in the string
                inStringOrChar = false;
                words.push_back(WordTokenPair(currentWord, i));
                currentWord = "";
                endStringOrChar = false;
            }

            if(readBackslashLastTime){
                readBackslashLastTime = false;
            }

            if(justReadBackslash){
                justReadBackslash = false;
                readBackslashLastTime = true;
            }
        }

        //this is the end of the current line - if i have a word that is not a carriage return, be sure to add it
        //also, trim unwanted spaces from the word
        if(currentWord.length() > 1 || (currentWord.length() == 1 && currentWord.c_str()[0] != '\r')){

            if(currentWord[currentWord.length()-1] == ' ')
                currentWord.erase(currentWord.length()-1);
            words.push_back(WordTokenPair(currentWord, i));
        }
    }

    return words;
}

/*
* Given a vector of WordTokenPairs, determines the token for each undecided word via DFA analysis.
* param inputPairs - the pairs to determine
* Return - the inputPairs vector with all tokens decided
*/
std::vector<WordTokenPair> LexicalAnalyzer::runThroughDFA(std::vector<WordTokenPair> inputPairs){
    for(unsigned int i = 0; i < inputPairs.size(); i++){
        if(inputPairs[i].getType() == Tokens::UNDECIDED){
            //this word needs work
            int currentState = 0;   //always start at the initial state
            for(unsigned int j = 0; j < inputPairs[i].getWord().length(); j++){       //the minus 1 was in this line. i dunno...
                currentState = this->selectNextState(currentState, inputPairs[i].getWord()[j]);
            }
            //use the final state to determine the token and assign it
            Tokens::type finalToken = this->getTokenFromFinalState(currentState);
            inputPairs[i].setType(finalToken);
        }
    }
    return inputPairs;
}

/*
* Given the final state of the DFA, determines which token it corresponds to accepting (or rejecting)
* Param finalState - the state to look up
* Return - The token corresponsing to the state
*/
Tokens::type LexicalAnalyzer::getTokenFromFinalState(int finalState){
    if(finalState == 1 || finalState == 2)
        return Tokens::INTEGER;
    if(finalState == 4)
        return Tokens::FLOAT;
    if(finalState == 5)
        return Tokens::OCTAL;
    if(finalState == 7)
        return Tokens::HEXADECIMAL;
    if(finalState == 8)
        return Tokens::ID;
    if(finalState == 13)
        return Tokens::CHAR;
    if(finalState == 15)
        return Tokens::STRING;

    //else
    return Tokens::UNDEFINED;
}

/*
* Given a DFA state and the next input symbol, determines the subsequent state.
* Param oldState - the state the machine reached on the last step
* Param nextChar - the next character in the DFA's input
* Return - the number of the next state of the DFA
*/
int LexicalAnalyzer::selectNextState(int oldState, char nextChar){
    int inputClass = this->determineInputClass(nextChar);
    return this->dfaLookup[oldState][inputClass];
}

/*
* Given an input, determines which of many mutually-exclusive input classes it belongs to
* Param input - The input the test
* Return - the number of the input class
*/
int LexicalAnalyzer::determineInputClass(char input){
    if(input == 48) //0
        return 0;
    if(input >= 49 && input <= 55) //1-7
        return 1;
    if(input == 56 || input == 57) //8,9
        return 2;
    if(input >= 97 && input <= 102) //a-f
        return 3;
    if(input >= 65 && input <= 70) //A-F
        return 4;
    if(input >= 103 && input <= 119) //g-w
        return 5;
    if(input == 120) //x
        return 6;
    if(input == 121 || input == 122) //y,z
        return 7;
    if(input >= 71 && input <= 90) //G-Z
        return 8;
    if(input == 46) //.
        return 9;
    if(input == 36 || input == 95) //_,$
        return 10;
    if(input == 34) //"
        return 11;
    if(input == 39) //'
        return 12;
    if(input == 92) //backslash
        return 13;

    // all else
    return 14;
}

/*
* Given a raw body of text, lexes it.
* Param rawInput - the text to lex
* Return - The words and tokens created by lexing
*/
std::vector<WordTokenPair> LexicalAnalyzer::lexer(std::string rawInput){

    //vector to hold input lines
    std::vector<std::string> inputAsLines = std::vector<std::string>();
    //put the string in a stream for line-by-line reading
    std::istringstream inputStream(rawInput);
    std::string tempString;
    while(std::getline(inputStream, tempString))
        inputAsLines.push_back(tempString);

    std::vector<WordTokenPair> words;
    words = this->convertLinesToPairs(inputAsLines);

    words = this->runThroughDFA(words);

    words = this->identifyKeywords(words);

/*for(unsigned int i = 0; i < words.size(); i++){
    words[i].getFormattedOutput();
}*/

    return words;
}
