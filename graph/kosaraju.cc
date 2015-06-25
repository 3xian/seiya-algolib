// Input
vector<vector<int> > edge;
// Output
vector<int> component_label;
int component_count;
// Temp
vector<vector<int> > reversed_edge;
vector<int> stack;

void dfs1(int u) {
    if (component_label[u] != -1) return;
    component_label[u] = 0;

    const vector<int>& e = edge[u];
    for (int i = 0; i < e.size(); i++) {
        dfs1(e[i]);
    }

    stack.push_back(u);
}

void dfs2(int u) {
    if (component_label[u] != -1) return;
    component_label[u] = component_count;

    const vector<int>& e = reversed_edge[u];
    for (int i = 0; i < e.size(); i++) {
        dfs2(e[i]);
    }
}

void build_reversed_graph(int n) {
    reversed_edge.resize(n);
    for (int u = 0; u < n; u++) {
        reversed_edge[u].clear();
    }
    for (int u = 0; u < n; u++) {
        const vector<int>& e = edge[u];
        for (int i = 0; i < e.size(); i++) {
            int v = e[i];
            reversed_edge[v].push_back(u);
        }
    }
}

void kosaraju(int n) {
    component_label.resize(n);
    component_count = 0;
    build_reversed_graph(n);

    std::fill(component_label.begin(), component_label.end(), -1);
    for (int i = 0; i < n; i++) {
        dfs1(i);
    }

    std::fill(component_label.begin(), component_label.end(), -1);
    while (not stack.empty()) {
        int top_vertex = stack.back();
        stack.pop_back();

        if (component_label[top_vertex] == -1) {
            dfs2(top_vertex);
            component_count++;
        }
    }
}

