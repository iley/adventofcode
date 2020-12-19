package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type constraint struct {
	from1 int
	to1   int
	from2 int
	to2   int
}

func validate(val int, cons constraint) bool {
	return cons.from1 <= val && val <= cons.to1 && cons.from2 <= val && val <= cons.to2
}

type dataset struct {
	fields        map[string]constraint
	myTicket      []int
	nearbyTickets [][]int
}

func load(input io.Reader) *dataset {
	fieldRe := regexp.MustCompile(`(\w+): (\d+)-(\d+) or (\d+)-(\d+)`)
	data := dataset{
		fields:        make(map[string]constraint),
		myTicket:      []int{},
		nearbyTickets: [][]int{},
	}
	stage := 0
	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		if strings.Contains(scanner.Text(), "your ticket:") {
			stage = 1
			continue
		} else if strings.Contains(scanner.Text(), "nearby tickets:") {
			stage = 2
			continue
		}

		if stage == 0 {
			m := fieldRe.FindStringSubmatch(scanner.Text())
			if m == nil {
				continue
			}
			f := m[1]
			c := constraint{
				from1: parseInt(m[2]),
				to1:   parseInt(m[3]),
				from2: parseInt(m[4]),
				to2:   parseInt(m[5]),
			}
			data.fields[f] = c
			continue
		}

		if stage == 1 {
			t := parseTicket(scanner.Text())
			if len(t) > 0 {
				data.myTicket = t
			}
			continue
		}

		if stage == 2 {
			t := parseTicket(scanner.Text())
			if len(t) > 0 {
				data.nearbyTickets = append(data.nearbyTickets, t)
			}
		}
	}
	return &data
}

func parseInt(str string) int {
	i64, err := strconv.ParseInt(str, 10, 32)
	if err != nil {
		log.Fatal(err)
	}
	return int(i64)
}

func parseTicket(str string) []int {
	res := []int{}
	ss := strings.Split(str, ",")
	for _, s := range ss {
		i64, err := strconv.ParseInt(s, 10, 32)
		if err != nil {
			continue
		}
		res = append(res, int(i64))
	}
	return res
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

	data := load(input)
	fmt.Printf("%+v\n", data)

}
