#!/usr/bin/env python3
import re
import sys

mask_re = re.compile('mask = ([01X]+)')
mem_re = re.compile('mem\[(\d+)\] = (\d+)')

def load(input_file):
    program = []
    for line in input_file:
        m = mask_re.match(line)
        if m is not None:
            mask = m.group(1)
            program.append(('mask', mask, None))
            continue
        m = mem_re.match(line)
        if m is not None:
            addr, val = int(m.group(1)), int(m.group(2))
            program.append(('mem', addr, val))
            continue
    return program


def apply_mask(val, mask):
    zeroes = 0
    ones = 0
    for ch in mask:
        zeroes = (zeroes << 1)
        ones = (ones << 1)
        if ch == '0':
            zeroes = zeroes | 1
        elif ch == '1':
            ones = ones | 1
    # print("mask %s ones = %s zeroes = %s" % (mask, bin(ones), bin(zeroes)))
    return (val | ones) & ~zeroes


def execute(program):
    memory = {}
    mask = None
    for opcode, arg1, arg2 in program:
        if opcode == 'mask':
            mask = arg1
        elif opcode == 'mem':
            masked_val = apply_mask(arg2, mask)
            memory[arg1] = masked_val
        else:
            assert False
    return memory


if len(sys.argv) < 2:
    print("Usage: %s file" % sys.argv[0], file=sys.stdout)
    sys.exit(1)

input_path = sys.argv[1]
with open(input_path) as inp:
    program = load(inp)

memory = execute(program)
answer = sum(memory.values())
print(answer)
