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
	"time"
)

const (
	TOP    = 0
	RIGHT  = 1
	BOTTOM = 2
	LEFT   = 3
)

var (
	tileStartRe = regexp.MustCompile(`Tile (\d+)+:`)
)

type tile [][]byte

type tileInfo struct {
	variants  []tile
	borderIds [][]int
}

type tileRef struct {
	id    int
	tinfo tileInfo
	varid int
}

func makeTileInfo(t tile) tileInfo {
	vars := tileVariants(t)
	bids := make([][]int, len(vars))
	for i, v := range vars {
		bids[i] = borderIds(v)
	}
	return tileInfo{
		variants:  vars,
		borderIds: bids,
	}
}

func copyTile(t tile) tile {
	tc := make(tile, len(t))
	for i := range t {
		tc[i] = make([]byte, len(t[i]))
		for j := range t[i] {
			tc[i][j] = t[i][j]
		}
	}
	return tc
}

func tileVariants(t tile) []tile {
	vars := []tile{}
	for _, tm := range []tile{t, mirrorVertical(t), mirrorHorizontal(t), mirrorVertical(mirrorHorizontal(t))} {
		vars = append(vars, tileRotatations(tm)...)
	}
	return vars
}

func tileRotatations(t tile) []tile {
	r1 := rotRight(t)
	r2 := rotRight(r1)
	r3 := rotRight(r2)
	return []tile{t, r1, r2, r3}
}

func rotRight(t tile) tile {
	side := len(t)
	tr := copyTile(t)
	for r := 0; r < side; r++ {
		for c := 0; c < side; c++ {
			tr[c][side-1-r] = t[r][c]
		}
	}
	return tr
}

func mirrorVertical(t tile) tile {
	m := copyTile(t)
	for i := range t {
		for j := range t[i] {
			m[i][j] = t[i][len(t[i])-1-j]
		}
	}
	return m
}

func mirrorHorizontal(t tile) tile {
	m := copyTile(t)
	for i := 0; i < len(t)/2; i++ {
		m[i], m[len(m)-1-i] = m[len(m)-1-i], m[i]
	}
	return m
}

func borderIds(t tile) []int {
	return []int{
		borderId(topBorder(t)),
		borderId(rightBorder(t)),
		borderId(bottomBorder(t)),
		borderId(leftBorder(t)),
	}
}

func borderId(row []byte) int {
	id := 0
	for _, c := range row {
		id = id << 1
		if c != 0 {
			id = id | 1
		}
	}
	return id
}

func topBorder(t tile) []byte {
	return t[0]
}

func rightBorder(t tile) []byte {
	res := []byte{}
	for _, r := range t {
		res = append(res, r[len(r)-1])
	}
	return res
}

func bottomBorder(t tile) []byte {
	return t[len(t)-1]
}

func leftBorder(t tile) []byte {
	res := []byte{}
	for _, r := range t {
		res = append(res, r[0])
	}
	return res
}

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
		printTile(t)
		fmt.Println()
	}
}

func printTile(t tile) {
	for _, row := range t {
		fmt.Println(row)
	}
}

func makeField(size int) [][]*tileRef {
	f := make([][]*tileRef, size)
	for i := 0; i < size; i++ {
		f[i] = make([]*tileRef, size)
	}
	return f
}

func copyField(f [][]*tileRef, size int) [][]*tileRef {
	c := makeField(size)
	for i := 0; i < size; i++ {
		for j := 0; j < size; j++ {
			c[i][j] = f[i][j]
		}
	}
	return c
}

func fitTiles(tiles map[int]tile, size, hint int) [][]*tileRef {
	f := makeField(size)

	tinfos := make(map[int]tileInfo)
	for id := range tiles {
		tinfos[id] = makeTileInfo(tiles[id])
	}

	idx := neighbourIndex(tinfos)

	f, ok := tryFit(f, 0, 0, size, tinfos, idx, hint)
	if !ok {
		fmt.Println("could not fit tiles")
	}

	return f
}

var lastUpdate time.Time

func tryFit(field [][]*tileRef, row, col, size int, tinfos map[int]tileInfo, index map[int][]int, hint int) ([][]*tileRef, bool) {
	if row >= size || col >= size {
		return field, true
	}

	nextRow := row
	nextCol := col + 1
	if nextCol >= size {
		nextRow++
		nextCol = 0
	}

	neighbourFilter := map[int]bool{}
	if row > 0 {
		neighbour := field[row-1][col]
		for _, id := range index[neighbour.id] {
			neighbourFilter[id] = true
		}
	}
	if col > 0 {
		neighbour := field[row][col-1]
		for _, id := range index[neighbour.id] {
			neighbourFilter[id] = true
		}
	}

	for tileid, tinfo := range tinfos {
		if hint > 0 && row == 0 && col == 0 && tileid != hint {
			continue
		}

		if len(neighbourFilter) > 0 && !neighbourFilter[tileid] {
			continue
		}

		// exclude current tile
		nextTinfos := make(map[int]tileInfo)
		for k, v := range tinfos {
			if k != tileid {
				nextTinfos[k] = v
			}
		}

		for varid := 0; varid < len(tinfo.variants); varid++ {
			tr := &tileRef{id: tileid, tinfo: tinfo, varid: varid}
			if !fits(field, row, col, size, tr) {
				continue
			}

			nextField := copyField(field, size)
			nextField[row][col] = tr

			f, ok := tryFit(nextField, nextRow, nextCol, size, nextTinfos, index, hint)
			if ok {
				return f, true
			}
		}
	}

	return field, false
}

func fits(field [][]*tileRef, row, col, size int, tr *tileRef) bool {
	bids := tr.tinfo.borderIds[tr.varid]
	if row > 0 {
		upper := field[row-1][col]
		if upper != nil && bids[TOP] != upper.tinfo.borderIds[upper.varid][BOTTOM] {
			return false
		}
	}
	if col > 0 {
		left := field[row][col-1]
		if left != nil && bids[LEFT] != left.tinfo.borderIds[left.varid][RIGHT] {
			return false
		}
	}
	//if col < size-1 {
	//right := field[row][col+1]
	//if right != nil && bids[RIGHT] != right.tinfo.borderIds[right.varid][LEFT] {
	//return false
	//}
	//}
	//if row < size-1 {
	//lower := field[row+1][col]
	//if lower != nil && bids[BOTTOM] != lower.tinfo.borderIds[lower.varid][TOP] {
	//return false
	//}
	//}
	return true
}

func printField(field [][]*tileRef, size int) {
	for row := 0; row < size; row++ {
		for col := 0; col < size; col++ {
			if field[row][col] == nil {
				fmt.Print("X    ")
			} else {
				fmt.Printf("%d ", field[row][col].id)
			}
		}
		fmt.Println()
	}
}

func neighbourIndex(tinfos map[int]tileInfo) map[int][]int {
	idx := map[int][]int{}
	for id1, tinfo1 := range tinfos {
		for id2, tinfo2 := range tinfos {
			if haveCommonBorder(tinfo1, tinfo2) {
				idx[id1] = append(idx[id1], id2)
				idx[id2] = append(idx[id2], id1)
			}
		}
	}
	return idx
}

func haveCommonBorder(ti1, ti2 tileInfo) bool {
	bidMap := make(map[int]bool)
	for _, bids := range ti1.borderIds {
		for _, bid := range bids {
			bidMap[bid] = true
		}
	}
	for _, bids := range ti2.borderIds {
		for _, bid := range bids {
			if bidMap[bid] {
				return true
			}
		}
	}
	return false
}

func main() {
	if len(os.Args) < 3 {
		fmt.Fprintf(os.Stderr, "Usage: %s FILE\n", os.Args[0])
		os.Exit(1)
	}

	inputPath := os.Args[1]

	i64, err := strconv.ParseInt(os.Args[2], 10, 32)
	if err != nil {
		log.Fatal(err)
	}

	// field size in tiles
	size := int(i64)

	hint := 0
	if len(os.Args) >= 4 {
		i64, err := strconv.ParseInt(os.Args[3], 10, 32)
		if err != nil {
			log.Fatal(err)
		}
		hint = int(i64)
	}

	input, err := os.Open(inputPath)
	if err != nil {
		log.Fatal(err)
	}
	defer input.Close()

	tiles := load(input)
	// fmt.Printf("loaded %d tiles, field size %d\n", len(tiles), size)

	if size*size != len(tiles) {
		log.Fatalf("wrong size or tile #")
	}

	f := fitTiles(tiles, size, hint)

	tileInnerSize := 8
	imgRows := tileInnerSize * size
	imgCols := tileInnerSize * size

	for row := 0; row < imgRows; row++ {
		for col := 0; col < imgCols; col++ {
			tr := f[row/tileInnerSize][col/tileInnerSize]
			t := tr.tinfo.variants[tr.varid]
			if t[row%tileInnerSize+1][col%tileInnerSize+1] == 0 {
				fmt.Print(".")
			} else {
				fmt.Print("#")
			}
		}
		fmt.Println()
	}
}
