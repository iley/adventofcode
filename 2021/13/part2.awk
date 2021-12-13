BEGIN { FS="[ =,]" }

/[0-9]+,[0-9]+/ {
    map[$1, $2] = 1
    if ($1 > maxx) maxx = $1
    if ($2 > maxy) maxy = $2
}

/fold/ {
    if ($3 == "x") {
        for (y = 0; y <= maxy; y++)
            for (x = 0; x < $4; x++)
                if (map[maxx-x, y]) map[x, y] = 1
        maxx = $4 - 1
    } else {
        for (y = 0; y < $4; y++)
            for (x = 0; x <= maxx; x++)
                if (map[x, maxy-y]) map[x, y] = 1
        maxy = $4 - 1
    }
    for (x = 0; x <= maxx; x++)
        for (y = 0; y <= maxy; y++)
            s += map[x, y]
}

END {
    for (y = 0; y <= maxy; y++) {
        for (x = 0; x <= maxx; x++)
            printf("%s", map[x,y] ? "#" : ".")
        printf("\n")
    }
}
