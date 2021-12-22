BEGIN { delete map }

match($0, /(on|off) x=(.+)\.\.(.+),y=(.+)\.\.(.+),z=(.+)\.\.(.+)/, grp) {
    x1 = grp[2]; x2 = grp[3]; y1 = grp[4]; y2 = grp[5]; z1 = grp[6]; z2 = grp[7]
    if (x1 < -50 && x2 < -50 || x1 > 50 && x2 > 50 || y1 < -50 && y2 < -50 || y1 > 50 && y2 > 50 || z1 < -50 && z2 < -50 || z1 > 50 && z2 > 50)
        next
    op = grp[1] == "on" ? 1 : 0

    for (x = x1; x <= x2; x++)
        for (y = y1; y <= y2; y++)
            for (z = z1; z <= z2; z++)
                if (op) map[x, y, z] = 1
                else delete map[x, y, z]
}

END {
    for (x = -50; x <= 50; x++)
        for (y = -50; y <= 50; y++)
            for (z = -50; z <= 50; z++)
                if ((x SUBSEP y SUBSEP z) in map)
                    s++

    print s
}
