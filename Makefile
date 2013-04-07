
OBJS	= src/interpreter.lex.o src/interpreter.tab.o src/interpreter.o

libinterpreter.a: $(OBJS)	
	ar -r 	 libinterpreter.a $(OBJS)

src/interpreter.lex.c: src/interpreter.l src/interpreter.tab.h
	flex -o src/interpreter.lex.c src/interpreter.l

src/interpreter.lex.o:	src/interpreter.lex.c
	gcc -c src/interpreter.lex.c -o src/interpreter.lex.o

src/interpreter.tab.c: src/interpreter.y
	bison -o src/interpreter.tab.c -d src/interpreter.y

src/interpreter.tab.h: src/interpreter.y
	bison --defines=src/interpreter.tab.h -d src/interpreter.y

src/interpreter.tab.o:	src/interpreter.tab.c
	gcc -c src/interpreter.tab.c -o src/interpreter.tab.o

src/interpreter.o:src/interpreter.c
	gcc -c src/interpreter.c -o src/interpreter.o

clean:
	rm -f $(OBJS) src/interpreter.lex.c   src/interpreter.tab.c src/interpreter.tab.h

