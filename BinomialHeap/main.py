with open("input.txt", "r") as f, open("output.txt", "w") as w:
    for (i, j) in enumerate(reversed(bin(int(f.readline()))[2:])):
        if j == "1":
            print(i)  