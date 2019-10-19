import functools
f, w = open('input.txt', 'r'), open('output.txt', 'w')
n = int(f.readline())
positions = {int(card) - 1 : pos for pos, card in enumerate(f.readline().split())}
@functools.lru_cache(maxsize=None)
def result(i, j):
    if i == j:
        return 0
    elif j - i == 1:
        return  abs(positions[i] - positions[j])
    else:
        return min([result(i, d) + result(d + 1, j) + abs(positions[d] - positions[j]) for d in range(i, j)])
w.write(str(result(0, n - 1)))