BEGIN {
    pair["("] = ")"; pair["["] = "]"; pair["{"] = "}"; pair["<"] = ">"
    score[")"] = 3; score["]"] = 57; score["}"] = 1197; score[">"] = 25137
    FS = ""
}
{
    delete stack
    for (i = 1; i <= NF; i++) {
        if (pair[$i]) {
            stack[length(stack)+1] = $i
        } else {
            open = stack[length(stack)]; delete stack[length(stack)]
            if (pair[open] != $i) {
                print "expected " pair[open] " but found " $i
                total_score += score[$i]
                next
            }
        }
    }
}

END { print total_score }
