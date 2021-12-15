function update_dist(pos) {
    if (!(pos in unvisited) || !(pos in map)) return
    if (dist[current] + map[pos] < dist[pos]) {
        dist[pos] = dist[current] + map[pos]
        candidates[pos] = 1
    }
}

BEGIN { FS="" }

{
    for (i = 1; i <= NF; i++) map[NR, i] = $i
}

END {
    maxrow = 5 * NR
    maxcol = 5 * NF

    for (tilerow = 0; tilerow < 5; tilerow++)
        for (tilecol = 0; tilecol < 5; tilecol++)
            for (row = 1; row <= NR; row++)
                for (col = 1; col <= NF; col++) {
                    val = map[row, col] + tilerow + tilecol
                    map[tilerow*NR+row, tilecol*NF+col] = val > 9 ? val - 9 : val
                }

    for (row = 1; row <= maxrow; row++)
        for (col = 1; col <= maxcol; col++) {
            dist[row, col] = 999999
            unvisited[row, col] = 1
        }
    dist[1, 1] = 0

    current = 1 SUBSEP 1
    while (current != (maxrow SUBSEP maxcol)) {
        split(current, curcoord, SUBSEP)

        update_dist(curcoord[1]-1 SUBSEP curcoord[2])
        update_dist(curcoord[1]+1 SUBSEP curcoord[2])
        update_dist(curcoord[1] SUBSEP curcoord[2]-1)
        update_dist(curcoord[1] SUBSEP curcoord[2]+1)

        delete unvisited[current]
        delete candidates[current]

        current = ""
        for (unv in candidates)
            if (current == "" || dist[unv] < dist[current]) {
                current = unv
            }
    }

    print dist[maxrow, maxcol]
}
