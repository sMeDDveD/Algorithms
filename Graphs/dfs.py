with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    matrix = [list(map(int, f.readline().split())) for _ in range(n)]
    not_used = {i for i in range(n)}
    times = [0] * n
    time = 1


    def dfs(v: int):
        global time
        times[v] = time
        time += 1
        for j in range(n):
            if matrix[v][j] and j in not_used:
                not_used.discard(j)
                dfs(j)


    while not_used:
        dfs(not_used.pop())

    print(*times, file=w)
