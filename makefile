EXEC = run
CC = g++ -std=gnu++11
CFLAGS = -c -Wall

$(EXEC) :parser.o lexer.o
        $(CC) -o $(EXEC) parser.o lexer.o

parser.o:Header.h parser.cpp lexer.cpp
        $(CC) $(CFLAGS) parser.cpp
lexer.o:Header.h lexer.cpp
        $(CC) $(CFLAGS) lexer.cpp
symboltable.0:Header.h symboltable.cpp
        $(CC) $(CFLAGS) symboltable.cpp
clean :
        $(RM) *.o

