/**
 * @file maxflow_dinic.cc
 * @brief Dinic
 * @author 3xian
 * @version 1.1
 * @date 2011-08-08
 */

typedef int flow_t;

struct Edge {
  flow_t c, f;
  int v;
  Edge* next;
};

Edge e[M * 2];
Edge* head[N];
Edge* ep;
vector<int> d;

inline void new_edge(int u, int v, flow_t c) {
  ep->v=v, ep->c=c, ep->f=0, ep->next=head[u]; head[u]=ep++;
  ep->v=u, ep->c=0, ep->f=0, ep->next=head[v]; head[v]=ep++; // directed
}

inline Edge* back(Edge* p) {
  return e + (p - e ^ 1);
}

void init(int n) {
  ep = e;
  for (int i = 0; i < n; ++i) {
    head[i] = NULL;
  }
  d.resize(n);
}

bool bfs(int source, int sink) {
  fill(d.begin(), d.end(), -1);
  d[source] = 0;
  deque<int> q;
  for (q.push_back(source); !q.empty(); q.pop_front()) {
    int u = q.front();
    for (Edge* p = head[u]; p != NULL; p = p->next) {
      int& v = p->v;
      if (p->c > p->f && d[v] == -1) {
        d[v] = d[u] + 1;
        q.push_back(v);
      }
    }
  }
  return d[sink] != -1;
}

flow_t find(int u, int t, flow_t in) {
  if (u == t) return in;
  flow_t out = 0, m;
  for (Edge* p = head[u]; p != NULL && out < in; p = p->next) {
    if (p->c > p->f && d[p->v] == d[u] + 1 && (m = find(p->v, t, min(p->c - p->f, in - out))) > 0) {
      p->f += m;
      back(p)->f -= m;
      out += m;
    }
  }
  if (out == 0) d[u] = -1;
  return out;
}

flow_t dinic(int n, int s, int t) {
  flow_t flow = 0;
  while (bfs(s, t)) while (flow_t m = find(s, t, INF)) flow += m;
  return flow;
}
