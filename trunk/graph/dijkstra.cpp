/**
 * @brief single source shortest path
 *        Dijkstra algorithm
 *
 * @tparam T
 */
template<typename T>
class Dijkstra {
public:
	void init(int n) {
		mk.resize(n, false);
		dis.resize(n, INF);
		edge.resize(n, vector<Edge>());
		father.resize(n, -1);
	}
	void new_edge(int u, int v, const T& weight) {
		edge[u].push_back(Edge(v, weight));
	}
	void run(int source) {
		dis[source] = 0;
		priority_queue<Edge> q;
		q.push(Edge(source, 0));
		while (!q.empty()) {
			int v1 = q.top().v;
			T w1 = q.top().w;
			q.pop();
			if (mk[v1]) {
				continue;
			}
			mk[v1] = true;
			for (typeof(edge[v1].begin()) it = edge[v1].begin(); it != edge[v1].end(); ++it) {
				int& v2 = it->v;
				T& w2 = it->w;
				if (!mk[v2]) {
					T w3 = w1 + w2;
					if (w3 < dis[v2]) {
						dis[v2] = w3;
						q.push(Edge(v2, w3));
						father[v2] = v1;
					}
				}
			}
		}
	}
	T get_route(int source, int dest, vector<int> &route) {
		route.clear();
		if (dis[dest] == INF) {
			return -1;
		}
		for (int u = dest; ; u = father[u]) {
			route.push_back(u);
			if (u == source) {
				break;
			}
		}
		reverse(route.begin(), route.end());
		return dis[dest];
	}

	vector<T> dis;
	vector<int> father;

private:
	class Edge {
	public:
		Edge() {
		}
		Edge(int _v, const T& _w)
			: v(_v), w(_w) {
		}
		bool operator < (const Edge& e) const {
			return w > e.w;
		}
		int v;
		T w;
	};

	static const T INF = INT_MAX / 2;
	vector<vector<Edge> > edge; 
	vector<bool> mk;
};

