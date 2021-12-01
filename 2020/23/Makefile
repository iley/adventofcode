BIN=part1 part2 part2ll part2opt

all: $(BIN)

run_part1: part1 always
	./part1

run_part2: part2 always
	./part2

run_part2ll: part2ll always
	./part2ll

run_part2opt: part2opt always
	./part2opt

$(BIN): %: %.c
	$(CC) -std=c17 -Wall -Werror -O3 -o $@ $<

clean:
	rm -f $(BIN)

.PHONY: all always clean
