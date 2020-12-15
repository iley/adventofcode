#!/usr/bin/env python3

start = int(input())
id_strs = input().split(',')

ids = []
for id_str in id_strs:
    try:
        num = int(id_str)
        ids.append(num)
    except ValueError:
        continue


print(start)
print(ids)

starts = []
for id in ids:
    if start % id == 0:
        starts.append(start)
    else:
        x = (start // id + 1) * id
        starts.append((x, id))


s, id = min(starts)
print(s, id)
print( (s-start) * id )
