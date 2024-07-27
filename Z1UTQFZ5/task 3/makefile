# Variables
CC = gcc
LEX = flex
YACC = yacc
CFLAGS = -Wall
LIBS = -lfl
LEX_SOURCE = Z1UTQFZ5.l
YACC_SOURCE = Z1UTQFZ5.y
LEX_OUT = lex.yy.c
YACC_OUT = y.tab.c
YACC_HEADER = y.tab.h
OBJECTS = lex.yy.o y.tab.o
EXECUTABLE = myparser

# Default rule
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

lex.yy.o: $(LEX_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) -c $(LEX_OUT) -o $@

y.tab.o: $(YACC_OUT)
	$(CC) $(CFLAGS) -c $(YACC_OUT) -o $@

$(LEX_OUT): $(LEX_SOURCE)
	$(LEX) $(LEX_SOURCE)

$(YACC_OUT) $(YACC_HEADER): $(YACC_SOURCE)
	$(YACC) $(YFLAGS) -d $(YACC_SOURCE)

# Clean rule
clean:
	rm -f $(LEX_OUT) $(YACC_OUT) $(YACC_HEADER) $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean

# Command-line argument for input file
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)
