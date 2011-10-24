def dijkstra(graph, source):
  dis = [None] * len(graph)
  mask = [False] * len(graph)
  dis[source] = 0
  heap = []
  heappush(heap, (0, source))
  while heap:
    path_weight, u = heappop(heap)
    if mask[u]:
      continue
    mask[u] = True
    for v, w in graph[u]:
      new_dis = path_weight + w
      if dis[v] is None or new_dis < dis[v]:
        dis[v] = new_dis
        heappush(heap, (new_dis, v))
  return dis
