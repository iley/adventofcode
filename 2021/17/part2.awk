function simulate(velx, vely,    x, y) {
    x = 0; y = 0
    while (x <= tx2 && y >= ty1) {
        x += velx
        y += vely

        if (velx > 0) velx -= 1
        else if (velx < 0) velx += 1

        vely -= 1

        if (tx1 <= x && x <= tx2 && ty1 <= y && y <= ty2)
            return 1
    }
    return 0
}

match($0, /target area: x=(.*)\.\.(.*), y=(.*)\.\.(.*)/, a) {
    tx1 = a[1]; tx2 = a[2]; ty1 = a[3]; ty2 = a[4]

    for (velx = 1; velx <= tx2; velx++)
        for (vely = ty1; vely <= 1000; vely++) {
            s += simulate(velx, vely)
        }

    print s
}
