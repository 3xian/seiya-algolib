from collections import deque

inf = float('inf')

def add_edge(graph, u, v, cap):
	if u not in graph[v]:
		graph[u][v] = [0, 0]
		graph[v][u] = [0, 0]
	graph[u][v][1] += cap

def isap(graph, source, sink):
	n = len(graph)
	father, dis, cnt = [source] * n, [n] * n, [0] * n

	dis[sink] = 0
	q = deque([sink])
	while q:
		v = q.popleft()
		cnt[dis[v]] += 1
		for u in graph[v]:
			if dis[u] == n and graph[u][v][0] < graph[u][v][1]:
				dis[u] = dis[v] + 1
				q.append(u)

	flow = 0
	u = source
	while dis[source] < n:
		if u == sink:
			aug = inf
			to = u
			while to != source:
				fr = father[to]
				aug = min(aug, graph[fr][to][1] - graph[fr][to][0])
				to = fr
			while u != source:
				v = father[u]
				graph[v][u][0] += aug
				graph[u][v][0] -= aug
				u = v
			flow += aug

		go = False
		mindis = n
		for v, w in graph[u].items():
			if dis[v] < mindis and w[0] < w[1]:
				if dis[u] == dis[v] + 1:
					go = True
					father[v] = u
					u = v
					break
				mindis = dis[v]
		if not go:
			if mindis == n: break
			cnt[dis[u]] -= 1
			if cnt[dis[u]] == 0: break
			dis[u] = mindis + 1
			cnt[dis[u]] += 1
			u = father[u];
	return flow
