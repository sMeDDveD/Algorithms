with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    adjacency = [[] for i in range(n)]
    answer = [0 for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(lambda x: int(x) - 1, f.readline().split())
        adjacency[u].append(v)
    for i in range(n):
        for now in adjacency[i]:
            answer[now] = i + 1
    print(*answer, file=w)
