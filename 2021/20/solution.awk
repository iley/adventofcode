function read(r, c) {
    if ((r SUBSEP c) in map) return map[r, c]
    else return background
}

function window(r, c) {
    return read(r-1,c-1)*256+read(r-1,c)*128+read(r-1,c+1)*64+read(r,c-1)*32+read(r,c)*16+read(r,c+1)*8+read(r+1,c-1)*4+read(r+1,c)*2+read(r+1,c+1)
}

BEGIN { FS=""; if (!STEPS) STEPS=2 }
NR==1 { for (i = 1; i <= NF; i++) algo[i-1] = ($i == "#") ? 1 : 0 }
NR >= 3 { for (i = 1; i <= NF; i++) if ($i == "#") map[NR-2, i] = 1 }

END {
    minrow = 1; maxrow = NR-2
    mincol = 1; maxcol = NF
    background = 0

    for (step = 1; step <= STEPS; step++) {
        delete newmap
        for (row = minrow-2; row <= maxrow+2; row++)
            for (col = mincol-2; col <= maxcol+2; col++)
                newmap[row, col] = algo[window(row, col)]

        if (background == 0) background = algo[0]
        else background = algo[511]

        for (idx in newmap) {
            split(idx, coords, SUBSEP)
            if (coords[1] < minrow) minrow = coords[1]
            if (coords[1] > maxrow) maxrow = coords[1]
            if (coords[2] < mincol) mincol = coords[2]
            if (coords[2] > maxcol) maxcol = coords[2]
        }

        delete map
        for (idx in newmap)
            map[idx] = newmap[idx]
    }

    for (idx in map) if (map[idx]) sum++
    print sum
}
