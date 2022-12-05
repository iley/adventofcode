ncrates = 9
input_file = "input.txt"

crates = []
for i in range(ncrates):
    crates.append([])

instructions = []

with open(input_file) as inp:
    reading_crates = True

    for line in inp:
        line = line[:-1]

        if line == "":
            reading_crates = False
            continue

        if reading_crates:
            for i in range(ncrates):
                index = 4 * i + 1
                if index > len(line) or line[index] == " " or line[index].isdigit():
                    continue
                crates[i] = [line[index]] + crates[i]
        else:
            parts = line.split(" ")
            n = int(parts[1])
            from_crate = int(parts[3])
            to_crate = int(parts[5])
            instructions.append((n, from_crate, to_crate))

for (n, fro, to) in instructions:
    for i in range(n):
        x = crates[fro-1].pop()
        crates[to-1].append(x)

ans = ""
for crate in crates:
    if len(crate) == 0:
        continue
    ans += crate[-1]
print(ans)
