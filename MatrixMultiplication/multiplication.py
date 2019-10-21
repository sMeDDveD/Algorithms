import functools
with open('input.txt', 'r') as f,  open('output.txt', 'w') as w:
    n = int(f.readline())
    matrix = [list(map(int, line.split())) for line in f.readlines()]

    @functools.lru_cache(maxsize=None)
    def result(i, j):
        if i == j:
            return 0
        else:
            return min([result(i, d) + result(d + 1, j) +  matrix[i][0] * matrix[d][1] * matrix[j][1] for d in range(i, j)])
    w.write(str(result(0, n - 1)))