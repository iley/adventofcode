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
	return (cons.from1 <= val && val <= cons.to1) || (cons.from2 <= val && val <= cons.to2)
}

type ruleset map[string]constraint
type ticket []int

type dataset struct {
	rules         ruleset
	myTicket      ticket
	nearbyTickets []ticket
}

func load(input io.Reader) *dataset {
	ruleRe := regexp.MustCompile(`([\w ]+): (\d+)-(\d+) or (\d+)-(\d+)`)
	data := dataset{
		rules:         make(ruleset),
		myTicket:      ticket{},
		nearbyTickets: []ticket{},
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
			m := ruleRe.FindStringSubmatch(scanner.Text())
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
			data.rules[f] = c
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

func parseTicket(str string) ticket {
	res := ticket{}
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

func validateTicket(t ticket, rules ruleset) bool {
	for _, val := range t {
		valid := false
		for _, rule := range rules {
			// fmt.Printf("%d rule %+v\n", val, rule)
			if validate(val, rule) {
				valid = true
			}
		}
		if !valid {
			return false
		}
	}
	return true
}

func possibleFields(val int, rules ruleset) []string {
	matching := []string{}
	for f, c := range rules {
		if validate(val, c) {
			matching = append(matching, f)
		}
	}
	return matching
}

func remove(ss []string, x string) []string {
	res := []string{}
	for _, s := range ss {
		if s != x {
			res = append(res, s)
		}
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

	fieldCount := len(data.myTicket)

	fmt.Printf("loaded %d rules, %d fields in my ticket, %d nearby tickets\n", len(data.rules), len(data.myTicket), len(data.nearbyTickets))

	validTickets := []ticket{data.myTicket}
	for _, t := range data.nearbyTickets {
		if validateTicket(t, data.rules) {
			validTickets = append(validTickets, t)
		}
	}
	fmt.Printf("found %d valid tickets\n", len(validTickets))

	candidates := make([][]string, fieldCount)

	for i := 0; i < fieldCount; i++ {
		m := make(map[string]int)
		for _, t := range validTickets {
			fields := possibleFields(t[i], data.rules)
			for _, f := range fields {
				m[f]++
			}
		}
		for f, c := range m {
			if c == len(validTickets) {
				candidates[i] = append(candidates[i], f)
			}
		}
	}

	fieldNames := make([]string, fieldCount)
	for {
		progress := false

		for i := 0; i < fieldCount; i++ {
			if fieldNames[i] != "" {
				continue
			}

			if len(candidates[i]) == 1 {
				fieldNames[i] = candidates[i][0]
				for j := 0; j < fieldCount; j++ {
					candidates[j] = remove(candidates[j], fieldNames[i])
				}
				progress = true
			}
		}

		if !progress {
			break
		}
	}

	fmt.Println(strings.Join(fieldNames, ", "))

	answer := 1
	for i := 0; i < fieldCount; i++ {
		if strings.HasPrefix(fieldNames[i], "departure") {
			answer *= data.myTicket[i]
		}
	}

	fmt.Println(answer)
}
