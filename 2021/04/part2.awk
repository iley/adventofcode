function has_won(board,     x, y, winning_row, winning_col) {
    for (y = 1; y <= height; y++) {
        winning_row = 1
        for (x = 1; x <= height; x++) {
            if (board[x, y] != -1) {
                winning_row = 0
                break
            }
        }

        if (winning_row) {
            return 1
        }
    }

    for (x = 1; x <= width; x++) {
        winning_col = 1
        for (y = 1; y <= height; y++) {
            if (board[x, y] != -1) {
                winning_col = 0
                break
            }
        }

        if (winning_col) {
            return 1
        }
    }

    return 0
}

function score(winning_board, last_number,     x, y, s) {
    for (y = 1; y <= height; y++)
        for (x = 1; x <= width; x++)
            if (winning_board[x, y] != -1)
                s += winning_board[x, y]
    return s * last_number
}

BEGIN { FS = "," }

NR == 1 {
    for (i = 1; i <= NF; i++) {
        numbers[i] = $i
    }
    FS = " "
}

/^$/ {
    nboards++
    y = 0
}

NR > 2 && !/^$/ {
    y++
    for (x = 1; x <= NF; x++) {
        boards[nboards][x, y] = $x
    }
}

END {
    width = x - 1
    height = y

    for (i in numbers) {
        n = numbers[i]

        for (j in boards) {
            for (y = 1; y <= height; y++) {
                for (x = 1; x <= width; x++) {
                    if (boards[j][x, y] == n) {
                        boards[j][x, y] = -1
                    }
                }
            }
        }

        for (j in boards) {
            if (has_won(boards[j])) {
                if (length(boards) == 1) {
                    print score(boards[j], n)
                    exit
                }
                delete boards[j]
            }
        }
    }
}
