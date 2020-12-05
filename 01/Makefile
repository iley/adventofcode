run: solve always
	./solve < input.txt

solve: solve.c
	clang -std=c17 -Wall -Werror -o $@ $<

clean:
	rm -f solve

.PHONY: always clean
