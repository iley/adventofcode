package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

type image [][]byte

func load(input io.Reader) [][]byte {
	m := [][]byte{}

	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())

		row := []byte{}
		for _, ch := range line {
			if ch == '.' {
				row = append(row, 0)
			} else if ch == '#' {
				row = append(row, 1)
			}
		}
		if len(row) > 0 {
			m = append(m, row)
		}
	}
	return m
}

func imageVariants(t [][]byte) []image {
	vars := []image{}
	for _, tm := range []image{t, mirrorVertical(t), mirrorHorizontal(t), mirrorVertical(mirrorHorizontal(t))} {
		vars = append(vars, imageRotatations(tm)...)
	}
	return vars
}

func imageRotatations(t image) []image {
	r1 := rotRight(t)
	r2 := rotRight(r1)
	r3 := rotRight(r2)
	return []image{t, r1, r2, r3}
}

func rotRight(t image) image {
	side := len(t)
	tr := copyimage(t)
	for r := 0; r < side; r++ {
		for c := 0; c < side; c++ {
			tr[c][side-1-r] = t[r][c]
		}
	}
	return tr
}

func mirrorVertical(t image) image {
	m := copyimage(t)
	for i := range t {
		for j := range t[i] {
			m[i][j] = t[i][len(t[i])-1-j]
		}
	}
	return m
}

func mirrorHorizontal(t image) image {
	m := copyimage(t)
	for i := 0; i < len(t)/2; i++ {
		m[i], m[len(m)-1-i] = m[len(m)-1-i], m[i]
	}
	return m
}

func copyimage(t image) image {
	tc := make(image, len(t))
	for i := range t {
		tc[i] = make([]byte, len(t[i]))
		for j := range t[i] {
			tc[i][j] = t[i][j]
		}
	}
	return tc
}

func findMonsters(img image) (image, int) {
	cimg := copyimage(img)
	c := 0
	for row := 0; row < len(img); row++ {
		for col := 0; col < len(img[0]); col++ {
			if match(img, row, col) {
				mark(cimg, row, col)
				c++
			}
		}
	}
	return cimg, c
}

func match(img image, row, col int) bool {
	if row+2 >= len(img) || col+19 >= len(img[0]) {
		return false
	}
	return img[row][col+18] == 1 &&
		img[row+1][col] == 1 &&
		img[row+1][col+5] == 1 &&
		img[row+1][col+6] == 1 &&
		img[row+1][col+11] == 1 &&
		img[row+1][col+12] == 1 &&
		img[row+1][col+17] == 1 &&
		img[row+1][col+18] == 1 &&
		img[row+1][col+19] == 1 &&
		img[row+2][col+1] == 1 &&
		img[row+2][col+4] == 1 &&
		img[row+2][col+7] == 1 &&
		img[row+2][col+10] == 1 &&
		img[row+2][col+13] == 1 &&
		img[row+2][col+16] == 1
}

func mark(img image, row, col int) {
	img[row][col+18] = 2
	img[row+1][col] = 2
	img[row+1][col+5] = 2
	img[row+1][col+6] = 2
	img[row+1][col+11] = 2
	img[row+1][col+12] = 2
	img[row+1][col+17] = 2
	img[row+1][col+18] = 2
	img[row+1][col+19] = 2
	img[row+2][col+1] = 2
	img[row+2][col+4] = 2
	img[row+2][col+7] = 2
	img[row+2][col+10] = 2
	img[row+2][col+13] = 2
	img[row+2][col+16] = 2
}

func printImage(img image) {
	for _, row := range img {
		for _, dot := range row {
			if dot == 1 {
				fmt.Print("#")
			} else if dot == 2 {
				fmt.Print("O")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println()
	}
}

func waterCount(img image) int {
	c := 0
	for _, row := range img {
		for _, dot := range row {
			if dot == 1 {
				c++
			}
		}
	}
	return c
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

	image := load(input)

	fmt.Printf("loaded image %dx%d\n", len(image), len(image[0]))

	vars := imageVariants(image)
	fmt.Printf("found %d image variants\n", len(vars))

	for i, img := range vars {
		newImg, n := findMonsters(img)
		if n > 0 {
			fmt.Printf("found %d monsters in image variant %d\n", n, i)
			printImage(newImg)
			fmt.Println(waterCount(newImg))
			break
		}
	}
}
