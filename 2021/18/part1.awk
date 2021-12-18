function explode(s,   depth, i, startpos, endpos, pair, g, left, right, before, after, number) {
    depth = 0
    for (i = 1; i <= length(s); i++) {
        if (substr(s, i, 1) == "[") depth++
        else if (substr(s, i, 1) == "]") depth--
        if (depth >= 5) break
    }
    if (i > length(s)) return s
    startpos = i
    endpos = startpos - 1 + index(substr(s, startpos), "]")
    before = substr(s, 1, startpos-1)
    pair = substr(s, startpos, endpos-startpos+1)
    after = substr(s, endpos+1)
    match(pair, /\[([0-9]+),([0-9]+)\]/, g)
    left = g[1]; right = g[2]
    if (match(before, /([0-9]+)[^0-9]*$/, g)) {
        number = g[1]
        before = substr(before, 1, RSTART-1) (number+left) substr(before, RSTART+length(number))
    }
    if (match(after, /([0-9]+)/, g)) {
        number = g[1]
        after = substr(after, 1, RSTART-1) (number+right) substr(after, RSTART+length(number))
    }
    return before "0" after
}

function splt(s,    number, pair) {
    if (match(s, /[0-9]{2,}/)) {
        number = substr(s, RSTART, RLENGTH)
        pair = "[" int(number / 2) "," int(number / 2) + number % 2 "]"
        s = substr(s, 1, RSTART-1) pair substr(s, RSTART+RLENGTH)
    }
    return s
}

function magn(s,   g) {
    while (match(s, /\[([0-9]+),([0-9]+)\]/, g)) {
        s = substr(s, 1, RSTART-1) g[1]*3+g[2]*2 substr(s, RSTART+RLENGTH)
    }
    return s
}

function add(x, y,   s, t) {
    s = "[" x "," y "]"
    while (1) {
        t = s
        s = explode(s)
        if (t != s) continue
        s = splt(s)
        if (t != s) continue
        break
    }
    return s
}

NR == 1 { sum = $1 }
NR > 1 { sum = add(sum, $1) }
END {
    print sum
    print magn(sum)
}
