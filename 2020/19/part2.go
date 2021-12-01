package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"regexp"
	"sort"
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

func (rs ruleset) matches(idx int, msg string) []string {
	r := rs[idx]
	if r.letter != 0 {
		if len(msg) > 0 && msg[0] == r.letter {
			return []string{msg[1:]}
		}
		return []string{}
	}
	if r.seq2 != nil {
		return uniq(append(rs.matchesSeq(r.seq1, msg), rs.matchesSeq(r.seq2, msg)...))
	}
	return rs.matchesSeq(r.seq1, msg)
}

func (rs ruleset) matchesSeq(seq []int, msg string) []string {
	if len(seq) == 0 {
		return []string{msg}
	}

	m := []string{}
	for _, rest := range rs.matches(seq[0], msg) {
		m = append(m, rs.matchesSeq(seq[1:], rest)...)
	}

	return uniq(m)
}

func uniq(ss []string) []string {
	r := []string{}
	sort.Strings(ss)
	for i := range ss {
		if i == 0 || ss[i-1] != ss[i] {
			r = append(r, ss[i])
		}
	}
	return r
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

	fmt.Printf("loaded %d rules and %d messages\n", len(ruleMap), len(messages))
	//for _, r := range rules {
	//fmt.Printf("%+v\n", r)
	//}

	count := 0
	for _, msg := range messages {
		ms := rules.matches(0, msg)
		for _, m := range ms {
			if m == "" {
				count++
				break
			}
		}
	}
	fmt.Println(count)
}
