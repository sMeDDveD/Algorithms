with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    matrix = [list(map(int, f.readline().split())) for _ in range(n)]
    answer = [0] * n
    for i in range(n):
        for j in range(n):
            if matrix[i][j]:
                answer[j] = i + 1
    print(*answer, file=w)