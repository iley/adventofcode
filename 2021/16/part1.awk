function parsebin(binstr,   i, res) {
    res = 0
    for (i = 1; i <= length(binstr); i++)
        res = res * 2 + substr(binstr, i, 1)
    return res
}

function parse(    id) {
    id = parsebin(substr(packet, pos+3, 3))
    if (id == 4) return parse_literal()
    else return parse_operator()
}

function parse_literal(    version) {
    version = parsebin(substr(packet, pos, 3))
    for (pos = pos + 6; substr(packet, pos, 1) == "1"; pos += 5) {}
    pos += 5
    return version
}

function parse_operator(    ver_sum, len, start_pos, npackets, i) {
    ver_sum = parsebin(substr(packet, pos, 3))
    if (substr(packet, pos+6, 1) == "0") {
        len = parsebin(substr(packet, pos+7, 15))
        pos += 22
        start_pos = pos
        while (pos < start_pos + len)
            ver_sum += parse()
    } else {
        npackets = parsebin(substr(packet, pos+7, 11))
        pos += 18
        for (i = 1; i <= npackets; i++)
            ver_sum += parse()
    }
    return ver_sum
}

BEGIN {
    FS = ""
    hex2bin["0"]="0000"
    hex2bin["1"]="0001"
    hex2bin["2"]="0010"
    hex2bin["3"]="0011"
    hex2bin["4"]="0100"
    hex2bin["5"]="0101"
    hex2bin["6"]="0110"
    hex2bin["7"]="0111"
    hex2bin["8"]="1000"
    hex2bin["9"]="1001"
    hex2bin["A"]="1010"
    hex2bin["B"]="1011"
    hex2bin["C"]="1100"
    hex2bin["D"]="1101"
    hex2bin["E"]="1110"
    hex2bin["F"]="1111"
}

{
    packet = ""
    for (i = 1; i <= NF; i++) packet = packet hex2bin[$i]
    pos = 1
    print parse()
}
