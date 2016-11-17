# Compiler Builder 8
# Lester Young
# Timothy Konzel
# Remington Howell
# Johnathan Sattler
# John Herold

compile: compile.o lexer.o input.o printing.o parser.o
	gcc -o compile compile.o lexer.o input.o printing.o parser.o

compile.o: compile.c compile.h lexer.h input.h printing.h tokens.h
	gcc -c compile.c

lexer.o: lexer.c lexer.h tokens.h
	gcc -c lexer.c

input.o: input.c input.h tokens.h
	gcc -c input.c

printing.o: printing.c printing.h tokens.h
	gcc -c printing.c

parser.o: parser.c parser.h tokens.h input.h
	gcc -c parser.c

clean:
	rm -f *.o compile