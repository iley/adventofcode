BEGIN { if (!NSTEPS) NSTEPS = 40 }

/^[A-Z]+$/ {
    template = $1
    for (i = 1; i <= length(template)-1; i++)
        pairs[substr(template, i, 2)]++
}

/->/ { rules[$1] = $3 }

END {
    for (step = 1; step <= NSTEPS; step++) {
        delete new_pairs
        for (pair in pairs) {
            if (rules[pair]) {
                left = substr(pair, 1, 1) rules[pair]
                right = rules[pair] substr(pair, 2, 1)
                new_pairs[left] += pairs[pair]
                new_pairs[right] += pairs[pair]
            } else {
                new_pairs[pair] = pairs[pair]
            }
        }

        delete pairs
        for (pair in new_pairs)
            pairs[pair] = new_pairs[pair]
    }

    freq[substr(template, 1, 1)] # the very first character is not accounted for below
    for (pair in pairs) {
        freq[substr(pair, 2, 1)] += pairs[pair]
    }

    least_common = substr(template, 1, 1)
    most_common = substr(template, 1, 1)
    for (char in freq) {
        if (freq[char] > freq[most_common]) most_common = char
        if (freq[char] < freq[least_common]) least_common = char
    }
    print freq[most_common] - freq[least_common]
}
