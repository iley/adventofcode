#!/usr/bin/env python3
from functools import reduce


def chinese_remainder(n, a):
    sum = 0
    prod = reduce(lambda a, b: a*b, n)
    for n_i, a_i in zip(n, a):
        p = prod // n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod


def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1


start = int(input())
id_strs = input().split(',')

ids = []
for id_str in id_strs:
    if id_str == 'x':
        ids.append(-1)
    else:
        try:
            num = int(id_str)
            ids.append(num)
        except ValueError:
            continue

print(ids)
divisors = []
reminders = []
for i, n in enumerate(ids):
    if n == -1:
        continue
    divisors.append(n)
    reminders.append((-i) % n)

print(divisors)
print(reminders)


print(chinese_remainder(divisors, reminders))
