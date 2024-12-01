from collections import defaultdict

input_left = []
input_right = []

# input_file = "sample.txt"
input_file = "input.txt"

with open(input_file, "r") as inp:
    for line in inp:
        parts = line.split("   ")
        if len(parts) != 2:
            continue
        input_left.append(int(parts[0]))
        input_right.append(int(parts[1]))

rcounts = defaultdict(int)
for relem in input_right:
    rcounts[relem] += 1

sum = 0
for lelem in input_left:
    sum += lelem * rcounts[lelem]

print(sum)
