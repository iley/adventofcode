function floodfill(x, y) {
    if (m[x, y] >= 9) return 0
    m[x, y] = 10
    return 1 + floodfill(x+1, y) + floodfill(x-1, y) + floodfill(x, y+1) + floodfill(x, y-1)
}

BEGIN {
    FS = ""
    delete poolsizes
}

{
    for (x = 1; x <= NF; x++) m[x, NR] = $x
    m[0, NR] = 9; m[NF+1, NR] = 9
}

END {
    maxx = NF; maxy = NR
    for (x = 1; x <= maxx; x++) {
        m[x, 0] = 9; m[x, maxy+1] = 9
    }

    for (x = 1; x <= maxx; x++) {
        for (y = 1; y <= maxy; y++) {
            if (map[x, y] < 9) {
                size = floodfill(x, y)
                poolsizes[length(poolsizes)+1] = size
            }
        }
    }

    asort(poolsizes)
    len = length(poolsizes)
    print poolsizes[len] * poolsizes[len-1] * poolsizes[len-2]
}
