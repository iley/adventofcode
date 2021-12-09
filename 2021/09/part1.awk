BEGIN { FS = "" }

{
    for (i = 1; i <= NF; i++) m[NR, i] = $i
    m[NR, 0] = 10; m[NR, NF+1] = 10
}

END {
    maxx = NF; maxy = NR
    print "maxx = " maxx " maxy = " maxy
    for (x = 1; x <= maxx; x++) {
        m[0, x] = 10; m[maxy+1, x] = 10
    }

    for (y = 1; y <= maxy; y++)
        for (x = 1; x <= maxx; x++)
            if (m[y, x] < m[y, x-1] && m[y, x] < m[y, x+1] && m[y, x] < m[y-1, x] && m[y, x ] < m[y+1, x])
                s += m[y, x] + 1
    print s
}
