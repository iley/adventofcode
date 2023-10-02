import sys

original_file = []

with open(sys.argv[1]) as inp:
    for line in inp:
        original_file.append(int(line))


def mix(original_file):
    file = list(original_file)

    # print(file)

    for c, n in enumerate(original_file):
        print(c)
        for i in range(abs(n)):
            i = file.index(n)
            if n >= 0:
                if i == len(file) - 1:
                    file = file[0:1] + [n] + file[1:len(file)-1]
                elif i == len(file) - 2:
                    file = [n] + file[:len(file)-2] + file[len(file)-1:]
                else:
                    tmp = file[i]
                    file[i] = file[i+1]
                    file[i+1] = tmp
            else:
                if i == 0:
                    file = file[1:len(file)-1] + [n] + file[len(file)-1:]
                elif i == 1:
                    file = file[:1] + file[2:] + [n]
                else:
                    tmp = file[i]
                    file[i] = file[i-1]
                    file[i-1] = tmp
        # print(file)

    return file


mixed_file = mix(original_file)
zero_pos = mixed_file.index(0)
coord1 = mixed_file[(zero_pos + 1000) % len(mixed_file)]
coord2 = mixed_file[(zero_pos + 2000) % len(mixed_file)]
coord3 = mixed_file[(zero_pos + 3000) % len(mixed_file)]
print(coord1 + coord2 + coord3)
