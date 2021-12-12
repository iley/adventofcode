function traverse(from,   i) {
    if (match(from, /^[a-z]+$/)) visited[from]++
    if (from == "end") {
        npaths++
    } else {
        for (i in graph[from]) {
            if (graph[from][i] != "start" && (visited[graph[from][i]] < 1 || maxval(visited) <= 1))
                traverse(graph[from][i])
        }
    }
    visited[from]--
}

function maxval(dict,   k, max) {
    max = 0
    for (k in dict)
        if (dict[k] > max)
            max = dict[k]
    return max
}

BEGIN { FS = "-" }

{
    graph[$1][length(graph[$1])+1] = $2
    graph[$2][length(graph[$2])+1] = $1
}

END {
    traverse("start")
    print npaths
}
