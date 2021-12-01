#!/usr/bin/env python3
import re
import sys


line_re = re.compile('(nop|acc|jmp) ([+-]\d+)')


def load(input_file):
    program = []
    for line in input_file:
        m = line_re.match(line)
        if m is None:
            continue
        opcode, param = m.group(1), int(m.group(2))
        program.append((opcode, param))
    return program


def terminates(program):
    ra = 0
    ip = 0
    ip_history = set()

    while ip < len(program):
        if ip in ip_history:
            return False
        ip_history.add(ip)

        opcode, param = program[ip]
        if opcode == 'nop':
            ip += 1
        elif opcode == 'acc':
            ra += param
            ip += 1
        elif opcode == 'jmp':
            ip += param
        else:
            print("invalid opcode %s" % opcode)
            ip += 1
    return True


def execute(program):
    ra = 0
    ip = 0

    while ip < len(program):
        opcode, param = program[ip]
        if opcode == 'nop':
            ip += 1
        elif opcode == 'acc':
            ra += param
            ip += 1
        elif opcode == 'jmp':
            ip += param
        else:
            print("invalid opcode %s" % opcode)
            ip += 1

    return ra


def make_copy(program):
    return [line for line in program]


def mutations(program):
    for i in range(len(program)):
        opcode, param = program[i]
        if opcode == 'jmp':
            copy = make_copy(program)
            copy[i] = ('nop', param)
            yield copy
        if opcode == 'nop':
            copy = make_copy(program)
            copy[i] = ('jmp', param)
            yield copy


program = load(sys.stdin)

for mutated_program in mutations(program):
    if not terminates(mutated_program):
        continue
    result = execute(mutated_program)
    print(result)
    break
