run: lexer.o parser.o symboltable.o semantics.o
        g++ -std=c++11 -o run lexer.o parser.o symboltable.o semantics.o

lexer.o: lexer.hpp lexer.cpp
        g++ -std=c++11 -c -Wall lexer.cpp

parser.o: parser.hpp parser.cpp
        g++ -std=c++11 -c -Wall parser.cpp

symboltable.o: symboltable.cpp
        g++ -std=c++11 -c -Wall symboltable.cpp
semantics.o: semantics.cpp
        g++ -std=c++11 -c -Wall semantics.cpp

clean:
        rm *.o
