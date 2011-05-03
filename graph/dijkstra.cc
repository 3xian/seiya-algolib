/**
 * single source shortest path
 * Dijkstra algorithm
 */

template<typename T> struct Dijkstra {
    struct Edge {
        int v;
        T w;
        bool operator < (const Edge& e) const { return w > e.w; }
    };

    static const T INF = __INT_MAX__ / 2;
    vector<vector<Edge>> edge;
    vector<bool> mk;
    vector<T> dis;
    vector<int> father;

    void init(int n) {
        edge = vector<vector<Edge>>(n, vector<Edge>());
        mk = vector<bool>(n, false);
        dis = vector<T>(n, INF);
        father = vector<int>(n, -1);
    }
    void new_edge(int u, int v, const T& weight) {
        edge[u].push_back(Edge{v, weight});
    }
    void run(int source) {
        priority_queue<Edge> q;
        dis[source] = 0;
        for (q.push({source, 0}); !q.empty(); ) {
            int v1 = q.top().v;
            T w1 = q.top().w;
            q.pop();
            if (mk[v1]) continue;
            mk[v1] = true;
            for (auto& i : edge[v1]) {
                int& v2 = i.v;
                T& w2 = i.w;
                if (!mk[v2]) {
                    T w3 = w1 + w2;
                    if (w3 < dis[v2]) {
                        dis[v2] = w3;
                        q.push({v2, w3});
                        father[v2] = v1;
                    }
                }
            }
        }
    }
    T get_route(int source, int dest, vector<int>& route) const {
        route.clear();
        if (dis[dest] == INF) return -1;
        for (int u = dest; ; u = father[u]) {
            route.push_back(u);
            if (u == source) break;
        }
        reverse(route.begin(), route.end());
        return dis[dest];
    }
};
