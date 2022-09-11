SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS := --std=c99 -Wall -I./include
LINK := -L./bin/ -lwdl
TEST_SRC := $(wildcard test/*.c)
TEST_BIN := $(patsubst test/%.c, bin/%, $(TEST_SRC))
CC := tcc

.PHONY: all clean test

all: bin/libwdl.a

bin/libwdl.a: $(OBJ)
	ar rcs $@ $^

$(OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f obj/*.o bin/* tags

test: $(TEST_BIN)

$(TEST_BIN): bin/%: test/%.c
	$(CC) $(CFLAGS) -o $@ $<
