import collections

with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n = int(f.readline())
    matrix = [list(map(int, f.readline().split())) for _ in range(n)]
    numbers = [0 for _ in range(n)]
    not_used = {i for i in range(n)}
    number = 1
    while not_used:
        d = collections.deque()
        d.append(not_used.pop())
        while d:
            now = d.popleft()
            numbers[now] = number
            number += 1
            for i in range(n):
                if matrix[now][i] == 1 and i in not_used:
                    d.append(i)
                    not_used.discard(i)
    print(*numbers, file=w)