import re
from os import path
from collections import defaultdict

cd_regex = re.compile(r"\$ cd (.+)")
ls_dir_regex = re.compile(r"dir (.+)")
ls_file_regex = re.compile(r"([0-9]+) (.+)")

current_path = ["/"]
current_dir = "/"
dirs = defaultdict(list)

with open("input.txt") as inp:
    for line in inp:
        line = line[:-1]
        if line == "$ ls" or line == "$ cd /":
            continue
        m = cd_regex.match(line)
        if m is not None:
            cd_target = m.group(1)
            if cd_target == "..":
                if len(current_path) > 1:
                    current_path.pop()
            else:
                current_path.append(cd_target)
            current_dir = path.join(*current_path)
            continue
        m = ls_dir_regex.match(line)
        if m is not None:
            subdir = m.group(1)
            dirs[current_dir].append((subdir, None))
            continue
        m = ls_file_regex.match(line)
        if m is not None:
            size = int(m.group(1))
            file = m.group(2)
            dirs[current_dir].append((file, size))
            continue
        print(line)
        print(cd_regex)
        assert(False)

dir_sizes = {}

def dir_size(root):
    global total_size_of_small_dirs
    total_size = 0
    for entry, size in dirs[root]:
        if size is None:
            total_size += dir_size(path.join(root, entry))
        else:
            total_size += size
    dir_sizes[root] = total_size
    return total_size

dir_size("/")
total_used = dir_sizes["/"]
fs_size = 70000000
required = 30000000
free_space = fs_size - total_used
to_free_up = required - free_space

print("need to free up %d" % to_free_up)
canddiates = [(size, entry) for entry, size in dir_sizes.items() if size >= to_free_up]
print(sorted(canddiates)[0])
