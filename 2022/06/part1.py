inp = input()

for i in range(len(inp)):
    chars = inp[i-4:i]
    if len(set(chars)) == 4:
        print(i)
        break
