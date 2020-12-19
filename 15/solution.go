package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func parse(input string) []int64 {
	numbers := []int64{}
	parts := strings.Split(input, ",")
	for _, part := range parts {
		n, err := strconv.ParseInt(part, 10, 64)
		if err != nil {
			continue
		}
		numbers = append(numbers, n)
	}
	return numbers
}

func play(input []int64, steps int) int64 {
	var num, prev int64
	history := make(map[int64]int64)
	for i := 0; i < steps; i++ {
		step := int64(i + 1)

		if i < len(input) {
			num = input[i]
		} else {
			lastStep, repeat := history[prev]
			if repeat {
				num = step - 1 - lastStep
			} else {
				num = 0
			}
		}

		history[prev] = step - 1
		prev = num
	}
	return num
}

func main() {
	if len(os.Args) < 3 {
		fmt.Fprintf(os.Stderr, "Usage: %s NUMBERS STEP\n", os.Args[0])
		os.Exit(1)
	}

	input := parse(os.Args[1])
	step, err := strconv.ParseInt(os.Args[2], 10, 32)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(play(input, int(step)))

}
