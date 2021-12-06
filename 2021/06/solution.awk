# To run: awk -v DAYS=80 -f solution.awk input.txt
BEGIN { FS="," }
{
    for (i = 1; i <= NF; i++) fish[$i]++
    for (d = 1; d <= DAYS; d++) {
        newfish[8] = fish[0]
        newfish[6] = fish[0]
        for (i = 1; i <= 8; i++) newfish[i-1] += fish[i]
        delete fish
        for (i in newfish) fish[i] = newfish[i]
        delete newfish
    }
    for (i in fish) s += fish[i]
    print s
}
