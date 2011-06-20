from collections import deque

inf = float('inf')

def add_edge(graph, u, v, cap):
	if u not in graph[v]:
		graph[u][v] = [0, 0]
		graph[v][u] = [0, 0]
	graph[u][v][1] += cap

def dinic(graph, source, sink):
	flow = 0
	dis = [-1] * len(graph)

	def bfs():
		for i in xrange(len(dis)): dis[i] = -1 
		dis[source] = 0;
		q = deque([source])
		while q:
			u = q.popleft()
			for v, w in graph[u].items():
				if dis[v] == -1 and w[0] < w[1]:
					dis[v] = dis[u] + 1
					q.append(v)
		return dis[sink] != -1

	def find(u, inpour):
		if u == sink: return inpour;
		outpour = 0
		for v, w in graph[u].items():
			if dis[v] == dis[u] + 1 and w[0] < w[1]:
				aug = find(v, min(inpour - outpour, w[1] - w[0]))
				if aug > 0:
					w[0] += aug
					graph[v][u][0] -= aug
					outpour += aug
		if outpour == 0: dis[u] = -1
		return outpour

	while bfs():
		while True:
			aug = find(source, inf)
			if aug > 0: flow += aug
			else: break
	return flow
