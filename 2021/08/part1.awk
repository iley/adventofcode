{
    for (i = 12; i <= NF; i++)
        if (length($i) == 2 || length($i) == 4 || length($i) == 3 || length($i) == 7)
            s++
}

END { print s }
