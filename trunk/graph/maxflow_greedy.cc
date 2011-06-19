/**
 * if the edges are directed, need not create the backward ones
 */

typedef map<int, pair<FlowType, FlowType>> Edge;  // {node,{flow,capacity}}
struct State {
    int node, parent;
    FlowType flow;
    bool operator < (const State& e) const { return flow < e.flow; }
};
vector<Edge> e;
FlowType max_flow(int n, int source, int sink) {
    FlowType total_flow = 0;
    while (1) {
        priority_queue<State> pq;
        vector<State> path(n, {-1, -1, 0});
        for (pq.push({source, -1, INF}); !pq.empty(); ) {
            State s = pq.top(); pq.pop();
            if (path[s.node].node != -1) continue;
            path[s.node] = s;
            if (s.node == sink) break;
            for (auto& i : e[s.node])
                if (path[i.first].node == -1)
                    pq.push({i.first, s.node, min(i.second.second - i.second.first, s.flow)});
        }
        if (path[sink].flow == 0) break;
        for (int to = sink, fr; to != source; to = fr) {
            fr = path[to].parent;
            e[fr][to].first += path[sink].flow;
            e[to][fr].first -= path[sink].flow;
        }
        total_flow += path[sink].flow;
    }
    return total_flow;
}
