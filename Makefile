SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS := -std=c99 -Wall -I./include -g
LINK := -L./bin/ -lwdl
TEST_SRC := $(wildcard test/*.c)
TEST_BIN := $(patsubst test/%.c, testbin/%, $(TEST_SRC))
BIN_SRC := $(wildcard src/game/*.c)
BIN_OBJ := $(patsubst src/%.c, obj/%.o, $(BIN_SRC))
CC := gcc

.PHONY: all clean test 

all: bin/libwdl.a test bin/game

bin/libwdl.a: $(OBJ)
	ar rcs $@ $^

$(OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f obj/*.o bin/* tags testbin/*

test: $(TEST_BIN) bin/libwdl.a

testbin/%: test/%.c bin/libwdl.a
	$(CC) $(CFLAGS) -o $@ $< $(LINK)

bin/game: $(BIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

$(BIN_OBJ): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LINK)
