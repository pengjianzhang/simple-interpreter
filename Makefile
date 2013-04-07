
OBJS	= lex.yy.o interpreter.tab.o interpreter.o

libinterpreter.a: $(OBJS)	
	ar -r 	 libinterpreter.a $(OBJS)

lex.yy.c: interpreter.l interpreter.tab.h
	flex interpreter.l

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

interpreter.tab.c: interpreter.y
	bison -d interpreter.y

interpreter.tab.h: interpreter.y
	bison -d interpreter.y



interpreter.tab.o:	interpreter.tab.c
	gcc -c interpreter.tab.c -o interpreter.tab.o

interpreter.o:interpreter.c
	gcc -c interpreter.c -o interpreter.o

clean:
	rm -f $(OBJS) lex.yy.c   interpreter.tab.c interpreter.tab.h

