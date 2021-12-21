{ p[NR-1] = $5-1 }

END {
    delete score
    while (1) {
        for (pn = 0; pn < 2; pn++) {
            roll = 3 * die + 6
            die += 3
            p[pn] = (p[pn] + roll) % 10
            score[pn] += p[pn] + 1

            printf("player %d rolls %d and moves to %d total score %d\n", pn, roll, p[pn]+1, score[pn])

            if (score[pn] >= 1000) {
                print score[1-pn] * die
                exit
            }
        }
    }
}
