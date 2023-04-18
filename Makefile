# Compiler
CC = gcc
BISON = bison
FLEX = flex

# Compilation Flags
CFLAGS = -Wall -g -Iinclude

# Directories
INCDIR = include
SRCDIR = src
TESTDIR = test
OBJDIR = obj

# Source Files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
TESTSRCS = $(wildcard $(TESTDIR)/*.c)
TESTOBJS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TESTSRCS))

# Main Target
all: main

# Compile Source Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Test Files
$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build main Executable
main: $(OBJS) $(TESTOBJS) $(OBJDIR)/y.tab.o $(OBJDIR)/lex.yy.o
	$(CC) $(CFLAGS) $(OBJS) $(TESTOBJS) -o $@

# Build parser Executable (only symbols table so far)
parse: $(OBJS) $(OBJDIR)/y.tab.o $(OBJDIR)/lex.yy.o
	$(CC) $(CFLAGS) $(OBJDIR)/y.tab.o $(OBJDIR)/lex.yy.o $(OBJDIR)/sym_tab.o  $(OBJDIR)/arith_exp.o -o $@


$(OBJDIR)/y.tab.c: $(SRCDIR)/parser.y
	$(BISON) -t -v -d -Wcounterexamples $< -o $(OBJDIR)/y.tab.c

$(OBJDIR)/lex.yy.c: $(SRCDIR)/lex.l
	$(FLEX) -o $(OBJDIR)/lex.yy.c $<

# Create Object Directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean
clean:
	del $(OBJDIR) *.exe myASM.txt

# Test Function
test:
	main

# Launch Parser
launch:
	.\parse.exe < input.txt
