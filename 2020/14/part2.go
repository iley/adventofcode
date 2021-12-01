package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"math/big"
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

func expandAddr(addr int64, mask string) []int64 {
	addrs := []int64{}

	ones := int64(0)
	xpos := []int{}

	for i := 0; i < len(mask); i++ {
		ones = ones << 1
		if mask[i] == '1' {
			ones = ones | 1
		} else if mask[i] == 'X' {
			xpos = append(xpos, len(mask)-1-i)
		}
	}

	for x := 0; x < (1 << len(xpos)); x++ {
		a := addr | ones
		for i := 0; i < len(xpos); i++ {
			if x&(1<<i) == 0 {
				a = (a &^ (1 << xpos[i]))
			} else {
				a = (a | (1 << xpos[i]))
			}
		}
		addrs = append(addrs, a)
	}
	return addrs
}

func execute(program []instruction) map[int64]int64 {
	var mask string
	mem := make(map[int64]int64)
	for i, inst := range program {
		fmt.Printf("%d/%d\n", i, len(program))

		if inst.opcode == "mask" {
			mask = inst.mask
		} else if inst.opcode == "mem" {
			addrs := expandAddr(inst.addr, mask)
			for _, addr := range addrs {
				mem[addr] = inst.val
			}
		}
	}
	return mem
}

func memorySum(mem map[int64]int64) big.Int {
	var s big.Int
	for _, val := range mem {
		s.Add(&s, big.NewInt(val))
	}
	return s
}

func printProgram(program []instruction) {
	for i := range program {
		fmt.Printf("%+v\n", program[i])
	}
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

	mem := execute(program)
	sum := memorySum(mem)
	fmt.Println(sum.String())
}
