BEGIN { FS="" }

{
    for (i = 1; i <= NF; i++) {
        if ($i == 1) ones[i]++
        else zeroes[i]++
    }
}

END {
    gamma = 0
    epsilon = 0
    for (i = 1; i <= NF; i++) {
        digit = ones[i] > zeroes[i] ? 1 : 0
        gamma = gamma * 2 + digit
        epsilon = epsilon * 2 + 1 - digit
    }
    print gamma * epsilon
}
