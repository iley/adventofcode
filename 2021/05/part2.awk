function step(a, b) {
    if (a == b) return 0
    else if (a < b) return 1
    else return -1
}

BEGIN { FS = "[, ]" }

{
    x1 = $1; y1 = $2; x2 = $4; y2 = $5
    x = x1; y = y1
    while (x != x2 || y != y2) {
        map[x, y]++
        x += step(x1, x2)
        y += step(y1, y2)
    }
    map[x2, y2]++
}

END {
    for (idx in map)
        if (map[idx] > 1)
            sum++
    print sum
}
