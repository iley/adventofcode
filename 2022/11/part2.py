import re

class Monkey:
    def __init__(self, items, operation, test, iftrue, iffalse):
        self.items = items
        self.operation = operation
        self.test = test
        self.iftrue = iftrue
        self.iffalse = iffalse
        self.count = 0


monkeys = []
op_regex = re.compile(r"Operation: new = old (.) (old|\d+)")

with open("input.txt") as inp:
    for line in inp:
        line = line.strip()
        if line.startswith("Monkey"):
            items = []
            op = None
            test = None
            iftue = None
            iffalse = None
        elif line.startswith("Starting items: "):
            items = [int(x) for x in line.removeprefix("Starting items: ").split(", ")]
        elif line.startswith("Operation:"):
            m = op_regex.match(line)
            operator = m.group(1)
            value = m.group(2)
            op = [operator, value]
        elif line.startswith("Test: divisible by"):
            test = int(line.removeprefix("Test: divisible by"))
        elif line.startswith("If true: throw to monkey "):
            iftrue = int(line.removeprefix("If true: throw to monkey "))
        elif line.startswith("If false: throw to monkey "):
            iffalse = int(line.removeprefix("If false: throw to monkey "))
            monkey = Monkey(items, op, test, iftrue, iffalse)
            monkeys.append(monkey)
        elif line == "":
            continue
        else:
            assert False

common_monkey_denominator = 1
for monkey in monkeys:
    common_monkey_denominator *= monkey.test

for step in range(10000):
    for i, monkey in enumerate(monkeys):
        print("Monkey %d" % i)
        for item in monkey.items:
            op, val = monkey.operation
            if op == "+":
                if val == "old":
                    new_item = item + item
                else:
                    new_item = item + int(val)
            elif op == "*":
                if val == "old":
                    new_item = item * item
                else:
                    new_item = item * int(val)
            else:
                assert False
            new_item = new_item % common_monkey_denominator
            if new_item % monkey.test == 0:
                dest = monkey.iftrue
            else:
                dest = monkey.iffalse
            print("item %d -> %d, throw to %d" % (item, new_item, dest))
            assert dest != i
            monkeys[dest].items.append(new_item)
            monkey.count += 1
            monkey.items = []


sorted_monkeys = sorted(monkeys, key=lambda m: m.count, reverse=True)
print(sorted_monkeys[0].count * sorted_monkeys[1].count)
