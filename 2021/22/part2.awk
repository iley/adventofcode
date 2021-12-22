BEGIN { delete cubes }

function cut(val, axis,    newcubes, cube, c) {
    delete newcubes
    for (cube in cubes) {
        split(cube, c, SUBSEP)

        if (!(x2 >= c[1] && c[2] >= x1 &&
              y2 >= c[3] && c[4] >= y1 &&
              z2 >= c[5] && c[6] >= z1)) {
            newcubes[cube] = 1
            continue
        }

        if (axis == "x") {
            if (c[1] < val && c[2] >= val) {
                newcubes[c[1], val-1, c[3], c[4], c[5], c[6]] = 1
                newcubes[val, c[2], c[3], c[4], c[5], c[6]] = 1
            } else {
                newcubes[cube] = 1
            }
        } else if (axis == "y") {
            if (c[3] < val && c[4] >= val) {
                newcubes[c[1], c[2], c[3], val-1, c[5], c[6]] = 1
                newcubes[c[1], c[2], val, c[4], c[5], c[6]] = 1
            } else {
                newcubes[cube] = 1
            }
        } else {
            if (c[5] < val && c[6] >= val) {
                newcubes[c[1], c[2], c[3], c[4], c[5], val-1] = 1
                newcubes[c[1], c[2], c[3], c[4], val, c[6]] = 1
            } else {
                newcubes[cube] = 1
            }
        }
    }
    delete cubes
    for (cube in newcubes)
        cubes[cube] = newcubes[cube]
}

match($0, /(on|off) x=(.+)\.\.(.+),y=(.+)\.\.(.+),z=(.+)\.\.(.+)/, grp) {
    # print NR ": " $0

    x1 = grp[2]; x2 = grp[3]; y1 = grp[4]; y2 = grp[5]; z1 = grp[6]; z2 = grp[7]
    turnon = grp[1] == "on" ? 1 : 0

    cut(x1, "x"); cut(x2+1, "x")
    cut(y1, "y"); cut(y2+1, "y")
    cut(z1, "z"); cut(z2+1, "z")

    delete newcubes
    for (cube in cubes) {
        split(cube, c, SUBSEP)
        if (c[1] >= x1 && c[2] <= x2 &&
            c[3] >= y1 && c[4] <= y2 &&
            c[5] >= z1 && c[6] <= z2) {
            continue
        } else
            newcubes[cube] = 1
    }

    delete cubes
    for (cube in newcubes)
        cubes[cube] = newcubes[cube]

    if (turnon)
        cubes[x1,x2,y1,y2,z1,z2] = 1
}

END {
    s = 0
    for (cube in cubes) {
        split(cube, c, SUBSEP)
        s += (c[2] - c[1] + 1) * (c[4] - c[3] + 1) * (c[6] - c[5] + 1)
    }
    print s
}
