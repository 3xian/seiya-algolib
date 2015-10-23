def add_edge(graph, u, v, cap):
    graph[u].setdefault(v, [0, 0])[1] += cap
    graph[v].setdefault(u, [0, 0])

def preflow_push(graph, source, sink):
    n = len(graph)
    e, h = [0] * n, [0] * n
    e[source] = float('inf')
    h[source] = n
    from collections import deque
    q = deque([source])

    def enqueue(u):
        if u != source and u != sink: q.append(u)

    def push(u, v):
        if e[v] == 0: enqueue(v)
        aug = min(e[u], graph[u][v][1] - graph[u][v][0])
        e[u] -= aug
        e[v] += aug
        graph[u][v][0] += aug
        graph[v][u][0] -= aug

    while q:
        u = q.popleft()
        for v, w in graph[u].items():
            if (u == source or h[u] == h[v] + 1) and w[0] < w[1]:
                push(u, v)
                if e[u] == 0: break
        if e[u] > 0:
            h[u] += 1
            enqueue(u)
    return e[sink]
