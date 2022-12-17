import sys

with open(sys.argv[1]) as inp:
    line = next(inp)
    moves = line.strip()


rocks = [
    [ "####" ],
    [ ".#.", "###", ".#." ],
    [ "..#", "..#", "###" ],
    [ "#", "#", "#", "#" ],
    [ "##", "##" ]
]

rock_heights = [ 1, 3, 3, 4, 2 ]

for i in range(len(rocks)):
    strs = rocks[i]
    rocks[i] = [ [0 if ch == "." else 1 for ch in s] for s in strs ]

field_height = 4
field_width = 7
field = []

for i in range(field_height):
    row = []
    for j in range(field_width):
        row.append(0)
    field.append(row)

def try_move(rock, row_row, rock_col, rock_row_diff, rock_col_diff):
    for row in range(len(rock)):
        for col in range(len(rock[row])):
            if rock[row][col]:
                field[rock_row - row][rock_col + col] = 0

    for row in range(len(rock)):
        for col in range(len(rock[row])):
            if rock[row][col] and (
                rock_col + rock_col_diff + col < 0 or
                rock_col + rock_col_diff + col >= field_width or
                rock_row + rock_row_diff - row < 0 or
                field[rock_row + rock_row_diff - row][rock_col + rock_col_diff + col]):
                # failed, move back
                for row in range(len(rock)):
                    for col in range(len(rock[row])):
                        if rock[row][col]:
                            field[rock_row - row][rock_col + col] = 1
                return False

    for row in range(len(rock)):
        for col in range(len(rock[row])):
            if rock[row][col]:
                field[rock_row + rock_row_diff - row][rock_col + rock_col_diff + col] = 1
    return True

def print_field():
    for row in reversed(field):
        for ch in row:
            if ch:
                print("#",end="")
            else:
                print(".",end="")
        print("")
    print("")


tower_height = 0
jet_index = 0
for i in range(2022):
    rock = rocks[i % len(rocks)]

    rock_row = tower_height + 3 + len(rock) - 1
    rock_col = 2

    while len(field) <= rock_row:
        field.append([0] * field_width)

    for row in range(len(rock)):
        for col in range(len(rock[row])):
            if rock[row][col] == 1:
                field[rock_row - row][rock_col + col] = 1
    # print_field()

    while True:
        jet_ch = moves[jet_index]
        jet_index = (jet_index + 1) % len(moves)

        if jet_ch == "<":
            jet_dir = -1
        else:
            jet_dir = 1

        if try_move(rock, rock_row, rock_col, 0, jet_dir):
            rock_col += jet_dir

        if try_move(rock, rock_row, rock_col, -1, 0):
            rock_row -= 1
        else:
            break

    for row in range(len(field)):
        if all(x == 0 for x in field[row]):
            tower_height = row
            break

print(tower_height)
