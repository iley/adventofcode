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

var (
	ruleRe = regexp.MustCompile(`(\d+): (.+)`)
	charRe = regexp.MustCompile(`"(\w)"`)
)

type rule struct {
	index  int
	letter byte
	seq1   []int
	seq2   []int
}

type ruleset []rule

// match at the start, return rest
func (rs ruleset) match(idx int, msg string) string {
	//fmt.Printf("match(%d, %s)\n", idx, msg)
	r := rs[idx]
	if r.letter != 0 {
		//fmt.Printf("match letter %c\n", r.letter)
		if len(msg) > 0 && msg[0] == r.letter {
			return msg[1:]
		}
		return msg
	}
	if r.seq2 != nil {
		r1 := rs.matchSeq(r.seq1, msg)
		if len(r1) < len(msg) {
			return r1
		}
		return rs.matchSeq(r.seq2, msg)
	}
	return rs.matchSeq(r.seq1, msg)
}

func (rs ruleset) matchSeq(seq []int, msg string) string {
	//fmt.Printf("matchSeq(%v, %s)\n", seq, msg)
	rest := msg
	for _, idx := range seq {
		r := rs.match(idx, rest)
		if len(r) == len(rest) {
			return msg
		}
		rest = r
	}
	return rest
}

func load(input io.Reader) (map[int]rule, []string) {
	scanner := bufio.NewScanner(input)

	rules := make(map[int]rule)

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			break
		}
		if r, ok := parseRule(line); ok {
			rules[r.index] = r
		} else {
			fmt.Printf("could not parse rule %s", line)
		}
	}

	messages := []string{}
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line != "" {
			messages = append(messages, line)
		}
	}

	return rules, messages
}

func parseRule(text string) (rule, bool) {
	var r rule

	m := ruleRe.FindStringSubmatch(text)
	if m == nil {
		return r, false
	}

	idx, _ := strconv.ParseInt(m[1], 10, 32)
	r.index = int(idx)

	body := m[2]

	m = charRe.FindStringSubmatch(body)
	if m != nil {
		r.letter = m[1][0]
	} else {
		parts := strings.Split(body, "|")
		r.seq1 = parseSeq(parts[0])
		if len(parts) > 1 {
			r.seq2 = parseSeq(parts[1])
		}
	}

	return r, true
}

func parseSeq(text string) []int {
	parts := strings.Split(text, " ")
	numbers := []int{}
	for _, part := range parts {
		n, err := strconv.ParseInt(part, 10, 32)
		if err != nil {
			continue
		}
		numbers = append(numbers, int(n))
	}
	return numbers
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

	ruleMap, messages := load(input)

	maxIdx := 0
	for k := range ruleMap {
		if k > maxIdx {
			maxIdx = k
		}
	}

	rules := make(ruleset, maxIdx+1)

	for k, v := range ruleMap {
		rules[k] = v
	}

	fmt.Printf("loaded %d rules and %d messages\n", len(rules), len(messages))
	//for _, r := range rules {
	//fmt.Printf("%+v\n", r)
	//}

	count := 0
	for _, msg := range messages {
		rest := rules.match(0, msg)
		fmt.Printf("match %s -> %s\n", msg, rest)
		if rest == "" {
			count++
		}
	}
	fmt.Println(count)
}
