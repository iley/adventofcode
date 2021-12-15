BEGIN { FS="" }
{
    for (i = 1; i <= NF; i++) map[NR, i] = $i
}
END {
    for (row = 2; row <= NR; row++) map[row, 1] += map[row-1, 1]
    for (col = 2; col <= NF; col++) map[1, col] += map[1, col-1]
    for (row = 2; row <= NR; row++)
        for (col = 2; col <= NF; col++)
            if (map[row-1, col] < map[row, col-1]) map[row, col] += map[row-1, col]
            else map[row, col] += map[row, col-1]
    print map[NR, NF] - map[1, 1]
}
