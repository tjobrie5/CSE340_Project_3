#ifndef LEXER
#define LEXER
//begin include guard LEXER
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>

//This class contains the enum used to represent tokens internally
class Tokens{
    public:
        enum type {
            UNDECIDED,
            OPERATOR,
            DELIMITER,
            INTEGER,
            FLOAT,
            HEXADECIMAL,
            OCTAL,
            STRING,
            CHAR,
            ID,
            KEYWORD,
            UNDEFINED
        };
};

//Data structure - holds a word, and the token corresponding to that word.
//The made-up token UNDECIDED internally represents uncertainty about the word's final token.
class WordTokenPair{
    public:
        WordTokenPair(std::string word, unsigned int line);
        WordTokenPair(std::string word, Tokens::type type, unsigned int line);
        Tokens::type getType();
        void setType(Tokens::type);
        std::string getWord();
        std::string getFormattedOutput();

        unsigned int getLineNumber();
        void setLineNumber(unsigned int lineNumber);
    private:
        std::string word_;
        Tokens::type type_;
        unsigned int lineNumber_;
};

class Token{
    public:
        Token();
        Token(WordTokenPair convertible);
        Tokens::type getTokenName();
        std::string getTokenWord();
        unsigned int getTokenLineNumber();
    private:
        Tokens::type tokenName_;
        std::string tokenWord_;
        unsigned int tokenLineNumber_;
};

//A shell class that wraps the lexer. This is so I can conveniently integrate the lexer into the compiler later.
class LexerDriver{
    public:
        LexerDriver();
        std::vector<Token> performLexing(std::string inFile, std::string outFile);
};

//Catch-all class that handles everything related to the lexer itself.
class LexicalAnalyzer{
    public:
        LexicalAnalyzer();
        std::vector<WordTokenPair> lexer(std::string rawInput);
        std::string tokenizedOutputToString(std::vector<WordTokenPair> tokenizedInput);
        std::vector<std::vector<int> > dfaLookup;
        std::vector<Token> convertOutputToParserStandard(std::vector<WordTokenPair> input);
    private:
        void prepForTokenization(std::vector<std::string>);
        std::vector<WordTokenPair> identifyKeywords(std::vector<WordTokenPair>);
        std::vector<WordTokenPair> convertLinesToPairs(std::vector<std::string>);
        std::vector<WordTokenPair> runThroughDFA(std::vector<WordTokenPair>);
        int selectNextState(int oldState, char nextChar);
        int determineInputClass(char input); 
        Tokens::type getTokenFromFinalState(int finalState);
        bool isDelimiter(char input);
        bool isOperator(char input);
        bool isKeyword(std::string input);
};

//handles disk I/O. Very generic, likely portable to the parser and semantic analyzer.
class FileManager{
    public:
        FileManager(std::string inFile, std::string outFile);
        std::string readInput();
        void writeOutput(std::string stringToWrite);

    private:
        std::string inputFile_, outputFile_;
};



#endif
//end include guard LEXER
