CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

EXEC = bataille_navale
CSS = ./misc/github-pandoc.css
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

LDFLAGS = -lcunit
TEST_EXEC = test_bataille_navale
TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(patsubst test/%.c,test/obj/%.o,$(TEST_SRC))
NO_OBJ_MAIN = $(filter-out obj/main.o, $(OBJ))

.PHONY: all clean html test

all: link

link: compile

# JEU

compile: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@


obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

# TESTS

test: all bats-test cunit-test test-clean

bats-test:
	bats bataille_navale.bats

cunit-test: compile-cunit launch-cunit

compile-cunit: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ) $(NO_OBJ_MAIN)
	$(CC) $^ -o $@ $(LDFLAGS)

test/obj/%.o: test/%.c
	@mkdir -p test/obj
	$(CC) -o $@ -c $< $(CFLAGS)

launch-cunit:
	./$(TEST_EXEC)

html:
	pandoc -o README.html -sc $(CSS) README.md

clean: obj-clean test-clean html-clean

obj-clean:
	rm -rf obj
	rm -rf $(EXEC)

test-clean:
	rm -rf test/obj
	rm -rf obj
	rm -f $(TEST_EXEC)
	rm -rf $(EXEC)

html-clean:
	rm -f *.html

