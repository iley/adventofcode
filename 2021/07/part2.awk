function abs(x) { return x >= 0 ? x : -x }
BEGIN { FS="," }
{
    min = 9999; max = 0
    for (i = 1; i <= NF; i++) {
        if ($i < min) min = $i
        if ($i > max) max = $i
    }
    for (pos = min; pos <= max; pos++) {
        s = 0
        for (i = 1; i <= NF; i++) {
            dist = abs($i - pos)
            s += (dist*dist + dist) / 2
        }
        if (mins == 0 || mins > s) mins = s
    }
    print mins
}
