from collections import deque

inf = float('inf')

def add_edge(graph, u, v, cap):
  if u not in graph[v]:
    graph[u][v] = [0, 0]
    graph[v][u] = [0, 0]
  graph[u][v][1] += cap

def preflow_push(graph, source, sink):
  n = len(graph)
  e, h = [0] * n, [0] * n
  e[source] = inf
  h[source] = n
  q = deque([source])

  def enqueue(u):
    if u != source and u != sink:
      q.append(u)

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
