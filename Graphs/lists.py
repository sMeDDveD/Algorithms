with open('input.txt', 'r') as f, open('output.txt', 'w') as w:
    n, m = map(int, f.readline().split())
    answer = [[] for i in range(n)]
    for _ in range(m):
        i, j = map(lambda x: int(x) - 1, f.readline().split())
        answer[i].append(j + 1)
        answer[j].append(i + 1)
    for now in answer:
        print(len(now), *now, file=w)