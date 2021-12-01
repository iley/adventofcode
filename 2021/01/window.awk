{
    first = second
    second = third
    third = $1
}

NR >= 3 {
    print first + second + third
}
