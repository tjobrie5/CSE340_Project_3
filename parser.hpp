#ifndef PARSER
#define PARSER
//begin include guard PARSER

#include<string>

class Parser{
    public:
        Parser(std::string out);
        void importTokens(std::vector<Token> tL);
        void printTokens();

        void writeError(std::string errorMessage);

        void beginParsing();

        bool program();
        bool dvar_global();
        bool dvar_local();
        bool dmethod();
        bool parameter();
        bool line();
        bool braceBlock();
        bool ifstmt();
        bool whilestmt();
        bool assign();
        bool returnstmt();
        bool call_function();
        bool call_function_no_semicolon();
        bool exprlog();
        bool opand();
        bool opno();
        bool exprelConditional();
        bool exprel();
        bool expr();
        bool product();
        bool sign();
        bool term();

        void nextToken();
        void backToken();
        void advanceToNextLine();
        bool isLastToken();

        bool identifyType();
    private:
        std::vector<Token> tokenList_;
        Token currentToken_;
        unsigned int currentLocation_;
        bool buildSuccessful;
        std::string outputFileName;
        std::string errorMessagesToWrite;
};
#endif
//end include guard PARSER
