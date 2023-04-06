PARS=parser.y
LEX =lex.l
BIN =main


CFLAGS=-Wall -g

OBJ= sym_tab.o test_sym_tab.o

all:$(BIN)

%.o :%.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

y.tab.c: $(PARS)
	bison -t -v -Wcounterexample -d $<

lex.yy.c: $(LEX)
	flex $<

$(BIN): $(OBJ)
	gcc $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	del $(OBJ) parser.tab.c lex.yy.c parser.tab.h parser.output lex.exe main.exe
