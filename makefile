CC=gcc
OPT=-O0
DEBUG=1
DCCFLAGS=-g
CCFLAGS=$(OPT) -Wall

CCFLAGS:=$(CCFLAGS) $(DCCFLAGS)

INCDIR=includes
OBJDIR=objects
BINARY=bf
SRC=src
TESTDIR=test
OBJECTS=$(OBJDIR)/stack.o $(OBJDIR)/sha256.o $(OBJDIR)/writeFile.o $(OBJDIR)/main.o 
INLCUDES=$(INCDIR)/stack.h $(INCDIR)/writeFile.h $(INCDIR)/sha256.h
TEST_FILES=$(TESTDIR)/genTest.py
TEST_INPUT_FILE=$(TESTDIR)/input.txt
PYTHON_INTR=python3

all : $(BINARY)

# $@ => left of colon
# $^ => everything on right
# $< => first object
$(BINARY) : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(OBJDIR)/$@ $(OBJECTS)

$(OBJDIR)/%.o : $(SRC)/%.c $(INLCUDES)
	$(CC) $(CCFLAGS) -c -o $@ $<

# test: $(BINARY) $(TEST_FILES) $(TEST_INPUT_FILE)
# 	make all 
# 	./sqlite $(DB_FILE) < $(TEST_INPUT_FILE)
# 	rm $(TEST_INPUT_FILE)
clean:
	rm -rf $(OBJDIR)/* 
commit:
	git add .
	git commit -m "$(CM)"
	git push

