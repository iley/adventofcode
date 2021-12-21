#!/usr/bin/env gawk -M -f

function play(turn, p1, p2, s1, s2,   p1_wins, p2_wins, r1, r2, r3, move, new_s1, new_p1, new_s2, new_p2, ret) {
    if ((turn SUBSEP p1 SUBSEP p2 SUBSEP s1 SUBSEP s2) in memo)
        return memo[turn, p1, p2, s1, s2]

    p1_wins = 0
    p2_wins = 0

    for (r1 = 1; r1 <= 3; r1++) {
        for (r2 = 1; r2 <= 3; r2++) {
            for (r3 = 1; r3 <= 3; r3++) {
                move = r1 + r2 + r3

                if (turn == 0) {
                    new_p1 = (p1 + move) % 10
                    new_s1 = s1 + new_p1 + 1

                    if (new_s1 >= 21) p1_wins++
                    else {
                        split(play(1-turn, new_p1, p2, new_s1, s2), ret)
                        p1_wins += ret[1]
                        p2_wins += ret[2]
                    }
                } else {
                    new_p2 = (p2 + move) % 10
                    new_s2 = s2 + new_p2 + 1

                    if (new_s2 >= 21) p2_wins++
                    else {
                        split(play(1-turn, p1, new_p2, s1, new_s2), ret)
                        p1_wins += ret[1]
                        p2_wins += ret[2]
                    }
                }
            }
        }
    }

    memo[turn, p1, p2, s1, s2] = p1_wins FS p2_wins
    return p1_wins FS p2_wins
}

{ start_pos[NR] = $5 - 1 }

END {
    split(play(0, start_pos[1], start_pos[2], 0, 0), ret)
    print (ret[1] > ret[2]) ? ret[1] : ret[2]
}
