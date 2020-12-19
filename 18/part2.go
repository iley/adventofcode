package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"
)

type expr struct {
	op    byte
	left  *expr
	right *expr
	val   int
	str   string
}

func load(input io.Reader) []*expr {
	es := []*expr{}
	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		line := scanner.Text()
		line = cleanStr(line)
		e := parseExpr(line)
		es = append(es, e)
	}
	return es
}

func cleanStr(s string) string {
	r := ""
	for i := 0; i < len(s); i++ {
		if charOneOf(s[i], "0123456789()+-*") {
			r = fmt.Sprintf("%s%c", r, s[i])
		}
	}
	return r
}

func parseExpr(s string) *expr {
	// fmt.Printf("parsing '%s'\n", s)
	level := 0
	for i := len(s) - 1; i >= 0; i-- {
		c := s[i]
		if c == ')' {
			level++
		} else if c == '(' {
			level--
		} else if level == 0 && c == '*' {
			return &expr{
				str:   s,
				op:    c,
				left:  parseExpr(s[0:i]),
				right: parseExpr(s[i+1:]),
			}
		}
	}

	level = 0
	for i := len(s) - 1; i >= 0; i-- {
		c := s[i]
		if c == ')' {
			level++
		} else if c == '(' {
			level--
		} else if level == 0 && charOneOf(c, "+-") {
			return &expr{
				str:   s,
				op:    c,
				left:  parseExpr(s[0:i]),
				right: parseExpr(s[i+1:]),
			}
		}
	}

	if s[0] == '(' {
		return parseExpr(s[1 : len(s)-1])
	}

	n, err := strconv.ParseInt(s, 10, 32)
	if err != nil {
		panic(err)
	}

	return &expr{str: s, val: int(n)}
}

func eval(e *expr) int {
	if e.op == '+' {
		return eval(e.left) + eval(e.right)
	}
	if e.op == '-' {
		return eval(e.left) - eval(e.right)
	}
	if e.op == '*' {
		return eval(e.left) * eval(e.right)
	}
	if e.op == '/' {
		return eval(e.left) / eval(e.right)
	}
	return e.val
}

func charOneOf(ch byte, s string) bool {
	return strings.IndexByte(s, ch) != -1
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

	exprs := load(input)
	fmt.Printf("loaded %d expressions\n", len(exprs))

	s := int64(0)
	for _, e := range exprs {
		res := eval(e)
		fmt.Printf("%s = %d\n", e.str, res)
		s += int64(res)
	}

	fmt.Println(s)

}
