BEGIN { FS="," }

{
    for (i = 1; i <= NF; i++) fish[$i]++
    for (day = 1; day <= 80; day++) {
        new[8] = fish[0]
        new[6] = fish[0]
        for (i = 1; i <= 8; i++)
            new[i-1] += fish[i]
        delete fish
        for (i in new) fish[i] = new[i]
        delete new
    }
    for (i in fish) s += fish[i]
    print s
}
