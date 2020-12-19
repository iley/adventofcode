package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
)

const steps = 6

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

func (g *grid) activeCount() int {
	return len(g.m)
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
		y++
	}
	return g
}

func neighbours(g *grid, x, y, z int) int {
	n := 0
	for dx := -1; dx <= 1; dx++ {
		for dy := -1; dy <= 1; dy++ {
			for dz := -1; dz <= 1; dz++ {
				if dx == 0 && dy == 0 && dz == 0 {
					continue
				}

				if g.get(x+dx, y+dy, z+dz) {
					n++
				}
			}
		}
	}
	return n
}

func step(g *grid) *grid {
	ng := newGrid()
	for x := g.minx - 1; x <= g.maxx+1; x++ {
		for y := g.miny - 1; y <= g.maxy+1; y++ {
			for z := g.minz - 1; z <= g.maxz+1; z++ {
				n := neighbours(g, x, y, z)
				if n == 3 {
					ng.set(x, y, z, true)
				} else if n == 2 {
					ng.set(x, y, z, g.get(x, y, z))
				}
			}
		}
	}
	return ng
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

	for i := 0; i < steps; i++ {
		g = step(g)
	}

	answer := g.activeCount()
	fmt.Println(answer)
}
