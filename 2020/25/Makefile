BIN=part1 part2

all: $(BIN)

run1: part1 always
	./part1

run2: part2 always
	./part2

$(BIN): %: %.c
	clang -std=c17 -Wall -Werror -o $@ $<

clean:
	rm -f $(BIN)

.PHONY: all always clean run1 run2
