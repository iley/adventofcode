function most_common_bit(numbers, pos,    i, ones, zeroes) {
    for (i in numbers) {
        if (substr(numbers[i], pos, 1) == 1) ones++;
        else zeroes++;
    }
    if (ones == zeroes) return 1;
    else if (ones > zeroes) return 1;
    else return 0
}

function least_common_bit(numbers, pos,    i, ones, zeroes) {
    for (i in numbers) {
        if (substr(numbers[i], pos, 1) == 1) ones++;
        else zeroes++;
    }
    if (ones == zeroes) return 0;
    else if (ones < zeroes) return 1;
    else return 0
}

function o2_rating(numbers,    pos, i, remaining) {
    for (i in numbers) remaining[i] = numbers[i]
    for (pos = 1; pos <= NR; pos++) {
        bit = most_common_bit(remaining, pos)
        for (i in remaining) {
            if (substr(remaining[i], pos, 1) != bit) {
                delete remaining[i]
            }
        }
        if (length(remaining) == 1)
            for (i in remaining)
                return remaining[i]
    }
    # Should never get here.
}

function co2_rating(numbers,    remaining, pos, i) {
    for (i in numbers) remaining[i] = numbers[i]
    for (pos = 1; pos <= NR; pos++) {
        bit = least_common_bit(remaining, pos)
        for (i in remaining) {
            if (substr(remaining[i], pos, 1) != bit) {
                delete remaining[i]
            }
        }
        if (length(remaining) == 1)
            for (i in remaining)
                return remaining[i]
    }
    # Should never get here.
}

function parsebin(bin,    res, i) {
    res = 0
    for (i = 1; i <= length(bin); i++) {
        res = res * 2 + substr(bin, i, 1)
    }
    return res
}

{
    numbers[NR] = $0
}

END {
    o2 = o2_rating(numbers)
    co2 = co2_rating(numbers)
    print parsebin(o2) * parsebin(co2)
}
