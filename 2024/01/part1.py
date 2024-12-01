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

sum = 0
for left, right in zip(sorted(input_left), sorted(input_right)):
    sum += abs(left - right)

print(sum)
