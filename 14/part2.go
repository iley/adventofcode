package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"regexp"
	"strconv"
)

var (
	maskRe = regexp.MustCompile(`mask = ([01X]+)`)
	memRe  = regexp.MustCompile(`mem\[(\d+)\] = (\d+)`)
)

type instruction struct {
	opcode string
	mask   string
	addr   int64
	val    int64
}

func load(input io.Reader) []instruction {
	program := []instruction{}
	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		m := maskRe.FindStringSubmatch(scanner.Text())
		if m != nil {
			mask := m[1]
			program = append(program, instruction{opcode: "mask", mask: mask})
			continue
		}

		m = memRe.FindStringSubmatch(scanner.Text())
		if m != nil {
			addr, err := strconv.ParseInt(m[1], 10, 64)
			if err != nil {
				log.Fatal(err)
			}
			val, err := strconv.ParseInt(m[2], 10, 64)
			if err != nil {
				log.Fatal(err)
			}
			program = append(program, instruction{opcode: "mem", addr: addr, val: val})
			continue
		}
	}
	return program
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s FILE\n", os.Args[0])
		os.Exit(1)
	}

	inputPath := os.Args[1]

	input, err := os.Open(inputPath)
	if err != nil {
		log.Fatal(err)
	}
	defer input.Close()

	program := load(input)

	for i := range program {
		fmt.Printf("%+v\n", program[i])
	}
}
