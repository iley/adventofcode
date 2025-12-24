#INPUT=sample.txt
INPUT=input.txt

solution: solution.c input.h
	$(CC) -g -o solution solution.c

input.h: parse_input.awk $(INPUT)
	gawk -f parse_input.awk $(INPUT) > input.h

run: solution
	./solution

clean:
	rm -f solution input.h

.PHONY: clean run
