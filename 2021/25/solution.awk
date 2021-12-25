function step() {
    nmoved = 0
    delete tmpmap
    for (row = 0; row < nrows; row++) {
        for (col = 0; col < ncols; col++) {
            if (map[row, col] == ">") {
                if (map[row, (col + 1) % ncols] == ".") {
                    tmpmap[row, col] = "."
                    tmpmap[row, (col + 1) % ncols] = ">"
                    nmoved++
                }
                else
                    tmpmap[row, col] = ">"
            }
        }
    }
    for (row = 0; row < nrows; row++)
        for (col = 0; col < ncols; col++)
            if (!tmpmap[row, col])
                tmpmap[row, col] = map[row, col]
    delete map
    for (row = 0; row < nrows; row++) {
        for (col = 0; col < ncols; col++) {
            if (tmpmap[row, col] == "v") {
                if (tmpmap[(row + 1) % nrows, col] == ".") {
                    map[row, col] = "."
                    map[(row + 1) % nrows, col] = "v"
                    nmoved++
                }
                else
                    map[row, col] = "v"
            }
        }
    }
    for (row = 0; row < nrows; row++)
        for (col = 0; col < ncols; col++)
            if (!map[row, col])
                map[row, col] = tmpmap[row, col]
}

function printmap() {
    for (row = 0; row < nrows; row++) {
        for (col = 0; col < ncols; col++) printf("%s", map[row, col])
        printf("\n")
    }
}

BEGIN { FS = "" }

{
    for (i = 1; i <= NF; i++) {
        map[NR-1, i-1] = $i
    }
}

END {
    nrows = NR; ncols = NF
    nsteps = 0

    print "Initial state:"
    printmap()
    print ""

    do {
        step()
        nsteps++
        print "After " nsteps " steps:"
        printmap()
        print "Moved: " nmoved
        print ""
    } while (nmoved > 0)

    print "Answer: " nsteps
}
