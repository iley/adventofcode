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
	minw, maxw int
}

func newGrid() *grid {
	return &grid{
		m: make(map[string]bool),
	}
}

func (g *grid) set(x, y, z, w int, val bool) {
	key := fmt.Sprintf("%d:%d:%d:%d", x, y, z, w)
	if val {
		g.m[key] = val
		g.updateBounds(x, y, z, w)
	} else {
		delete(g.m, key)
	}
}

func (g *grid) updateBounds(x, y, z, w int) {
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
	if w < g.minw {
		g.minw = w
	}
	if w > g.maxw {
		g.maxw = w
	}
}

func (g *grid) get(x, y, z, w int) bool {
	key := fmt.Sprintf("%d:%d:%d:%d", x, y, z, w)
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
				g.set(x, y, 0, 0, true)
			}
		}
		y++
	}
	return g
}

func neighbours(g *grid, x, y, z, w int) int {
	n := 0
	for dx := -1; dx <= 1; dx++ {
		for dy := -1; dy <= 1; dy++ {
			for dz := -1; dz <= 1; dz++ {
				for dw := -1; dw <= 1; dw++ {
					if dx == 0 && dy == 0 && dz == 0 && dw == 0 {
						continue
					}

					if g.get(x+dx, y+dy, z+dz, w+dw) {
						n++
					}
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
				for w := g.minw - 1; w <= g.maxw+1; w++ {
					n := neighbours(g, x, y, z, w)
					if n == 3 {
						ng.set(x, y, z, w, true)
					} else if n == 2 {
						ng.set(x, y, z, w, g.get(x, y, z, w))
					}
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

	fmt.Printf("loaded grid %dx%dx%dx%d\n",
		(g.maxx - g.minx + 1),
		(g.maxy - g.miny + 1),
		(g.maxz - g.minz + 1),
		(g.maxw - g.minw + 1))

	for i := 0; i < steps; i++ {
		fmt.Printf("step %d\n", i)
		g = step(g)
	}

	answer := g.activeCount()
	fmt.Println(answer)
}
