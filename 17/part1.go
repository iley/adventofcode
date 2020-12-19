package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
)

type grid struct {
	m          map[string]bool
	minx, maxx int
	miny, maxy int
	minz, maxz int
}

func newGrid() *grid {
	return &grid{
		m: make(map[string]bool),
	}
}

func (g *grid) set(x, y, z int, val bool) {
	key := fmt.Sprintf("%d:%d:%d", x, y, z)
	if val {
		g.m[key] = val
		if x < g.minx {
			g.minx = x
		}
		if x > g.maxx {
			g.maxx = x
		}
		if y < g.miny {
			g.miny = y
		}
		if y > g.maxy {
			g.maxy = y
		}
		if z < g.minz {
			g.minz = z
		}
		if z > g.maxz {
			g.maxz = z
		}
	} else {
		delete(g.m, key)
	}
}

func (g *grid) get(x, y, z int) bool {
	key := fmt.Sprintf("%d:%d:%d", x, y, z)
	return g.m[key]
}

func load(input io.Reader) *grid {
	g := newGrid()
	scanner := bufio.NewScanner(input)
	y := 0
	for scanner.Scan() {
		line := scanner.Text()
		for x := 0; x < len(line); x++ {
			if line[x] == '#' {
				g.set(x, y, 0, true)
			}
		}
	}
	return g
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

	g := load(input)

	fmt.Printf("loaded grid %dx%dx%d\n", (g.maxx - g.minx + 1), (g.maxy - g.miny + 1), (g.maxz - g.minz + 1))

}
