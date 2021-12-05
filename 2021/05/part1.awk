function min(a, b) { return a < b ? a : b }
function max(a, b) { return a > b ? a : b }

BEGIN { FS = "[, ]" }

{
    x1 = $1; y1 = $2; x2 = $4; y2 = $5
    if (x1 == x2)
        for (y = min(y1, y2); y <= max(y1, y2); y++)
            map[x1, y]++
    else if (y1 == y2)
        for (x = min(x1, x2); x <= max(x1, x2); x++)
            map[x, y1]++
}

END {
    for (idx in map)
        if (map[idx] > 1)
            sum++
    print sum
}
