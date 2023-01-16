CC=gcc
OPT=-O3
DEBUG=1

INCDIR=includes
OBJDIR=objects
BINARY=rec
SRC=src
TESTDIR=test
OBJECTS=$(OBJDIR)/stack.o $(OBJDIR)/writeFile.o
INLCUDES=$(INCDIR)/stack.h $(INCDIR)/writeFile.h
TEST_FILES=$(TESTDIR)/genTest.py
TEST_INPUT_FILE=$(TESTDIR)/input.txt
PYTHON_INTR=python3

all : $(BINARY)

# $@ => left of colon
# $^ => everything on right
# $< => first object
$(BINARY) : $(OBJECTS) $(INLCUDES)
	$(CC) -o $(OBJDIR)/$@ $^

$(OBJDIR)/%.o : $(SRC)/%.c $(INCDIR)/%.h
	$(CC) -c -g -o $@ $<

test: $(BINARY) $(TEST_FILES) $(TEST_INPUT_FILE)
	make all 
	./sqlite $(DB_FILE) < $(TEST_INPUT_FILE)
	rm $(TEST_INPUT_FILE)
clean:
	rm -rf $(OBJDIR)/* 
commit:
	git add .
	git commit -m "$(CM)"
	git push

