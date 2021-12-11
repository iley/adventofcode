BEGIN { FS = "" }
{ for (i = 1; i <= NF; i++) map[NR, i] = $i }
END {
    step = 0
    do {
        step++
        total_flashes = 0

        for (i = 1; i <= NR; i++)
            for (j = 1; j <= NF; j++)
                map[i, j]++
        
        do {
            flashes = 0
            for (i = 1; i <= NR; i++)
                for (j = 1; j <= NF; j++)
                    if (map[i, j] > 9) {
                        map[i, j] = 0
                        flashes++
                        for (di = -1; di <= 1; di++)
                            for (dj = -1; dj <= 1; dj++)
                                if (map[i+di, j+dj] != 0)
                                    map[i+di, j+dj]++
                    }
            total_flashes += flashes
        } while (flashes > 0)
    } while (total_flashes != NR * NF)
    print step
}
