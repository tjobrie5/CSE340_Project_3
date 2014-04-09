EXEC=run	# name of executable is run
CC=g++		# compile with g++
CFLAGS=-std=c++11 -c  -Wall 

all: $(EXEC)

$(EXEC): parser.o lexer.o
	$(CC) -o $(EXEC) parser.o lexer.o

parser.o: parser.cpp
	$(CC) $(CFLAGS) parser.cpp

lexer.o: lexer.cpp Header.h
	$(CC) $(CFLAGS) lexer.cpp
	
clean: 
	rm -f *.o
	rm -f $(EXEC)
	rm -f *output.txt
