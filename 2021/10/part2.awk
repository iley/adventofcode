BEGIN {
    pair["("] = ")"; pair["["] = "]"; pair["{"] = "}"; pair["<"] = ">"
    score[")"] = 1; score["]"] = 2; score["}"] = 3; score[">"] = 4
    FS = ""
    delete scores
}
{
    delete stack
    for (i = 1; i <= NF; i++) {
        if (pair[$i]) {
            stack[length(stack)+1] = $i
        } else {
            open = stack[length(stack)]; delete stack[length(stack)]
            if (pair[open] != $i) {
                next
            }
        }
    }
    line_score = 0
    for (i = length(stack); i > 0; i--) {
        missing = pair[stack[i]]
        printf("%s", missing)
        line_score = line_score * 5 + score[missing]
    }
    printf(" %d\n", line_score)
    scores[length(scores)+1] = line_score
}

END {
    asort(scores)
    print "middle score = " scores[(length(scores)+1)/2]
}
