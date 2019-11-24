with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n, m = map(int, f.readline().split())
    matrix = [[0] * n for i in range(n)]
    for _ in range(m):
        i, j = map(lambda x: int(x) - 1, f.readline().split())
        matrix[i][j] = matrix[j][i] = 1
    for i in range(n):
        print(*matrix[i], file=w)
