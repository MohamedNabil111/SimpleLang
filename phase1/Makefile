# Makefile for SimpleLang Compiler

all: simplelang

simplelang: simplelang.y simplelang.l
	bison -y -d simplelang.y
	flex simplelang.l
	gcc y.tab.c lex.yy.c -o simplelang.exe

test1: simplelang
	./simplelang.exe < test1.sl

test2: simplelang
	./simplelang.exe < test2.sl

test3: simplelang
	./simplelang.exe < test3.sl

test4: simplelang
	./simplelang.exe < test4.sl

test5: simplelang
	./simplelang.exe < test5.sl

clean:
	rm -f lex.yy.c y.tab.c y.tab.h simplelang.exe
