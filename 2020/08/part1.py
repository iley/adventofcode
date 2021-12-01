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


def execute(program):
    ra = 0
    ip = 0
    ip_history = set()

    while True:
        if ip in ip_history:
            return ra
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

        #print('%s %d ip=%d ra=%d' % (opcode, param, ip, ra))


program = load(sys.stdin)
result = execute(program)
print(result)
