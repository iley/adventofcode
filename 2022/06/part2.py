inp = input()

for i in range(len(inp)):
    chars = inp[i-14:i]
    if len(set(chars)) == 14:
        print(i)
        break
