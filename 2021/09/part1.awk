BEGIN { FS = "" }

{
    for (x = 1; x <= NF; x++) m[x, NR] = $x
    m[0, NR] = 10; m[NF+1, NR] = 10
}

END {
    maxx = NF; maxy = NR
    for (x = 1; x <= maxx; x++) {
        m[x, 0] = 10; m[x, maxy+1] = 10
    }

    for (y = 1; y <= maxy; y++)
        for (x = 1; x <= maxx; x++)
            if (m[x, y] < m[x-1, y] && m[x, y] < m[x+1, y] && m[x, y] < m[x, y-1] && m[x, y] < m[x, y+1])
                s += m[x, y] + 1
    print s
}
