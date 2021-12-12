function traverse(from,   i) {
    if (match(from, /^[a-z]+$/)) visited[from] = 1
    if (from == "end") {
        npaths++
    } else {
        for (i in graph[from]) {
            if (!visited[graph[from][i]])
                traverse(graph[from][i])
        }
    }
    delete visited[from]
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
