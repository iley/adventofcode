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
	tileStartRe = regexp.MustCompile(`Tile (\d+)+:`)
)

type tile [][]byte

func load(input io.Reader) map[int]tile {
	scanner := bufio.NewScanner(input)
	tiles := make(map[int]tile)
	t := tile{}
	tilen := 0
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())

		g := tileStartRe.FindStringSubmatch(line)
		if g != nil {
			n, _ := strconv.ParseInt(g[1], 10, 32)

			if len(t) != 0 {
				tiles[tilen] = t
			}

			t = tile{}
			tilen = int(n)
			continue
		}

		row := []byte{}
		for _, ch := range line {
			if ch == '.' {
				row = append(row, 0)
			} else if ch == '#' {
				row = append(row, 1)
			}
		}
		if len(row) > 0 {
			t = append(t, row)
		}
	}
	// last tile
	if len(t) != 0 {
		tiles[tilen] = t
	}
	return tiles
}

func printTiles(tiles []tile) {
	for n, t := range tiles {
		fmt.Println(n)
		for _, row := range t {
			fmt.Println(row)
		}
		fmt.Println()
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

	tiles := load(input)
	fmt.Printf("loaded %d tiles\n", len(tiles))

}
