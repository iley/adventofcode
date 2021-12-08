function incl(a, b,   i) {
    for (i = 1; i <= length(b); i++)
        if (!match(a, substr(b, i, 1)))
            return 0
    return 1
}

function equal(a, b) {
    return length(a) == length(b) && incl(a, b)
}

function missing_char(a, b,    i) {
    for (i = 1; i <= length(a); i++)
        if (!match(b, substr(a, i, 1)))
            return substr(a, i, 1)
}

{
    for (i = 1; i <= 10; i++) {
        if (length($i) == 2) d[1] = $i
        if (length($i) == 4) d[4] = $i
        if (length($i) == 3) d[7] = $i
        if (length($i) == 7) d[8] = $i
    }
    for (i = 1; i <= 10; i++) if (length($i) == 5 && incl($i, d[1])) d[3] = $i
    for (i = 1; i <= 10; i++) if (length($i) == 6 && incl($i, d[3])) d[9] = $i
    wire_b = missing_char(d[9], d[3])
    for (i = 1; i <= 10; i++) if (length($i) == 5 && incl($i, wire_b)) d[5] = $i
    for (i = 1; i <= 10; i++) if (length($i) == 5 && $i != d[3] && $i != d[5]) d[2] = $i
    for (i = 1; i <= 10; i++) if (length($i) == 6 && $i != d[5] && !incl($i, d[1])) d[6] = $i
    for (i = 1; i <= 10; i++) if (length($i) == 6 && $i != d[6] && $i != d[9]) d[0] = $i

    reading = ""
    for (i = 12; i <= NF; i++) {
        for (j in d)
            if (equal($i, d[j])) {
                reading = reading j
                break
            }
    }
    sum += reading
}

END { print sum }
