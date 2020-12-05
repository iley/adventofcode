#!/usr/bin/env python3
import sys

def fields(line):
    parts = line.rstrip().split(' ')
    fields = {}
    for part in parts:
        if ':' not in part:
            continue
        key, val = part.split(':')
        fields[key] = val
    return fields

def passports(inp):
    passport = {}
    for line in inp:
        f = fields(line)
        if len(f) == 0:
            yield passport
            passport = {}
        passport.update(f)
    yield passport


expected_fields = set(['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'])
count = 0
for p in passports(sys.stdin):
    if expected_fields <= set(p.keys()):
        count += 1

print(count)
