/**
 * multi-paths augment Dinic
 * don't forget to init head[] before setting edges
 */

struct Edge { int v,c,f; Edge* next; } e[M * 2], * head[N], * ep;
vector<int> d;
inline void new_edge(int u, int v, int c) {
    ep->v=v,ep->c=c,ep->f=0,ep->next=head[u];head[u]=ep++;
    ep->v=u,ep->c=c,ep->f=0,ep->next=head[v];head[v]=ep++;
}
inline Edge* back(Edge* p) { return e + (p - e ^ 1); }
bool bfs(int n, int source, int t) {
    d.resize(n);
    fill(d.begin(), d.end(), -1);
    d[source] = 0;
    deque<int> q;
    for (q.push_back(source); !q.empty(); q.pop_front()) {
        int u = q.front();
        for (Edge* p = head[u]; p != NULL; p = p->next) {
            int& v = p->v;
            if (p->c > p->f && d[v] == -1) {
                d[v]=d[u]+1;
                q.push_back(v);
            }
        }
    }
    return d[t]!=-1;
}
int find(int u, int t, int in) {
    if (u == t) return in;
    int out = 0, m;
    for (Edge* p = head[u]; p != NULL && out < in; p = p->next) {
        if (p->c > p->f && d[p->v] == d[u]+1 && (m = find(p->v, t, min(p->c - p->f, in - out))) > 0) {
            p->f += m;
            back(p)->f -= m;
            out += m;
        }
    }
    if (out == 0) d[u] = -1;
    return out;
}
int dinic(int n, int s, int t) {
    int flow = 0;
    while (bfs(n, s, t)) while (int m = find(s, t, INF)) flow += m;
    return flow;
}
