# SimpleLang Compiler - Phase 2
# Makefile

CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison

# Output executable
TARGET = compiler

# Source files
SOURCES = symbol_table.c quadruples.c semantic.c
HEADERS = val.h parameter.h symbol_table.h quadruples.h semantic.h

# Generated files
LEX_OUT = lex.yy.c
YACC_OUT = y.tab.c y.tab.h

.PHONY: all clean test

all: $(TARGET)

# Generate lexer
lex.yy.c: simplelang.l
	$(LEX) simplelang.l

# Generate parser
y.tab.c y.tab.h: simplelang.y
	$(YACC) -d -y simplelang.y

# Compile the compiler
$(TARGET): y.tab.c y.tab.h lex.yy.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) y.tab.c lex.yy.c $(SOURCES) -lfl -lm

# Windows-specific target (use this on Windows with MinGW)
windows: y.tab.c y.tab.h lex.yy.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET).exe y.tab.c lex.yy.c $(SOURCES) -lm

# Clean generated files
clean:
	rm -f $(TARGET) $(TARGET).exe lex.yy.c y.tab.c y.tab.h y.output symbols.txt

# Test with a sample file
test: $(TARGET)
	./$(TARGET) test.sl

# Run the GUI
gui:
	python compiler_gui.py

# Run the GUI (Windows)
gui-win:
	python compiler_gui.py
