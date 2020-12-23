BIN=part1 part2

run: $(BIN) always
	@echo "=== PART 1 ==="
	./part1
	@echo "=== PART 2 ==="
	./part2

$(BIN): %: %.c
	clang -std=c17 -Wall -Werror -o $@ $<

clean:
	rm -f $(BIN)

.PHONY: always clean
