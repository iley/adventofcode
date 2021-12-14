/^[A-Z]+$/ { split($1, poly, "") }
/->/ { rules[$1] = $3 }

END {
    for (step = 1; step <= 10; step++) {
        delete next_poly
        next_poly[1] = poly[1]
        for (i = 2; i <= length(poly); i++) {
            pair = poly[i-1] poly[i]
            if (rules[pair])
                next_poly[length(next_poly)+1] = rules[pair]
            next_poly[length(next_poly)+1] = poly[i]
        }

        delete poly
        for (i in next_poly) poly[i] = next_poly[i]
    }

    for (i in poly) {
        freq[poly[i]]++
    }

    least_common = poly[1]
    most_common = poly[1]
    for (char in freq) {
        if (freq[char] > freq[most_common]) most_common = char
        if (freq[char] < freq[least_common]) least_common = char
    }
    print freq[most_common] - freq[least_common]
}
