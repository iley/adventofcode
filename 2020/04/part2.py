#!/usr/bin/env python3
import re
import sys


color_re = re.compile('^#[0-9a-f]{6}$')
pid_re = re.compile('^\d{9}$')


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


def validate_number(s, min_val, max_val):
    try:
        val = int(s)
    except ValueError:
        return False
    return min_val <= val <= max_val


def validate_height(s):
    if s.endswith('cm'):
        return validate_number(s[0:-2], 150, 193)
    elif s.endswith('in'):
        return validate_number(s[0:-2], 59, 76)
    else:
        return False


def valid(passport):
    expected_fields = set(['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'])
    if not expected_fields <= set(passport.keys()):
        return False

    if len(passport['byr']) != 4 or not validate_number(passport['byr'], 1920, 2002):
        return False

    if len(passport['iyr']) != 4 or not validate_number(passport['iyr'], 2010, 2020):
        return False

    if len(passport['eyr']) != 4 or not validate_number(passport['eyr'], 2020, 2030):
        return False

    if not validate_height(passport['hgt']):
        return False

    if color_re.match(passport['hcl']) is None:
        return False

    if passport['ecl'] not in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']:
        return False

    if pid_re.match(passport['pid']) is None:
        return False

    return True


count = 0
for p in passports(sys.stdin):
    if valid(p):
        count += 1

print(count)
