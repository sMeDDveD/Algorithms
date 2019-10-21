with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    a = list(map(int, f.readline().split()))

    def check(i, father_key):
        if i >= n:
            return True
        else:
            return a[i] >= father_key and check(2 * i + 1, a[i]) and check(2 * i + 2, a[i])

    w.write('Yes' if check(0, -1421342341242) else 'No')