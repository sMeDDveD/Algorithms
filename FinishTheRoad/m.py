import collections

with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    adjacency = [[] for i in range(n)]
    for i in range(int(f.readline())):
        a, b = map(lambda x: int(x) - 1, f.readline().split())
        adjacency[a].append(b)
        adjacency[b].append(a)
    used = [False] * n
    answer = 0

    def bfs(start):
        d = collections.deque()
        d.append(start)
        while d:
            now = d.popleft()
            used[now] = True
            for next_to in adjacency[now]:
                if not used[next_to]:
                    d.append(next_to)
    answer = 0
    for i in range(n):
        if not used[i]:
            bfs(i)
            answer += 1
    print(answer - 1, file=w)