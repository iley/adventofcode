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
        assert(False)

total_size_of_small_dirs = 0

def traverse(root):
    global total_size_of_small_dirs
    total_size = 0
    for entry, size in dirs[root]:
        if size is None:
            total_size += traverse(path.join(root, entry))
        else:
            total_size += size
    if total_size < 100000:
        total_size_of_small_dirs += total_size
    return total_size

traverse("/")
print(total_size_of_small_dirs)
